#include "Parser.h"
#include "AlertProcessor.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <Wt/Dbo/Dbo>
#include <tools/Session.h>
#include "ToolsEngine.h"
 
void* checkNewDatas(void* data);
void* checkNewAlerts(void* data);

Session ToolsEngine::sessionParser("hostaddr=172.16.3.101 port=5432 dbname=echoes user=echoes password=toto");
Session ToolsEngine::sessionAlertProcessor("hostaddr=172.16.3.101 port=5432 dbname=echoes user=echoes password=toto");
Wt::WLogger ToolsEngine::logger;

int main()
{
   /* Parser a;
    std::string toto;
    toto.assign("[prop@5875 ver=1 probe=12][res2@5875 offset=15 81-4-15-6-2=\"543\" 8-4-51-6-1=\"54546\"][res1@5875 offset=75 844-4-5-456-2=\"129873\" 8-445-5-645-1=\"pojl\"]");
    a.unserializeStructuredData(toto); */
    
    ToolsEngine::logger.setFile("/tmp/engine.log");
    
    // thread's creation
    pthread_t threadCheckNewDatas;
    pthread_t threadCheckNewAlerts;
    
    // execute the method checkNewDatas() et checkNewAlerts() in parallel
    pthread_create(&threadCheckNewDatas, NULL, checkNewDatas, NULL);
    pthread_create(&threadCheckNewAlerts, NULL, checkNewAlerts, NULL);    
 
    // wait the end of the created thread
    pthread_join(threadCheckNewDatas, NULL);
    pthread_join(threadCheckNewAlerts, NULL);
    
    return 0;
}

void* checkNewDatas(void* data)
{
    Parser parser ;
    //result
    int res = -1;
    
    while (true)
    {
        //SQL session
        {
            Wt::Dbo::Transaction transaction(ToolsEngine::sessionParser);
            Wt::Dbo::ptr<Syslog> receivedSyslog = ToolsEngine::sessionParser.find<Syslog>().where("\"SLO_STATE\" = ?").limit(1).bind("0");
            if (receivedSyslog )
            {
                // state is 0 is "new entry" state = 1 is "processing"
                receivedSyslog.modify()->state = 1;
                try
                {
                    res = parser.unserializeStructuredData(receivedSyslog);
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
        sleep(1);
    };
}

void* checkNewAlerts(void*)
{
    AlertProcessor alertProcessor;
    alertProcessor.VerifyAlerts();
}