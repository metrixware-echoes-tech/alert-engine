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

#include <Wt/WApplication>

#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/Json/Array>
#include <Wt/Json/Object>

#include <Wt/Http/Client>
#include <Wt/WIOService>
#include "Server.h"

using namespace std;

int Server::m_signum = 0;
boost::thread_group Server::m_threads;

Server::Server(const string& name, const string& version) :
m_optionsOK(false),
m_name(name),
m_version(version),
m_pidPath("/var/run/ea-engine.pid"),
m_session()
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
        log("info") << "[origin enterpriseId=\"40311\" software=\"" << m_name << "\" swVersion=\"" << m_version << "\"] (re)start";

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
            log("error") << m_pidPath << ": " << strerror(errno);
        }
        else
        {
            pidFile << getpid() << std::endl;
        }
#endif

        if (conf.readConfFile())
        {
            m_session.initConnection(conf.getSessConnectParams());
            
            if (conf.isInDB(m_session))
            {
                if (conf.isCleaner())
                {
                    m_threads.create_thread(boost::bind(&Server::removeOldValues, this));
                }
                else
                {	
                    log("info") << "Mode Cleaner disabled";
                }
                if (conf.isAlerter())
                {
                    m_threads.create_thread(boost::bind(&Server::checkNewAlerts, this));
                }
                else
                {
                    log("info") << "Mode Alerter disabled";
                }
                if (conf.isCalculator())
                {
                    m_threads.create_thread(boost::bind(&Server::calculate, this));
                }
                else
                {
                    log("info") << "Mode Calculator disabled";
                }
                if (conf.isCalculator())
                {
                    m_threads.create_thread(boost::bind(&Server::checkProbes, this));
                }
                else
                {
                    log("info") << "Mode Probe Checker disabled";
                }
                res = true;
            }
            else
            {
                log("error") << "This Engine ID is not in the database.";
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
        log("error") << m_pidPath << ": " << strerror(errno);
    }
#endif
    log("info") << "[origin enterpriseId=\"40311\" software=\"" << m_name << "\" swVersion=\"" << m_version << "\"] stop";
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

void Server::checkProbes()
{
    while (m_signum == 0)
    {
        log("info") << "Checking probes";
        
        map<long long,Wt::WString> enoIdTokens;

        try
        {
            Wt::Dbo::Transaction transaction(m_session,true);
            
            Wt::Dbo::ptr<Echoes::Dbo::Engine> pEng = m_session.find<Echoes::Dbo::Engine>()
                .where(QUOTE(TRIGRAM_ENGINE ID)" = ?").bind(conf.getId())
                .limit(1);
            
            Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Probe>> cPrb = m_session.find<Echoes::Dbo::Probe>()
                .where(QUOTE(TRIGRAM_PROBE SEP "ALERT_IF_DOWN") " IS TRUE")
                .where(QUOTE(TRIGRAM_PROBE SEP "DELETE") " IS NULL");

            for (const Wt::Dbo::ptr<Echoes::Dbo::Probe> &prb : cPrb)
            {
                Wt::Dbo::ptr<Echoes::Dbo::EngGrp> egpPtr = m_session.find<Echoes::Dbo::EngGrp>()
                                   .where(QUOTE(TRIGRAM_ENGINE ID SEP TRIGRAM_ENGINE ID)" = ?").bind(pEng.id())
                                   .where(QUOTE(TRIGRAM_GROUP ID SEP TRIGRAM_GROUP ID)" = ?").bind(prb->asset->group.id())
                                   .where(QUOTE(TRIGRAM_ENG_GRP SEP "DELETE")" IS NULL")
                                   .limit(1);
                
                if (egpPtr)
                {
                    enoIdTokens[prb.id()] = egpPtr->token;
                }
                
            }
            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            log("error") << "Wt::Dbo: " << e.what();
        }

        vector<string> parameterList;        
        for (auto it = enoIdTokens.begin() ; it != enoIdTokens.end(); ++it)
        {
            boost::function<void (Wt::Json::Value)> functorIsProbeAlive = boost::bind(&Server::isProbeAlive, this, _1); 
            sendHttpRequestGet("probes/"+ boost::lexical_cast<string>(it->first) +"/alive", parameterList, functorIsProbeAlive, it->second);    
        }
        
        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCheckProbes));
    }
}

void Server::isProbeAlive(Wt::Json::Value result)
{
       

    bool informationsGet = false;
    
    int id = -1;
    bool heartbeat = false;
    try
    {
        if(result.type() == Wt::Json::ObjectType)
        {
            Wt::Json::Object& jsonObject = result;
            if(jsonObject.contains("probe_heartbeat")
                    && jsonObject.contains("id"))
            {
                heartbeat = jsonObject.get("probe_heartbeat");
                id = jsonObject.get("id");
                informationsGet = true;
            }
        }
        else
        {
            log("error") << "missing parameters or unsafe format";
        }

    }
    catch(Wt::Json::ParseError e)
    {
        
    }
    if (informationsGet && !heartbeat)
    {
        bool sendAlert = false;
        Wt::WString probeName;
        long long mediaId;
        Wt::WString enoToken;
        try
        {
            Wt::Dbo::Transaction transaction(m_session,true);
            
            Wt::Dbo::ptr<Echoes::Dbo::Engine> pEng = m_session.find<Echoes::Dbo::Engine>()
                .where(QUOTE(TRIGRAM_ENGINE ID)" = ?").bind(conf.getId())
                .limit(1);
            
            Wt::Dbo::ptr<Echoes::Dbo::Probe> pPrb = m_session.find<Echoes::Dbo::Probe>()
                   .where(QUOTE(TRIGRAM_PROBE ID)" = ?").bind(id)
                   .limit(1);
            
            Wt::Dbo::ptr<Echoes::Dbo::EngGrp> egpPtr = m_session.find<Echoes::Dbo::EngGrp>()
                                   .where(QUOTE(TRIGRAM_ENGINE ID SEP TRIGRAM_ENGINE ID)" = ?").bind(pEng.id())
                                   .where(QUOTE(TRIGRAM_GROUP ID SEP TRIGRAM_GROUP ID)" = ?").bind(pPrb->asset->group.id())
                                   .where(QUOTE(TRIGRAM_ENG_GRP SEP "DELETE")" IS NULL")
                                   .limit(1);
            
            
            Wt::WDateTime lastAlert = pPrb->lastDownAlert;
            Wt::WDateTime lastLog = pPrb->lastlog;
            Wt::WDateTime now = Wt::WDateTime::currentDateTime();
            int timeToWaitBeforeAlerting = pPrb->snoozeBeforeNextWarning;
            
            // Si le dernier log est après la dernière alerte 
            // et que le heartbeat est false (condition qui nous permet d'arriver ici))
            // OU qu'on a dépassé le délais depuis la dernière alerte
            // OU qu'aucune alerte n'a jamais été envoyée
            // On passe sendAlert à true.
            if ((lastLog.secsTo(lastAlert) < 0) || ((lastAlert.secsTo(now)) > timeToWaitBeforeAlerting) || lastAlert.isNull()) 
            {
                probeName = pPrb->name;
                mediaId = pPrb->asset->group->defaultMedia.id();
                enoToken = egpPtr->token;
                sendAlert = true;
                pPrb.modify()->lastDownAlert = Wt::WDateTime::currentDateTime();
            }
            
            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            log("error") << "Wt::Dbo: " << e.what();
        }
        
        if (sendAlert)
        {
            Wt::Http::Message *message = new Wt::Http::Message();
            message->addBodyText("{");
            message->addBodyText("\n\"message\": \"Probe down : " + probeName.toUTF8() + "\"");
            message->addBodyText(",\n\"media_id\": " + boost::lexical_cast<string>(mediaId));
            message->addBodyText("\n}");
            sendHttpRequestPost("messages", message, enoToken); 
        }
    }
    
}


void Server::checkNewAlerts()
{
    AlertProcessor alertProcessor(m_session);
    log("info") << "Mode Alerter start";

    alertProcessor.verifyAlerts(&m_signum);
}

void Server::removeOldValues()
{
    log("info") << "Mode Cleaner start";

    while (m_signum == 0)
    {
        log("info") << "Cleaning of IVA Table";
        
        //remove values older than 1 day from information_value (duplicated in T_INFORMATION_HISTORICAL_VALUE_IHV)
        try
        {
            Wt::Dbo::Transaction transaction(m_session, true);
            const string queryString = "DELETE FROM \"T_INFORMATION_VALUE_IVA\""
                    " WHERE"
                    " \"IVA_CREA_DATE\" < (NOW() - interval '1 day')";
            m_session.execute(queryString);
            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            log("error") << "Wt::Dbo: " << e.what();
        }
        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadRemoveOldValues));
    }

    log("info") << "Mode Cleaner stop";
}

void Server::calculate()
{
    const int ivaListSize = 50;

    log("info") << "Mode Calculator start";

    while (m_signum == 0)
    {
        vector<long long> ivaIdList;

        try
        {
            Wt::Dbo::Transaction transaction(m_session, true);
            // we get iva values where state = ToBeCalculate
            string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
                    " WHERE \"IVA_STATE\" = 9 FOR UPDATE LIMIT ?";
            Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>> ivaList = m_session.query<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>>(queryString).bind(ivaListSize);

            for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::InformationValue> >::const_iterator it = ivaList.begin(); it != ivaList.end(); ++it)
            {
                m_session.execute("UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = ? WHERE \"IVA_ID\" = ?").bind(1).bind(it->id());
                ivaIdList.push_back(it->id());
            }

            log("debug") << ivaIdList.size() << " IVA retrieved to calculate";
            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            log("error") << "Wt::Dbo: " << e.what();
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
                Wt::Dbo::Transaction transaction(m_session, true);
                ivaPtr = m_session.find<Echoes::Dbo::InformationValue>()
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
                transaction.commit();
            }
            catch (Wt::Dbo::Exception const& e)
            {
                log("error") << "Wt::Dbo: " << e.what();
                continue;
            }
            
            if(calculate != "")
            {
                //FIXME
                log("debug") << "calculate value: " << calculate;

                if (calculate == "searchValueToCalculate")
                {
                    //we get the calculation data
                    try
                    {
                        Wt::Dbo::Transaction transaction(m_session, true);

                        Wt::Dbo::ptr<Echoes::Dbo::InformationData> ptrInfData = m_session.find<Echoes::Dbo::InformationData>()
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
                        transaction.commit();
                    }
                    catch (Wt::Dbo::Exception const& e)
                    {
                        log("error") << "Wt::Dbo: " << e.what();
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
                        Wt::Dbo::Transaction transaction(m_session, true);
                        log("debug") << "Launch calc query: " << realCalculate;
                        m_session.execute("SELECT " + realCalculate.toUTF8() + "(?, ?, ?, ?, ?, ?, ?)")
                        .bind(ivaPtr->informationData.id()).bind(ivaLotNum)
                        .bind(9) // state
                        .bind(ivaLineNum).bind(ivaAssetId)
                        .bind(10) // limit
                        .bind(ivaId);
                        log("debug") << "calc done.";
                        transaction.commit();
                    }
                    catch (Wt::Dbo::Exception const& e)
                    {
                        log("error") << "Wt::Dbo: " << e.what();
                        continue;
                    }   
                }
                else
                {
                    log("error") << "no real calculate";
                }
            }
            else
            {
                log("debug") << "no calculate";
            }
        }

        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCalculate));
    }

    log("info") << "Mode Calculator stop";
}

string Server::getApiAddress()
{
    string apiAddress;
    apiAddress = "http";
    apiAddress += (conf.isAPIHttps() ? "s" : "");
    apiAddress += "://" + conf.getAPIHost() + ":" + boost::lexical_cast<string>(conf.getAPIPort()) + "/";
    
    return apiAddress;
}

void Server::sendHttpRequestGet(string resource, vector<string> listParameter, boost::function<void (Wt::Json::Value)> functor, Wt::WString enoToken)
{    
    string apiAddress = getApiAddress();
    apiAddress += resource;
    apiAddress += "?eno_token=" + enoToken.toUTF8();

    for(size_t i(0); i<listParameter.size(); i++)
    {
        apiAddress += "&" + listParameter[i];
    }
    
    log("debug") << "[GET] address to call : " << apiAddress;

    Wt::WIOService ioService;
    ioService.start();
    Wt::Http::Client *client = new Wt::Http::Client(ioService);
    //FIXME: Use Wt Server ? Add parameters to the engine ?
    client->setSslCertificateVerificationEnabled(false);
    client->done().connect(boost::bind(&Server::getResourceCallback, this, _1, _2, client, functor));
    if (!client->get(apiAddress))
    {
        log("error") << "[Server][GET] Error Client Http";
    }
}

void Server::sendHttpRequestPost(string resource, Wt::Http::Message *message, Wt::WString enoToken)
{

    string apiAddress = getApiAddress();
    apiAddress += resource;
    apiAddress += "?eno_token=" + enoToken.toUTF8();
    
    Wt::WIOService ioService;
    ioService.start();
    Wt::Http::Client *client = new Wt::Http::Client(ioService);
    //FIXME: Use Wt Server ? Add parameters to the engine ?
    client->setSslCertificateVerificationEnabled(false);
    client->done().connect(boost::bind(&Server::postResourceCallback, this, _1, _2, client));

    if (!client->post(apiAddress, *message))
    {
        log("error") << "[Server][POST] Error Client Http";
    }
}

void Server::postResourceCallback(boost::system::error_code err, const Wt::Http::Message& response, Wt::Http::Client *client)
{
    delete client;
    if (!err)
    {
        if (response.status() == 201)
        {
            try
            {
                Wt::Json::Object result;
                Wt::Json::parse(response.body(), result);
            }
            catch (Wt::Json::ParseError const& e)
            {
                log("warning") << "[Server][POST] Problems parsing JSON: " << response.body();
            }
            catch (Wt::Json::TypeException const& e)
            {
                log("warning") << "[Server][POST] JSON Type Exception: " << response.body();
            }
        }
        else
        {
            log("warning") << "[Server][POST] Unexpected answer : " << response.body();
        }
    }
    else
    {
        log("warning") << "[Server][POST] error : " << err.message();
    }
}


void Server::getResourceCallback(boost::system::error_code err,
    const Wt::Http::Message& response, Wt::Http::Client *client, boost::function<void (Wt::Json::Value)> functor)
{
    delete client;
    
    if (!err)
    {
        if (response.status() == 200)
        {
            try
            {
                Wt::Json::Value result;
                Wt::Json::parse(response.body(), result);
                functor(result);
            }
            catch (Wt::Json::ParseError const& e)
            {
                log("warning") << "[Server] Problems parsing JSON: " << response.body();
            }
            catch (Wt::Json::TypeException const& e)
            {
                log("warning") << "[Server] JSON Type Exception: " << response.body();
            }
        }
        else 
        {
            functor(Wt::Json::Value::Null);
        }
    }
    else
    {
        log("warning") << "[Server] Http::Client get error: " << response.body();
    }
}
