#include "AlertProcessor.h"

AlertProcessor::AlertProcessor() {
}

AlertProcessor::~AlertProcessor() {
}

int AlertProcessor::VerifyAlerts()
{
typedef Wt::Dbo::collection< Wt::Dbo::ptr<Alert> > Alerts;
int threadNumber=0;
//std::vector<pthread_t> threadList;
    
    //SQL session
    {
        Wt::Dbo::Transaction transaction(ToolsEngine::sessionAlertProcessor);
        //we fill the local copy of the syslo pointer with the id of the received syslog
        //ptrSyslogTmp = ToolsEngine::session.find<Syslog>().where("\"SLO_ID\" = ?").bind(ptrSyslog.id());
        //oBracket = ptrSyslogTmp.get()->sd.value().find('[',oBracket+1);
        //cBracket = ptrSyslogTmp.get()->sd.value().find(']',cBracket+1);
        

        //we get the list of all defined alerts in the database
        Alerts alerts = ToolsEngine::sessionAlertProcessor.find<Alert>();
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << "We have " << alerts.size() << " Alert(s) in the database\n\n";

        for (Alerts::const_iterator i = alerts.begin(); i != alerts.end(); ++i)
        {
            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " the Alert : " << (*i)->name << " is in the database. \n";
            
            //we instanciate a thread for each alert
            pthread_t thread = 0;
           // threadList.push_back() = thread;

           Wt::Dbo::ptr<Alert> toto = *i;
           const Alert *alert = toto.get();
            // we execute the checkNewDatas method in the thread
            pthread_create(&thread, NULL, AlertProcessor::InformationValueLoop, (void*) alert);

            // wait the end of the created thread
            pthread_join(thread, NULL);

        }
    
    }
return 0;
}

void* AlertProcessor::InformationValueLoop(void* arg)
{
    Alert *alertPtr = arg;
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " the Alert : " << alertPtr->name << " from information value loop. \n";
    pthread_exit(NULL);
}