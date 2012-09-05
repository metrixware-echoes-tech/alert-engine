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

Wt::WLogger ToolsEngine::logger;

int main()
{  
    ToolsEngine::logger.setFile("/tmp/engine.log");
    ToolsEngine::logger.addField("type",false);
    ToolsEngine::logger.addField("datetime",false);
    ToolsEngine::logger.addField("message", true);
    
    te = new ToolsEngine();

    //création des tables de la bdd (to remove)    
    try 
        {
            te->sessionParser->createTables();
            std::cerr << "Created database." << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Using existing database";
        }

        
    // thread's creation
    boost::thread_group threadsEngine;
    
    // execute the method checkNewDatas() et checkNewAlerts() in parallel
    threadsEngine.create_thread(&checkNewDatas);
    threadsEngine.create_thread(&checkNewAlerts);
 
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
        //SQL session
        {
            Wt::Dbo::Transaction transaction(*(te->sessionParser));
            Wt::Dbo::ptr<Syslog> receivedSyslog = te->sessionParser->find<Syslog>().where("\"SLO_STATE\" = ?").limit(1).bind("0");
            if (receivedSyslog )
            {
                // state is 0 is "new entry" state = 1 is "processing"
                receivedSyslog.modify()->state = 1;
                try
                {
                    res = parser->unserializeStructuredData(receivedSyslog);
                    if (res == 0)
                    {
                        //state = 2 is "processing complete"
                        receivedSyslog.modify()->state = 2;                     
                    }
                    else if ( res == -1)
                    {
                        //state = 3 is "error"
                        receivedSyslog.modify()->state = 3;
                    }
                }
                catch (Wt::Dbo::Exception e)
                {   
                        ToolsEngine::log("info") << " [Class:main] "<< e.what();
                }      
            }

        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadCheckAlertMilliSec));
    };
}

void checkNewAlerts()
{
    AlertProcessor alertProcessor;
    alertProcessor.VerifyAlerts();
}