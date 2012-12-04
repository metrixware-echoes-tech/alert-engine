#include "Parser.h"
#include "AlertProcessor.h"
#include <stdlib.h>
#include <stdio.h>
#include <Wt/Dbo/Dbo>
#include <tools/Session.h>
#include "ToolsEngine.h"
#include <boost/thread/thread.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>


ToolsEngine *te;

void checkNewDatas();
void checkNewAlerts();
void removeOldValues();
void calculate();
void cleanAll();

Wt::WLogger ToolsEngine::logger;
boost::mutex ToolsEngine::mutex;
boost::mutex ToolsEngine::mutexCalculate;
//default criticity to log before reading file config : debug = 1 / info = 2 / warning = 3 / secure = 4 / error = 5/ fatal = 6
int ToolsEngine::criticity = 1;

int main(int argc, char *argv[])
{  
    // Declare the supported options.
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "That is where you are, it displays help and quits.")
        ("logfile", boost::program_options::value<std::string>(), "logfile path")
        ("logcriticity", boost::program_options::value<int>(), "log criticity level : debug = 1 / info = 2 / warning = 3 / secure = 4 / error = 5/ fatal = 6")
        ("conffile", boost::program_options::value<std::string>(), "conffile path")
    ;

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);    
    std::string confFile = "engine.conf";
    
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    if (vm.count("logfile")) 
    {
        ToolsEngine::logger.setFile(vm["logfile"].as<std::string>());
    } 
    else 
    {
        ToolsEngine::logger.setFile("/tmp/engine.log");
    }
    
    if (vm.count("logcriticity")) 
    {
        ToolsEngine::criticity = vm["logcriticity"].as<int>();
    } 
    std::cout << "INFO: log criticity = " << ToolsEngine::criticity << "\n"; 
    
    if (vm.count("conffile")) 
    {
        confFile = vm["conffile"].as<std::string>();
    } 
    std::cout << "INFO: conf file = " << confFile << "\n"; 

    
    /* Daemonization */
    #ifdef NDEBUG
        if(chdir("/") != 0)
        {
            std::cerr << "failed to reach root \n";
            return EXIT_FAILURE;
        }
        if(fork() != 0)
            exit(EXIT_SUCCESS);
        setsid();
        if(fork() != 0)
            exit(EXIT_SUCCESS);
    #endif
    
    
    //TODO : verif si le dossier n'existe pas le créer
    ToolsEngine::logger.addField("type",false);
    ToolsEngine::logger.addField("datetime",false);
    ToolsEngine::logger.addField("message", true);
    ToolsEngine::logger.configure("-debug");
    
    te = new ToolsEngine(confFile);
    

    //création des tables de la bdd (to remove)    
    try 
    {
        te->sessionParser->createTables();
        Wt::Dbo::Transaction transaction(*(te->sessionParser));
        ToolsEngine::log("debug") << " [Class:Main] " << "Created database.";
        te->sessionParser->execute(
                  "CREATE OR REPLACE FUNCTION trg_slo_slh()"
                  "  RETURNS trigger AS"
                  " $BODY$"
                  " BEGIN"
                  " INSERT INTO \"T_SYSLOG_HISTORY_SLH\" "
                  " VALUES (NEW.\"SLO_ID\","
                      "NEW.\"version\","
                      "NEW.\"SLO_APP_NAME\","
                      "NEW.\"SLO_HOSTNAME\","
                      "NEW.\"SLO_MSG_ID\","
                      "NEW.\"SLO_SD\","
                      "NEW.\"SLO_DELETE\","
                      "NEW.\"SLO_RCPT_DATE\","
                      "NEW.\"SLO_SENT_DATE\","
                      "NEW.\"SLO_PRI\","
                      "NEW.\"SLO_PROC_ID\","
                      "NEW.\"SLO_STATE\","
                      "NEW.\"SLO_VERSION\","
                      "NEW.\"SLO_PRB_PRB_ID\") ;"
                  " RETURN NULL;"
                  " END;"
                  " $BODY$"
                    " LANGUAGE plpgsql VOLATILE;"
        );
        te->sessionParser->execute(
                    "CREATE TRIGGER insert_slo"
                    " AFTER INSERT"
                    " ON \"T_SYSLOG_SLO\""
                    " FOR EACH ROW"
                    " EXECUTE PROCEDURE trg_slo_slh();"
        );
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        ToolsEngine::log("info") << " [Class:Main] " << "Using existing database." << e.what();
    }
    
    cleanAll();
        
    // thread's creation
    boost::thread_group threadsEngine;
    
    // execute the method checkNewDatas() removeOldValues() checkNewAlerts() in parallel
    if (te->isParser())
    {
        threadsEngine.create_thread(&checkNewDatas);
    }
    if (te->isAlerter())
    {
        threadsEngine.create_thread(&checkNewAlerts);
    }
    if (te->isCleaner())
    {
        threadsEngine.create_thread(&removeOldValues);
    }
    if (te->isCalculator())
    {
        threadsEngine.create_thread(&calculate);
    }
    
    // wait the end of the created thread
    threadsEngine.join_all();
    
    return 0;
}

void checkNewDatas()
{
    Parser *parser = new Parser();
    //result
    int res = -1;
    int syslogSize = 50;
    while (true)
    {
        long long syslogId[syslogSize];
        for (int i = 0 ; i < syslogSize ; i++)
        {
            syslogId[i] = -1;
        }
        //SQL session
        try
        {
            Wt::Dbo::Transaction transaction0(*(te->sessionParserGlobal));
//            Wt::Dbo::collection<Wt::Dbo::ptr<Syslog> > receivedSyslogCollection = te->sessionParser->find<Syslog>().where("\"SLO_STATE\" = ?) FOR UPDATE ").limit(100).bind("0");
            Wt::Dbo::collection<Wt::Dbo::ptr<Syslog> > receivedSyslogCollection = 
                    te->sessionParserGlobal->query<Wt::Dbo::ptr<Syslog> >(
                    "SELECT slo FROM \"T_SYSLOG_SLO\" slo WHERE \"SLO_STATE\" = 0 FOR UPDATE LIMIT ?"
                    ).bind(syslogSize);
            
            ToolsEngine::log("debug") << " [Class:main] avant for";
            int idx = 0;
            
            for (Wt::Dbo::collection<Wt::Dbo::ptr<Syslog> > ::const_iterator j = receivedSyslogCollection.begin(); j != receivedSyslogCollection.end(); ++j) 
            {
                te->sessionParserGlobal->execute("UPDATE \"T_SYSLOG_SLO\" SET \"SLO_STATE\" = ? WHERE \"SLO_ID\" = ?").bind(1).bind(j->id());
                syslogId[idx] = j->id();
                idx++;
            }
            transaction0.commit();
        }
        catch(Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:main] data 2 : "<< e.what();
        }   
        
        for (int i = 0 ; i < syslogSize ; i++)
        {
            ToolsEngine::log("debug") << " [Class:main] boucle syslog, i : " << i << " id : " << syslogId[i];
            if (syslogId[i] == -1)
            {
                break;
            }

            res = parser->unserializeStructuredData(syslogId[i]);

            if (res == 0)
            {
                //state = 2 is "processing complete"
                try
                {
                    Wt::Dbo::Transaction transaction(*(te->sessionParserGlobal));
                    te->sessionParserGlobal->execute("SELECT slo FROM \"T_SYSLOG_SLO\" slo WHERE \"SLO_ID\" = ? FOR UPDATE").bind(syslogId[i]);
                    te->sessionParserGlobal->execute("UPDATE \"T_SYSLOG_SLO\" SET \"SLO_STATE\" = ? WHERE \"SLO_ID\" = ?").bind(2).bind(syslogId[i]);
                    te->sessionParserGlobal->execute("UPDATE \"T_SYSLOG_HISTORY_SLH\" SET \"SLH_STATE\" = ? WHERE \"SLH_ID\" = ?").bind(2).bind(syslogId[i]);
                    te->sessionParserGlobal->execute("DELETE FROM \"T_SYSLOG_SLO\" WHERE \"SLO_ID\" = ?").bind(syslogId[i]);
//                    Wt::Dbo::ptr<Syslog> ptrSyslog = te->sessionParserGlobal->find<Syslog>().where("\"SLO_ID\" = ?").bind(syslogId[i]).limit(1);
//                    ptrSyslog.modify()->state = 2;
                    transaction.commit();
                }
                catch (Wt::Dbo::Exception e)
                {   
                        ToolsEngine::log("error") << " [Class:main] data 1.1 : "<< e.what() << " || res = " << res << " || id syslog : " << syslogId[i];
                }      
            }
            else if ( res == -1)
            {
                //state = 3 is "error"
                try
                {
                    Wt::Dbo::Transaction transaction(*(te->sessionParserGlobal));
                    te->sessionParserGlobal->execute("SELECT slo FROM \"T_SYSLOG_SLO\" slo WHERE \"SLO_ID\" = ? FOR UPDATE").bind(syslogId[i]);
                    te->sessionParserGlobal->execute("UPDATE \"T_SYSLOG_SLO\" SET \"SLO_STATE\" = ? WHERE \"SLO_ID\" = ?").bind(3).bind(syslogId[i]);
                    te->sessionParserGlobal->execute("UPDATE \"T_SYSLOG_HISTORY_SLH\" SET \"SLH_STATE\" = ? WHERE \"SLH_ID\" = ?").bind(3).bind(syslogId[i]);
                    te->sessionParserGlobal->execute("DELETE FROM \"T_SYSLOG_SLO\" WHERE \"SLO_ID\" = ?").bind(syslogId[i]);
//                    Wt::Dbo::ptr<Syslog> ptrSyslog = te->sessionParserGlobal->find<Syslog>().where("\"SLO_ID\" = ?").bind(syslogId[i]).limit(1);
//                    ptrSyslog.modify()->state = 3;
                    transaction.commit();
                }
                catch (Wt::Dbo::Exception e)
                {   
                        ToolsEngine::log("error") << " [Class:main] data 1.2 : "<< e.what() << " || res = " << res << " || id syslog : " << syslogId[i];
                } 
            }
            
        }
        
        boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadReadDatasMilliSec));
    };
}

void checkNewAlerts()
{
    AlertProcessor *alertProcessor = new AlertProcessor();
    alertProcessor->verifyAlerts();
}

void removeOldValues()
{
    while (true)
    {
        cleanAll();
        boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadRemoveOldValues));
    };
}

void cleanAll()
{
    //change the status for old values to avoid to send alert on old data
    try
    {
        Wt::Dbo::Transaction transaction(*(te->sessionOldValues));
        std::string queryString = "UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = 4 WHERE"
                                    " \"IVA_STATE\" = 0"
                                    " AND \"IVA_CREA_DATE\" < (NOW() - interval '1 hour')";
        te->sessionOldValues->execute(queryString);
        transaction.commit();
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:main] "<< e.what();
    }

    //remove values older than 1 day from information_value (duplicated in T_INFORMATION_HISTORICAL_VALUE_IHV)
    try
    {
        Wt::Dbo::Transaction transaction(*(te->sessionOldValues));
        std::string queryString = "DELETE FROM \"T_INFORMATION_VALUE_IVA\""
                                    " WHERE"
                                    " \"IVA_STATE\" = 0"
                                    " AND \"IVA_CREA_DATE\" < (NOW() - interval '1 day')";
        te->sessionOldValues->execute(queryString);
        transaction.commit();
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:main] "<< e.what();
    }

    //remove values older than 1 day from t_syslog_slo
    try
    {
        Wt::Dbo::Transaction transaction(*(te->sessionOldValues));
        std::string queryString = "DELETE FROM \"T_SYSLOG_SLO\""
                                    " WHERE \"SLO_STATE\" != 0"
                                    " AND \"SLO_RCPT_DATE\" < (NOW() - interval '1 day')";
        te->sessionOldValues->execute(queryString);
        transaction.commit();
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:main] "<< e.what();
    }
}

void calculate()
{
    int ivaListSize = 1;
    while (true)
    {
        long long ivaId[ivaListSize];
        for (int i = 0 ; i < ivaListSize ; i++)
        {
            ivaId[i] = -1;
        }
        try
        {
            Wt::Dbo::Transaction transaction1(*(te->sessionCalculate));
            // we get iva values where state = ToBeCalculate
            std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
                    " WHERE \"IVA_STATE\" = 9 FOR UPDATE LIMIT ?";
            Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > ivaList = 
                    te->sessionCalculate->query<Wt::Dbo::ptr<InformationValue> >(queryString).bind(ivaListSize);
            
            int idx = 0;
            for (Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> >::const_iterator j = ivaList.begin(); j != ivaList.end(); ++j) 
            {
                te->sessionCalculate->execute(
                            "UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = ? WHERE \"IVA_ID\" = ?"
                            ).bind(1).bind(j->id());
                ivaId[idx] = j->id();
                idx++;
            }
            transaction1.commit();
        }
        catch(Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:main] iva selection : "<< e.what();
        }
        
        
        try
        {
//            te->sessionCalculate->~Session();
            for (int i = 0 ; i < ivaListSize; i++)
            {
                te->reloadSessionCalculate();
                Wt::Dbo::Transaction transaction2(*(te->sessionCalculate));
                
                if (ivaId[i] == -1)
                {
                    break;
                }


                std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva WHERE \"IVA_ID\" = ? LIMIT 1";
                Wt::Dbo::ptr<InformationValue> ptrIva = 
                        te->sessionCalculate->query<Wt::Dbo::ptr<InformationValue> >(queryString).bind(ivaId[i]);

                // we get the information related to the iva
                Wt::Dbo::ptr<Information2> ptrInfTmp = ptrIva->information;
                Wt::Dbo::ptr<Information2> *ptrInfRes = new Wt::Dbo::ptr<Information2>();
                if (ptrInfTmp.get()->calculate)
                {
                    if (!ptrInfTmp.get()->calculate.get().empty())
                    {
                        ToolsEngine::log("debug") << " [Class:Main] " << "calculate value : " << ptrInfTmp.get()->calculate;
                        if (ptrInfTmp.get()->calculate.get() == "searchValueToCalculate")
                        {
//                            *ptrInfRes = te->sessionCalculate->find<Information2>()
//                                    .where("\"PLG_ID_PLG_ID\" = ?").bind(
//                                                          ptrInfTmp.get()->pk.search.get()->pk.source.get()->pk.plugin.id())
//                                    .where("\"SRC_ID\" = ?").bind(ptrInfTmp.get()->pk.search.get()->pk.source.get()->pk.id)
//                                    .where("\"SEA_ID\" = ?").bind(ptrInfTmp.get()->pk.search.get()->pk.id)
//                                    .where("\"INF_VALUE_NUM\" = ?").bind(-1).limit(1);
                            std::string queryString = "select inf from \"T_INFORMATION_INF\" inf where (\"PLG_ID_PLG_ID\" = ?) and (\"SRC_ID\" = ?) and (\"SEA_ID\" = ?) and (\"INF_VALUE_NUM\" = ?)";
                            *ptrInfRes = te->sessionCalculate->query<Wt::Dbo::ptr<Information2> >(queryString)
                                    .bind(ptrInfTmp->pk.search->pk.source->pk.plugin.id())
                                    .bind(ptrInfTmp->pk.search->pk.source->pk.id)
                                    .bind(ptrInfTmp->pk.search->pk.id)
                                    .bind(-1)
                                    .limit(1);
                        }
                        else
                        {
                            *ptrInfRes = ptrInfTmp;
                        }
                    }
                }
                else
                {
                    ToolsEngine::log("error") << " [Class:Main] " << "no calculate";
                    break;
                }
                
                
                ToolsEngine::log("debug") << " [Class:Main] " << "launching calcul" ;
                // We launch the calcul
                //Wt::Dbo::ptr<InformationValue> ptrIva = te->sessionCalculate->find<InformationValue>().where("\"IVA_ID\" = ?").bind(ivaId[i]);

                if ((ptrIva.id() != -1) && (*ptrInfRes) && (ptrInfTmp))
                {
                    std::string queryStr = "SELECT " + ptrInfRes->get()->calculate.get().toUTF8() + "(" + boost::lexical_cast<std::string>(ptrInfRes->get()->pk.search->pk.id)
                                        + "," + boost::lexical_cast<std::string>(ptrInfTmp->pk.search->pk.source->pk.id)
                                        + "," + boost::lexical_cast<std::string>(ptrInfTmp->pk.search->pk.source->pk.plugin.id())
                                        + "," + boost::lexical_cast<std::string>(ptrInfTmp->pk.subSearchNumber)
                                        + "," + boost::lexical_cast<std::string>(ptrInfTmp->pk.unit.id())
                                        + "," + boost::lexical_cast<std::string>(ptrIva->lotNumber)
                                        + ",9" //state
                                        + "," + boost::lexical_cast<std::string>(ptrIva->lineNumber)
                                        + "," + boost::lexical_cast<std::string>(ptrIva->asset.id())
                                        + ",10" // limit
                                        + "," + boost::lexical_cast<std::string>(ptrIva.id())
                                        + ")"
                                        ;
                    ToolsEngine::log("debug") << " [Class:Main] calc query : " << queryStr;
                    te->sessionCalculate->execute(queryStr);
                    ToolsEngine::log("debug") << " [Class:Main] calc done.";
                }
                else
                {
                    ToolsEngine::log("error") << " [Class:Main] " << "IVA not found. Id : " + ivaId[i] ;
                } 
//                ptrInfRes->~ptr();
//                ptrInfTmp.~ptr();
//                ptrIva.~ptr();
                transaction2.commit();
            }
        }
        catch(Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:Main:Dbo] calculation : "<< e.what();
        }
        catch(boost::bad_lexical_cast e)
        {
            ToolsEngine::log("error") << " [Class:Main:Boost] calculation : "<< e.what();
        }
   
                

        boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadCalculate));   
    }
}