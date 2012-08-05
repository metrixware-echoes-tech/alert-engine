#include "Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <Wt/Dbo/Dbo>
#include <tools/Session.h>
#include "ToolsEngine.h"
 
void* checkNewDatas(void* data);

Session ToolsEngine::session;

int main()
{
   /* Parser a;
    std::string toto;
    toto.assign("[prop@5875 ver=1 probe=12][res2@5875 offset=15 81-4-15-6-2=\"543\" 8-4-51-6-1=\"54546\"][res1@5875 offset=75 844-4-5-456-2=\"129873\" 8-445-5-645-1=\"pojl\"]");
    a.unserializeStructuredData(toto); */
    
    
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
    
    //SQL session
    {
        Wt::Dbo::Transaction transaction(ToolsEngine::session);
        Wt::Dbo::ptr<Syslog> receivedSyslog = ToolsEngine::session.find<Syslog>().where("\"SLO_STATE\" = ?").limit(1).bind("0");
        if (receivedSyslog )
        {
            receivedSyslog.modify()->state = 1;
            parser.unserializeStructuredData(receivedSyslog);
        }

    }
}