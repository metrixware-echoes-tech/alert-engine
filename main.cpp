#include "Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <Wt/Dbo/Dbo>
#include <tools/Session.h>
#include "ToolsEngine.h"
 
void* checkNewDatas(void* data);

Session ToolsEngine::session("hostaddr=127.0.0.1 port=5432 dbname=echoes user=echoes password=toto");
Wt::WLogger ToolsEngine::logger;

int main()
{
   /* Parser a;
    std::string toto;
    toto.assign("[prop@5875 ver=1 probe=12][res2@5875 offset=15 81-4-15-6-2=\"543\" 8-4-51-6-1=\"54546\"][res1@5875 offset=75 844-4-5-456-2=\"129873\" 8-445-5-645-1=\"pojl\"]");
    a.unserializeStructuredData(toto); */
    
    ToolsEngine::logger.setFile("/tmp/engine.log");
    
    // On crée un thread
    pthread_t thread;
    
    // Permet d'exécuter le fonction maFonction en parallèle
    pthread_create(&thread, NULL, checkNewDatas, NULL);
 
    // Attend la fin du thread créé
    pthread_join(thread, NULL);
      
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
            Wt::Dbo::Transaction transaction(ToolsEngine::session);
            Wt::Dbo::ptr<Syslog> receivedSyslog = ToolsEngine::session.find<Syslog>().where("\"SLO_STATE\" = ?").limit(1).bind("0");
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