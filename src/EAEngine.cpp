/* 
 * Engine
 * @author ECHOES Technologies (FPO)
 * @date 21/08/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS
 * WITHOUT COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "EAEngine.h"

using namespace std;

int EAEngine::_signum = 0;
boost::thread_group EAEngine::_threads;

EAEngine::EAEngine(const std::string& name, const std::string& version) :
_confOK(false), _name(name), _version(version)
{
     _signum = 0;
    signalsHangler();
}

EAEngine::EAEngine(const EAEngine& orig)
{
}

EAEngine::~EAEngine()
{
}

void EAEngine::setServerConfiguration(int argc, char **argv)
{
    if (conf.readProgramOptions(argc, argv))
        _confOK = true;
}

bool EAEngine::start()
{
    bool res = false;

    logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << _name << "\" swVersion=\"" << _version << "\"] (re)start";

    /* Daemonization */
#ifdef NDEBUG
    if (chdir("/") != 0)
    {
        cerr << "failed to reach root \n";
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
            if (conf.isCleaner())
                _threads.create_thread(boost::bind(&EAEngine::removeOldValues, this));
            else
                logger.entry("info") << "[EAEngine] Mode Cleaner disable";

            if (conf.isAlerter())
                _threads.create_thread(boost::bind(&EAEngine::checkNewAlerts, this));
            else
                logger.entry("info") << "[EAEngine] Mode Alerter disable";

            if (conf.isCalculator())
                _threads.create_thread(boost::bind(&EAEngine::calculate, this));
            else
                logger.entry("info") << "[EAEngine] Mode Calculator disable";

            res = true;
        }
        else
        {
            logger.entry("error") << "[EAEngine] This Engine ID is not in the database.";
        }
    }

    return res;
}

int EAEngine::waitForShutdown()
{
    // wait the end of the created thread
    _threads.join_all();

    return _signum;
}

void EAEngine::stop()
{
    logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << _name << "\" swVersion=\"" << _version << "\"] stop";
}

void EAEngine::signalsHangler()
{
    for (unsigned short i = 1; i < SIGWINCH; i++)
    {
        signal(i, EAEngine::signalHandling);
    }
    signal(SIGPWR, EAEngine::signalHandling);
    signal(SIGSYS, EAEngine::signalHandling);
}

void EAEngine::signalHandling(int signum)
{    
    _signum = signum;
    _threads.interrupt_all();
}

void EAEngine::checkNewAlerts()
{
    AlertProcessor alertProcessor;
    logger.entry("info") << "[EAEngine] Mode Alerter start";

    alertProcessor.verifyAlerts(&_signum);
}

void EAEngine::removeOldValues()
{
    Session session(conf.getSessConnectParams());
    
    logger.entry("info") << "[EAEngine] Mode Cleaner start";
    
    while (_signum == 0)
    {
        logger.entry("info") << "[EAEngine] Cleaning of IVA Table";
        
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
            logger.entry("error") << "[EAEngine] " << e.what();
        }

        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadRemoveOldValues));
    }
    
    logger.entry("info") << "[EAEngine] Mode Cleaner stop";
}

void EAEngine::calculate()
{
    const int ivaListSize = 50;
    Session session(conf.getSessConnectParams());

    logger.entry("info") << "[EAEngine] Mode Calculator start";
    
    while (_signum == 0)
    {
        std::vector<long long> ivaIdList;

        try
        {
            Wt::Dbo::Transaction transaction1(session);
            // we get iva values where state = ToBeCalculate
            std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
                    " WHERE \"IVA_STATE\" = 9 FOR UPDATE LIMIT ?";
            Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue>> ivaList = session.query<Wt::Dbo::ptr<InformationValue>>(queryString).bind(ivaListSize);

            for (Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> >::const_iterator it = ivaList.begin(); it != ivaList.end(); ++it)
            {
                session.execute("UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = ? WHERE \"IVA_ID\" = ?").bind(1).bind(it->id());
                ivaIdList.push_back(it->id());
            }

            logger.entry("debug") << "[EAEngine] " << ivaIdList.size() << " IVA retrieved to calculate";
            transaction1.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[EAEngine] IVA selection: " << e.what();
        }

        for (unsigned short i(0); i < ivaIdList.size(); ++i)
        {
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
                }
                transactionIvaData.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                logger.entry("error") << "[EAEngine] IVA data: " << e.what();
                continue;
            }
            
            if(calculate != "")
            {

                logger.entry("debug") << "[EAEngine] calculate value: " << calculate;

                if (calculate == "searchValueToCalculate")
                {
                    //we get the calculation data
                    try
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
                        }
                        transactionCalcData.commit();
                    }
                    catch (Wt::Dbo::Exception e)
                    {
                        logger.entry("error") << "[EAEngine] IVA data: " << e.what();
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
                        logger.entry("debug") << "[EAEngine] Launch calc query: " << realCalculate;
                        session.execute("SELECT " + realCalculate.toUTF8() + "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
                        .bind(seaId).bind(srcId).bind(plgId).bind(infValueNum).bind(untId).bind(ivaLotNum)
                        .bind(9) // state
                        .bind(ivaLineNum).bind(ivaAssetId)
                        .bind(10) // limit
                        .bind(ivaId);
                        logger.entry("debug") << "[EAEngine] calc done.";
                        transactionCalcul.commit();
                    }
                    catch (Wt::Dbo::Exception e)
                    {
                        logger.entry("error") << "[EAEngine] IVA data: " << e.what();
                        continue;
                    }   
                }
                else
                {
                    logger.entry("error") << "[EAEngine] no real calculate";
                }
            }
            else
            {
                logger.entry("debug") << "[EAEngine] no calculate";
            }
        }

        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCalculate));
    }

    logger.entry("info") << "[EAEngine] Mode Calculator stop";
}

