/* 
 * Main
 * @author ECHOES Technologies (RHI)
 * @date 20/02/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS
 * WITHOUT COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include <tools/Session.h>

#include "Logger.h"
#include "Conf.h"
#include "AlertProcessor.h"

void checkNewAlerts();
void removeOldValues();
void calculate();
void cleanAll();



#define SOFTWARE_NAME "ECHOES Alert - Engine"
#define SOFTWARE_VERSION "0.1.0"

int main(int argc, char **argv)
{
    int res = EXIT_FAILURE;

    if (conf.readProgramOptions(argc, argv))
    {
        logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << SOFTWARE_NAME << "\" swVersion=\"" << SOFTWARE_VERSION << "\"] (re)start";

        /* Daemonization */
#ifdef NDEBUG
        if (chdir("/") != 0)
        {
            std::cerr << "failed to reach root \n";
            return res;
        }
        if (fork() != 0)
            exit(EXIT_SUCCESS);
        setsid();
        if (fork() != 0)
            exit(EXIT_SUCCESS);
#endif

        if (conf.readConfFile())
        {
            if (conf.isInDB())
            {
                // thread's creation
                boost::thread_group threadsEngine;

                // execute the method removeOldValues() checkNewAlerts() in parallel
                if (conf.isCleaner())
                {
                    logger.entry("info") << "[Main] Mode Cleaner enable";
                    threadsEngine.create_thread(&removeOldValues);
                }
                else
                    logger.entry("info") << "[Main] Mode Cleaner disable";
                if (conf.isAlerter())
                {
                    logger.entry("info") << "[Main] Mode Alerter enable";
                    threadsEngine.create_thread(&checkNewAlerts);
                }
                else
                    logger.entry("info") << "[Main] Mode Alerter disable";
                if (conf.isCalculator())
                {
                    logger.entry("info") << "[Main] Mode Calculator enable";
                    threadsEngine.create_thread(&calculate);
                }
                else
                    logger.entry("info") << "[Main] Mode Calculator disable";

                // wait the end of the created thread
                threadsEngine.join_all();

                res = EXIT_SUCCESS;
            }
            else
            {
                logger.entry("error") << "[Main] This Engine ID is not in the database.";
            }
        }

        logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << SOFTWARE_NAME << "\" swVersion=\"" << SOFTWARE_VERSION << "\"] stop";
    }
    
    return res;
}

void checkNewAlerts()
{
    AlertProcessor alertProcessor;
    alertProcessor.verifyAlerts();
}

void removeOldValues()
{
    Echoes::Dbo::Session session(conf.getSessConnectParams());

    while (true)
    {
        logger.entry("info") << "[Main] Cleaning of IVA Table";
        
        //remove values older than 1 day from information_value (duplicated in T_INFORMATION_HISTORICAL_VALUE_IHV)
        try
        {
            Wt::Dbo::Transaction transaction(session);
            std::string queryString = "DELETE FROM \"T_INFORMATION_VALUE_IVA\""
                    " WHERE"
                    " \"IVA_CREA_DATE\" < (NOW() - interval '1 day')";
            session.execute(queryString);
            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[Main] " << e.what();
        }
        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadRemoveOldValues));
    };
}

void calculate()
{
    const int ivaListSize = 50;
    Echoes::Dbo::Session session(conf.getSessConnectParams());

    while (true)
    {
        std::vector<long long> ivaIdList;

        try
        {
            Wt::Dbo::Transaction transaction1(session);
            // we get iva values where state = ToBeCalculate
            std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
                    " WHERE \"IVA_STATE\" = 9 FOR UPDATE LIMIT ?";
            Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>> ivaList = session.query<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>>(queryString).bind(ivaListSize);

            for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::InformationValue> >::const_iterator it = ivaList.begin(); it != ivaList.end(); ++it)
            {
                session.execute("UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = ? WHERE \"IVA_ID\" = ?").bind(1).bind(it->id());
                ivaIdList.push_back(it->id());
            }

            logger.entry("debug") << "[Main] " << ivaIdList.size() << " IVA retrieved to calculate";
            transaction1.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[Main] IVA selection: " << e.what();
        }

        for (unsigned short i(0); i < ivaIdList.size(); ++i)
        {
            int ivaLotNum, ivaLineNum;
//            int infValueNum;
            long long ivaAssetId;
            long long ivaId; //, plgId, seaId, srcId, untId;

            Wt::WString calculate, realCalculate;

            // we get the information related to the iva into ptrInfTmp ptr
            Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr;
            try
            {
                Wt::Dbo::Transaction transactionIvaData(session);
                ivaPtr = session.find<Echoes::Dbo::InformationValue>()
                        .where("\"IVA_ID\" = ?").bind(ivaIdList[i])
                        .limit(1);

                ivaLotNum = ivaPtr->lotNumber;
                ivaLineNum = ivaPtr->lineNumber;
                ivaAssetId = ivaPtr->informationData->asset.id();
                ivaId = ivaIdList[i];



                if (ivaPtr->informationData->information->calculate)
                {
                    if (!ivaPtr->informationData->information->calculate.get().empty())
                    {
                        calculate = ivaPtr->informationData->information->calculate.get();
                    }
                }
                transactionIvaData.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                logger.entry("error") << "[Main] IVA data: " << e.what();
                continue;
            }
            
            if(calculate != "")
            {
                //FIXME
                logger.entry("debug") << "[Main] calculate value: " << calculate;

                if (calculate == "searchValueToCalculate")
                {
                    //we get the calculation data
                    try
                    {
                        Wt::Dbo::Transaction transactionCalcData(session);
                        
                        Wt::Dbo::ptr<Echoes::Dbo::InformationData> ptrInfData = session.find<Echoes::Dbo::InformationData>()
                                .where("\"IDA_FIL_FIL_ID\" = ?").bind(ivaPtr->informationData->filter.id())
                                .where("\"IDA_AST_AST_ID\" = ?").bind(ivaPtr->informationData->asset.id())
                                .where("\"IDA_FILTER_FIELD_INDEX\" = ?").bind(-1)
                                .limit(1);

                        if (ptrInfData->information->calculate)
                        {
                            if (!ptrInfData->information->calculate.get().empty())
                            {
                                realCalculate = ptrInfData->information->calculate.get();
                            }
                        }
                        transactionCalcData.commit();
                    }
                    catch (Wt::Dbo::Exception e)
                    {
                        logger.entry("error") << "[Main] IVA data: " << e.what();
                        continue;
                    }
                }
                else
                {
                    realCalculate = calculate;
                }

                if(realCalculate != "")
                {
                    //calcul
                    try
                    {
                        Wt::Dbo::Transaction transactionCalcul(session);
                        logger.entry("debug") << "[Main] Launch calc query: " << realCalculate;
                        session.execute("SELECT " + realCalculate.toUTF8() + "(?, ?, ?, ?, ?, ?, ?)")
                        .bind(ivaPtr->informationData.id()).bind(ivaLotNum)
                        .bind(9) // state
                        .bind(ivaLineNum).bind(ivaAssetId)
                        .bind(10) // limit
                        .bind(ivaId);
                        logger.entry("debug") << "[Main] calc done.";
                        transactionCalcul.commit();
                    }
                    catch (Wt::Dbo::Exception e)
                    {
                        logger.entry("error") << "[Main] IVA data: " << e.what();
                        continue;
                    }   
                }
                else
                {
                    logger.entry("error") << "[Main] no real calculate";
                }
            }
            else
            {
                logger.entry("debug") << "[Main] no calculate";
            }
        }

        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCalculate));
    }
}