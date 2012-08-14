#include "AlertProcessor.h"

AlertProcessor::AlertProcessor() {
}

AlertProcessor::~AlertProcessor() {
}

int AlertProcessor::VerifyAlerts()
{
typedef Wt::Dbo::collection< Wt::Dbo::ptr<Alert> > Alerts;
boost::thread_group threadsVerifyAlerts;
//int threadNumber=0;
//std::vector<pthread_t> threadList;
    boost::mutex::scoped_lock scoped_lock(mutex);
    //SQL session
    {
        Wt::Dbo::Transaction transaction(ToolsEngine::sessionAlertProcessor);        

        //we get the list of all defined alerts in the database
        Alerts alerts = ToolsEngine::sessionAlertProcessor.find<Alert>();
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << "We have " << alerts.size() << " Alert(s) in the database\n\n";

        for (Alerts::const_iterator i = alerts.begin(); i != alerts.end(); ++i)
        {
           ToolsEngine::log("info") << " [Class:AlertProcessor] " << " the Alert : " << (*i)->name << " is in the database. \n";
           //we instanciate a thread for each alert           
           //this : instance de la classe (l'objet lui même) dans laquelle est exécuté bind()
           threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::InformationValueLoop,this,*i));
        }
        threadsVerifyAlerts.join_all();
    }
return 0;
}

void AlertProcessor::InformationValueLoop(Wt::Dbo::ptr<Alert> alertPtr)
{
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " the Alert : " << alertPtr->name << " from information value loop. \n";
    
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert informations: type : " << alertPtr->alertType->name << "\n";
    
//    boost::mutex::scoped_lock scoped_lock(mutex);
    //SQL session
//    {
//        Wt::Dbo::Transaction transaction(ToolsEngine::sessionAlertProcessor);        
//
//        //we get the type of the alert and the params to build de comparison process
//        if (alertPtr->alertType->name == "threshold")
//        {
//            alertPtr.get()->alertType.get()->alertCriterias.get()->
//        }
//        Alerts alerts = ToolsEngine::sessionAlertProcessor.find<Alert>();
//    }
    
} 

/*
typedef std::vector<int>::iterator iterator ;
thg.create_thread(boost::bind(static_cast<void(*)(vector<int>::iterator,vector<int>::iterator)>(sort<vector<int>::iterator>), mass.begin(), mass.end()));

typedef Wt::Dbo::collection< Wt::Dbo::ptr<Alert> > Alerts;
threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::InformationValueLoop,i));*/