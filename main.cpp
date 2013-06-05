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

#include <tools/SessionPool.h>

#include "Logger.h"
#include "Conf.h"
#include "AlertProcessor.h"

void checkNewAlerts();
void removeOldValues();
void calculate();
void cleanAll();

SessionPool* SessionPool::instance = 0;
std::string SessionPool::credentials = "";
boost::mutex SessionPool::mutex;

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
//            return EXIT_FAILURE;
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
    Session session(conf.getSessConnectParams());

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
    Session session(conf.getSessConnectParams());

    while (true)
    {
        long long ivaIdList[ivaListSize];
        for (int i = 0; i < ivaListSize; i++)
        {
            ivaIdList[i] = -1;
        }
        try
        {
            Wt::Dbo::Transaction transaction1(session);
            // we get iva values where state = ToBeCalculate
            std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
                    " WHERE \"IVA_STATE\" = 9 FOR UPDATE LIMIT ?";
            Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue>> ivaList = session.query<Wt::Dbo::ptr<InformationValue>>(queryString).bind(ivaListSize);

            int idx = 0;
            for (Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> >::const_iterator j = ivaList.begin(); j != ivaList.end(); ++j)
            {
                session.execute("UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = ? WHERE \"IVA_ID\" = ?").bind(1).bind(j->id());
                ivaIdList[idx] = j->id();
                idx++;
            }
            transaction1.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[Main] IVA selection: " << e.what();
        }

        for (int i = 0; i < ivaListSize; i++)
        {
            if (ivaIdList[i] == -1)
            {
                break;
            }

            int ivaLotNum, ivaLineNum, infValueNum;
            long long ivaAssetId, ivaId, plgId, seaId, srcId, untId;

            Wt::WString calculate, realCalculate;

            // we get the information related to the iva into ptrInfTmp ptr

            try
            {
                Wt::Dbo::Transaction transactionIvaData(session);
                Wt::Dbo::ptr<InformationValue> ivaPtr = session.find<InformationValue>()
                        .where("\"IVA_ID\" = ?").bind(ivaIdList[i])
                        .limit(1);

                ivaLotNum = ivaPtr->lotNumber;
                ivaLineNum = ivaPtr->lineNumber;
                ivaAssetId = ivaPtr->asset.id();
                ivaId = ivaIdList[i];

                plgId = ivaPtr->information->pk.search->pk.source->pk.plugin.id();
                seaId = ivaPtr->information->pk.search->pk.id;
                srcId = ivaPtr->information->pk.search->pk.source->pk.id;
                untId = ivaPtr->information->pk.unit.id();
                infValueNum = ivaPtr->information->pk.subSearchNumber;

                if (ivaPtr->information->calculate)
                {
                    if (!ivaPtr->information->calculate.get().empty())
                    {
                        calculate = ivaPtr->information->calculate.get();
                    }
                    else
                    {
                        logger.entry("error") << "[Main] no calculate";
                        transactionIvaData.commit();
                        break;
                    }
                }
                else
                {
                    logger.entry("error") << "[Main] no calculate";
                    transactionIvaData.commit();
                    break;
                }
                transactionIvaData.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                logger.entry("error") << "[Main] IVA data: " << e.what();
            }

            //we get the calculation data
            try
            {
                logger.entry("debug") << "[Main] calculate value: " << calculate;

                if (calculate == "searchValueToCalculate")
                {
                    Wt::Dbo::Transaction transactionCalcData(session);
                    Wt::Dbo::ptr<Information2> ptrInfRes = session.find<Information2>()
                            .where("\"PLG_ID_PLG_ID\" = ?").bind(plgId)
                            .where("\"SRC_ID\" = ?").bind(srcId)
                            .where("\"SEA_ID\" = ?").bind(seaId)
                            .where("\"INF_VALUE_NUM\" = ?").bind(-1)
                            .limit(1);

                    if (ptrInfRes->calculate)
                    {
                        if (!ptrInfRes->calculate.get().empty())
                        {
                            realCalculate = ptrInfRes->calculate.get();
                        }
                        else
                        {
                            logger.entry("error") << "[Main] no real calculate";
                            transactionCalcData.commit();
                            break;
                        }
                    }
                    else
                    {
                        logger.entry("error") << "[Main] no real calculate";
                        transactionCalcData.commit();
                        break;
                    }
                    transactionCalcData.commit();
                }
                else
                {
                    realCalculate = calculate;
                }
            }
            catch (Wt::Dbo::Exception e)
            {
                logger.entry("error") << "[Main] iva data: " << e.what();
            }

            //calcul
            try
            {
                Wt::Dbo::Transaction transactionCalcul(session);
                std::string queryStr = "SELECT " + realCalculate.toUTF8() + "(" + boost::lexical_cast<std::string>(seaId)
                        + "," + boost::lexical_cast<std::string>(srcId)
                        + "," + boost::lexical_cast<std::string>(plgId)
                        + "," + boost::lexical_cast<std::string>(infValueNum)
                        + "," + boost::lexical_cast<std::string>(untId)
                        + "," + boost::lexical_cast<std::string>(ivaLotNum)
                        + ",9" //state
                        + "," + boost::lexical_cast<std::string>(ivaLineNum)
                        + "," + boost::lexical_cast<std::string>(ivaAssetId)
                        + ",10" // limit
                        + "," + boost::lexical_cast<std::string>(ivaId)
                        + ")"
                        ;
                logger.entry("debug") << "[Main] calc query: " << queryStr;
                session.execute(queryStr);
                logger.entry("debug") << "[Main] calc done.";
                transactionCalcul.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                logger.entry("error") << "[Main] iva data: " << e.what();
            }
            logger.entry("debug") << "[Main] launching calcul";
            // We launch the calcul

        }

        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCalculate));
    }
}