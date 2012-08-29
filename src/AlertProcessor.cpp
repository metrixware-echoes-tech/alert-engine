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
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << "We have " << alerts.size() << " Alert(s) in the database";

        for (Alerts::const_iterator i = alerts.begin(); i != alerts.end(); ++i)
        {
           ToolsEngine::log("info") << " [Class:AlertProcessor] " << " the Alert : " << (*i)->name << " is in the database.";
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
    //creation of a new SQL session
    Session sessionThread(ToolsEngine::sqlCredentials);
    
    // creation of a criteria and an information unit type enum
    criteria alertCriterias;
    informationUnitType alertTypes;
    
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " New Thread created, the Alert : " << alertPtr->name << " is now proccesed by the engine.";
    
    int alertId;
    
    //id of the plugin concerned by the alert            
    int pluginId;            
    //id of the source concerned by the alert
    int sourceId;
    // id of the search concerned by the alert
    int searchId;
    //  value number concerned by the alert
    int valueNum;
    
    //value of the alert set by the user in the database (need to be converted)
    double valNum; 
   
   // boost::mutex::scoped_lock scoped_lock(mutex);
    
    try //SQL transaction
    {  
        Wt::Dbo::Transaction transaction(sessionThread);        
        //we check if it's a simple or a complex alert (complex <=> AVA_ID doesn't exist)
        alertId = alertPtr.get()->alertValue.id();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << e.what();
    }
    
    if (alertId != -1)
    {
        try //SQL transaction
        {
            Wt::Dbo::Transaction transaction(sessionThread);
            ToolsEngine::log("info") << "[Class:AlertProcessor] " << "simple alert processing";
            //value of the alert that will be processed
            Wt::WString val =  alertPtr.get()->alertValue.get()->value;
            valNum = boost::lexical_cast<double>(val);
            //critieria that will be used of the alert process
            Wt::WString criteria = alertPtr.get()->alertValue.get()->alertCriteria.get()->name;

            //id of the plugin concerned by the alert            
            pluginId = alertPtr.get()->alertValue.get()->information.get()->pk.search.get()->pk.source.get()->pk.plugin.id();            
            //id of the source concerned by the alert
            sourceId = alertPtr.get()->alertValue.get()->information.get()->pk.search.get()->pk.source.get()->pk.id;
            // id of the search concerned by the alert
            searchId = alertPtr.get()->alertValue.get()->information.get()->pk.search.get()->pk.id;
            //  value number concerned by the alert
            valueNum = alertPtr.get()->alertValue.get()->information.get()->pk.subSearchNumber;          
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:AlertProcessor] " << e.what();
        }
        //TODO : on va sélectionner toutes les valeurs d'une même information, il peut être intéressant à l'avenir 
        //de limiter ce nombre de valeur par thread car le thread occupe le CPU durant toute la boucle sur ces valeurs.

        //we select the value that concern our alert
        typedef Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > tbInformationValue;

        while(1)
        {
            try //SQL transaction
            {
                    Wt::Dbo::Transaction transaction(sessionThread);
                tbInformationValue valuesToCheck = sessionThread.find<InformationValue>()
                    .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                    .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                    .where("\"SRC_ID\" = ?").bind(sourceId)
                    .where("\"SEA_ID\" = ?").bind(searchId)
                    .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                    ; 

                ToolsEngine::log("info") << " [Class:AlertProcessor] " << " The thread finds an InformationValue to process";

                //get the type of the value
                switch(alertPtr.get()->alertValue.get()->information.get()->unit.get()->unitType.id())
                {
                    case number:
                        switch(alertPtr.get()->alertValue.get()->alertCriteria.id())
                        {
                            case lt:
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    if( boost::lexical_cast<double>(i->get()->value) < valNum)
                                    {
                                        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated < "; 
                                    }
                                    i->modify()->state = 2;
                                }
                                break;
                            case le:
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    if( boost::lexical_cast<double>(i->get()->value) <= valNum)
                                    {
                                        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated <=";   
                                    }
                                    i->modify()->state = 2;
                                }
                                break;
                            case eq:
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    if( boost::lexical_cast<double>(i->get()->value) == valNum)
                                    {
                                        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated =";         
                                        //we create the sender
                                        AlertSender alertSender;
                                        alertSender.send(alertPtr,*i);
                                    }
                                    i->modify()->state = 2;
                                }
                                break;
                            case ne:
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    if( boost::lexical_cast<double>(i->get()->value) != valNum)
                                    {
                                        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated !=";
                                    }
                                    i->modify()->state = 2;                                    
                                }
                                break;                            
                            case ge:
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    if( boost::lexical_cast<double>(i->get()->value) >= valNum)
                                    {
                                        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated >=";
                                    }
                                    i->modify()->state = 2;
                                }
                                break;
                            case gt:
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    if( boost::lexical_cast<double>(i->get()->value) > valNum)
                                    {
                                        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated >";
                                    }
                                    i->modify()->state = 2;
                                }
                                break;
                            default:
                                ToolsEngine::log("error") << "[Class:AlertProcessor] " << "switch operator selection failed";
                                break; 
                        }
                        break;
                    case text:
                        ToolsEngine::log("info") << "[Class:AlertProcessor] " << "Text Alert not yet implemented";
                        break;
                    default:
                        ToolsEngine::log("error") << "[Class:AlertProcessor] " << "switch Information unit type check failed";
                        break;               
                }
                boost::this_thread::sleep(boost::posix_time::milliseconds(ToolsEngine::sleepThreadMilliSec)); 
                //sleep(1);
            }//fin try
            catch (Wt::Dbo::Exception e)
            {
                ToolsEngine::log("error") << " [Class:AlertProcessor] " << e.what();
            }
        }//end while
    }
    else
    {
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " The engine isn't able to calculate complex alerts now";
    }
} 