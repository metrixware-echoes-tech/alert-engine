/* 
 * Engine Server
 * @author ECHOES Technologies (RHI, FPO)
 * @date 24/02/2014
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2014 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "Server.h"

using namespace std;

int Server::m_signum = 0;
boost::thread_group Server::m_threads;

Server::Server(const string& name, const string& version) :
m_optionsOK(false),
m_name(name),
m_version(version)
{
    m_signum = 0;
    signalsHandler();
}

Server::~Server()
{
}	

void Server::setServerConfiguration(int argc, char **argv)
{
    if (conf.readProgramOptions(argc, argv))
    {
        m_optionsOK = true;
    }
}

bool Server::start()
{
    bool res = false;

    if (m_optionsOK)
    {
        logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << m_name << "\" swVersion=\"" << m_version << "\"] (re)start";

#ifdef NDEBUG
        // Daemonization
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

        // Pid File creation
        ofstream pidFile(m_pidPath.c_str());
        if (!pidFile)
        {
            logger.entry("error") << "[Server] " << m_pidPath << ": " << strerror(errno);
        }
        else
        {
            pidFile << getpid() << std::endl;
        }
#endif

        if (conf.readConfFile())
        {
            if (conf.isInDB())
            {
                if (conf.isCleaner())
                {
                    m_threads.create_thread(boost::bind(&Server::removeOldValues, this));
                }
                else
                {	
                    logger.entry("info") << "[Server] Mode Cleaner disable";
                }
                if (conf.isAlerter())
                {
                    m_threads.create_thread(boost::bind(&Server::checkNewAlerts, this));
                }
                else
                {
                    logger.entry("info") << "[Server] Mode Alerter disable";
                }
                if (conf.isCalculator())
                {
                    m_threads.create_thread(boost::bind(&Server::calculate, this));
                }
                else
                {
                    logger.entry("info") << "[Server] Mode Calculator disable";
                }

                res = true;
            }
            else
            {
                logger.entry("error") << "[Server] This Engine ID is not in the database.";
            }
        }
    }
    return res;
}

int Server::waitForShutdown()
{
    // wait the end of the created thread
    m_threads.join_all();

    return m_signum;
}

void Server::stop()
{
#ifdef NDEBUG
    // Pid File suppression
    if (remove(m_pidPath.c_str()) < 0)
    {
        logger.entry("error") << "[Server] " << m_pidPath << ": " << strerror(errno);
    }
#endif
    logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << m_name << "\" swVersion=\"" << m_version << "\"] stop";
}

void Server::restart(int argc, char **argv, char **envp)
{
  char *path = realpath(argv[0], 0);

  // Try a few times since this may fail because we have an incomplete
  // binary...
  for (int i = 0; i < 5; ++i)
  {
    int result = execve(path, argv, envp);
    if (result != 0)
    {
      sleep(1);
    }
  }

  perror("execve");
}

void Server::signalsHandler()
{
    set<unsigned short> ignored {SIGCHLD, SIGCLD, SIGIO, SIGPOLL, SIGSTOP, SIGTSTP, SIGCONT, SIGTTIN, SIGTTOU, SIGURG, SIGWINCH};
    
    for (unsigned short i = 1; i < SIGSYS; i++)
    {
        if (ignored.find(i) == ignored.end())
        {
            signal(i, Server::signalHandling);
        }
    }
}

void Server::signalHandling(int signum)
{    
    m_signum = signum;
    m_threads.interrupt_all();
}

void Server::checkNewAlerts()
{
    AlertProcessor alertProcessor;
    logger.entry("info") << "[Server] Mode Alerter start";

    alertProcessor.verifyAlerts(&m_signum);
}

void Server::removeOldValues()
{
    Echoes::Dbo::Session session(conf.getSessConnectParams());

    logger.entry("info") << "[Server] Mode Cleaner start";

    while (m_signum == 0)
    {
        logger.entry("info") << "[Server] Cleaning of IVA Table";
        
        //remove values older than 1 day from information_value (duplicated in T_INFORMATION_HISTORICAL_VALUE_IHV)
        try
        {
            Wt::Dbo::Transaction transaction(session);
            const string queryString = "DELETE FROM \"T_INFORMATION_VALUE_IVA\""
                    " WHERE"
                    " \"IVA_CREA_DATE\" < (NOW() - interval '1 day')";
            session.execute(queryString);
            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            logger.entry("error") << "[Server] Wt::Dbo: " << e.what();
        }
        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadRemoveOldValues));
    }

    logger.entry("info") << "[Server] Mode Cleaner stop";
}

void Server::calculate()
{
    const int ivaListSize = 50;
    Echoes::Dbo::Session session(conf.getSessConnectParams());

    logger.entry("info") << "[Server] Mode Calculator start";

    while (m_signum == 0)
    {
        vector<long long> ivaIdList;

        try
        {
            Wt::Dbo::Transaction transaction1(session);
            // we get iva values where state = ToBeCalculate
            string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
                    " WHERE \"IVA_STATE\" = 9 FOR UPDATE LIMIT ?";
            Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>> ivaList = session.query<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>>(queryString).bind(ivaListSize);

            for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::InformationValue> >::const_iterator it = ivaList.begin(); it != ivaList.end(); ++it)
            {
                session.execute("UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = ? WHERE \"IVA_ID\" = ?").bind(1).bind(it->id());
                ivaIdList.push_back(it->id());
            }

            logger.entry("debug") << "[Server] " << ivaIdList.size() << " IVA retrieved to calculate";
            transaction1.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            logger.entry("error") << "[Server] Wt::Dbo: " << e.what();
        }

        for (unsigned short i(0); i < ivaIdList.size(); ++i)
        {
            int ivaLotNum, ivaLineNum;
            long long ivaAssetId;
            long long ivaId;

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
            catch (Wt::Dbo::Exception const& e)
            {
                logger.entry("error") << "[Server] Wt::Dbo: " << e.what();
                continue;
            }
            
            if(calculate != "")
            {
                //FIXME
                logger.entry("debug") << "[Server] calculate value: " << calculate;

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
                    catch (Wt::Dbo::Exception const& e)
                    {
                        logger.entry("error") << "[Server] Wt::Dbo: " << e.what();
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
                        logger.entry("debug") << "[Server] Launch calc query: " << realCalculate;
                        session.execute("SELECT " + realCalculate.toUTF8() + "(?, ?, ?, ?, ?, ?, ?)")
                        .bind(ivaPtr->informationData.id()).bind(ivaLotNum)
                        .bind(9) // state
                        .bind(ivaLineNum).bind(ivaAssetId)
                        .bind(10) // limit
                        .bind(ivaId);
                        logger.entry("debug") << "[Server] calc done.";
                        transactionCalcul.commit();
                    }
                    catch (Wt::Dbo::Exception const& e)
                    {
                        logger.entry("error") << "[Server] Wt::Dbo: " << e.what();
                        continue;
                    }   
                }
                else
                {
                    logger.entry("error") << "[Server] no real calculate";
                }
            }
            else
            {
                logger.entry("debug") << "[Server] no calculate";
            }
        }

        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCalculate));
    }

    logger.entry("info") << "[Server] Mode Calculator stop";
}

