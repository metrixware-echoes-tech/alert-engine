#include "Parser.h"
#include "AlertProcessor.h"
#include <stdlib.h>
#include <stdio.h>
#include <Wt/Dbo/Dbo>
#include <tools/Session.h>
#include "ToolsEngine.h"
#include <boost/thread/thread.hpp>


ToolsEngine *te;

void checkNewDatas();
void checkNewAlerts();
void removeOldValues();

Wt::WLogger ToolsEngine::logger;
boost::mutex ToolsEngine::mutex;
//default criticity to log before reading file config : debug = 1 / info = 2 / warning = 3 / secure = 4 / error = 5/ fatal = 6
int ToolsEngine::criticity = 2;

int main()
{  
    ToolsEngine::logger.setFile("/tmp/engine.log");
    //TODO : verif si le dossier n'existe pas le créer
    ToolsEngine::logger.addField("type",false);
    ToolsEngine::logger.addField("datetime",false);
    ToolsEngine::logger.addField("message", true);
    ToolsEngine::logger.configure("-debug");
    
    te = new ToolsEngine();

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

        
    // thread's creation
    boost::thread_group threadsEngine;
    
    // execute the method checkNewDatas() removeOldValues() checkNewAlerts() in parallel
    threadsEngine.create_thread(&checkNewDatas);
//    threadsEngine.create_thread(&checkNewAlerts);
    //threadsEngine.create_thread(&removeOldValues);
 
    // wait the end of the created thread
   threadsEngine.join_all();
    
    return 0;
}

void checkNewDatas()
{
    Parser *parser = new Parser();
    //result
    int res = -1;
    
    while (true)
    {
        long long syslogId[100];
        for (int i = 0 ; i < 100 ; i++)
        {
            syslogId[i] = -1;
        }
        //SQL session
        try
        {
            Wt::Dbo::Transaction transaction0(*(te->sessionParserGlobal));
//            Wt::Dbo::collection<Wt::Dbo::ptr<Syslog> > receivedSyslogCollection = te->sessionParser->find<Syslog>().where("\"SLO_STATE\" = ?) FOR UPDATE ").limit(100).bind("0");
            Wt::Dbo::collection<Wt::Dbo::ptr<Syslog> > receivedSyslogCollection = te->sessionParserGlobal->query<Wt::Dbo::ptr<Syslog> >("SELECT slo FROM \"T_SYSLOG_SLO\" slo WHERE \"SLO_STATE\" = 0 LIMIT 100;");
            
            ToolsEngine::log("debug") << " [Class:main] avant for";
            int idx = 0;
            
            for (Wt::Dbo::collection<Wt::Dbo::ptr<Syslog> > ::const_iterator j = receivedSyslogCollection.begin(); j != receivedSyslogCollection.end(); ++j) 
            {
                syslogId[idx] = j->id();
                idx++;
            }
            transaction0.commit();
        }
        catch(Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:main] data 2 : "<< e.what();
        }   
        
        for (int i = 0 ; i < 100 ; i++)
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
                    te->sessionParserGlobal->execute("UPDATE \"T_SYSLOG_SLO\" SET \"SLO_STATE\" = ? WHERE \"SLO_ID\" = ?").bind(2).bind(syslogId[i]);
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
                    te->sessionParserGlobal->execute("UPDATE \"T_SYSLOG_SLO\" SET \"SLO_STATE\" = ? WHERE \"SLO_ID\" = ?").bind(3).bind(syslogId[i]);
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
            std::string queryString = "DELETE \"T_INFORMATION_VALUE_IVA\""
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
        
        //remove values older than 1 day from t_syslog_slo (duplicated in T_INFORMATION_HISTORICAL_VALUE_IHV)
        try
        {
            Wt::Dbo::Transaction transaction(*(te->sessionOldValues));
            std::string queryString = "DELETE \"T_SYSLOG_SLO\""
                                        " WHERE SLO_STATE != 0"
                                        " AND \"SLO_RCPT_DATE\" < (NOW() - interval '1 day')";
            te->sessionOldValues->execute(queryString);
            transaction.commit();
        }
        catch(Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:main] "<< e.what();
        }
        
        boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadRemoveOldValues));
    };
}