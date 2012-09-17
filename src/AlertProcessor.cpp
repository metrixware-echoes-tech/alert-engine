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
    Alerts alerts;
    //SQL session
    try
    {
        Wt::Dbo::Transaction transaction(*(te->sessionAlertProcessor));        
       
        //we get the list of all defined alerts in the database
        alerts = te->sessionAlertProcessor->find<Alert>();
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << "We have " << alerts.size() << " Alert(s) in the database";

        for (Alerts::const_iterator i = alerts.begin(); i != alerts.end(); ++i)
        {
           ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " the Alert : " << (*i)->name << " is in the database.";
           //we instanciate a thread for each alert           
           //this : instance de la classe (l'objet lui même) dans laquelle est exécuté bind()
           threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::InformationValueLoop,this,(*i).id()));
        }
        threadsVerifyAlerts.join_all();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << e.what();
    }
return 0;
}

//TODO: avec le fonctionnement actuel de la méthode, il n'est pas possible de définir deux alertes sur la même information
//TODO: car le state de l'info est passé a 2 ( donc traité) au 1er passage d'une verification d'une alerte, du coup une 2ème alerte ne retraitera pas cette info
void AlertProcessor::InformationValueLoop(long long idAlert)
{
    Wt::WDateTime *now = new Wt::WDateTime();
    
    //the alert that we will re construct with the idAlert param 
    Wt::Dbo::ptr<Alert> alertPtr = new Alert();
     
    //creation of a new SQL session
    Session sessionThread(te->sqlCredentials);
    // creation of a criteria and an information unit type enum
    criteria alertCriterias;
    informationUnitType alertTypes;
    
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
    
    //the line number we search if the information value has a key
    int lineNumber;
   
   // boost::mutex::scoped_lock scoped_lock(mutex);
    
    try //SQL transaction
    {  
        Wt::Dbo::Transaction transaction(sessionThread);        
        
       
        alertPtr = sessionThread.find<Alert>()
                    .where("\"ALE_ID\" = ?").bind(idAlert);
        alertId = alertPtr.get()->alertValue.id();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << e.what();
    }
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " New Thread created, the Alert : " << alertPtr->name << " is now proccesed by the engine.";
    //we check if it's a simple or a complex alert (complex <=> AVA_ID doesn't exist)
    if (alertId != -1)//a NULL dbo pointer return -1
    {
        try //SQL transaction
        {
            Wt::Dbo::Transaction transaction(sessionThread);
         //   ToolsEngine::log("info") << "[Class:AlertProcessor] " << "simple alert processing";
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
        
        int posKey;
        
        *now = Wt::WDateTime::currentDateTime(); //for setting the last attempt of the alert;
    
        try //SQL transaction
        {
            Wt::Dbo::Transaction transaction(sessionThread);
            alertPtr.modify()->lastAttempt = *now;
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:AlertProcessor] " << e.what();
        }

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
                if (valuesToCheck.size() > 0)
                {
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " The thread finds an InformationValue to process";
                }
                else
                {
                    boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadCheckAlertMilliSec));
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " The thread doesn't finds an InformationValue to process";                    
                    continue;
                }
                
                for (tbInformationValue::const_iterator l = valuesToCheck.begin(); l != valuesToCheck.end(); ++l) 
                {
                    posKey = valuesToCheck.front().get()->information.get()->pk.search.get()->pos_key_value;
                    //TODO : remove the break , goal : just do one turn on the collection ti get the position key value, because it is the same information on 
                    //all entries of the collection, so one turn is enough
                    break;
                    
                }
                
                //let's check if we are face to SEA_POS_KEY_VALUE !=0
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "valuesToCheck size : " << valuesToCheck.size();
                //if (valuesToCheck.front().get()->information.get()->pk.search.get()->pos_key_value !=0)
                if (posKey !=0)
                {
                    //we have a pos_key_value, so we have to find the value concerned by the alert
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " 
                                             << " The thread finds an InformationValue to process which has a KEY_VALUE, position : " << posKey;
                    
                    //for the case if there is a key, we need a collection to stock the list of the keys
                    tbInformationValue keyToCheck = sessionThread.find<InformationValue>()
                    .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                    .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                    .where("\"SRC_ID\" = ?").bind(sourceId)
                    .where("\"SEA_ID\" = ?").bind(searchId)
                    .where("\"INF_VALUE_NUM\" = ?").bind(posKey)
                    ;
                    
                    
                    //TODO : a transformer en while ?
                    for (tbInformationValue::const_iterator k = keyToCheck.begin(); k != keyToCheck.end(); ++k) 
                    {
                        
                        if (k->get()->value == alertPtr.get()->alertValue.get()->keyValue /*eth0 for example*/)
                        {
                            lineNumber = k->get()->lineNumber;
                            ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "We have find the line number corresponding to the key " << k->get()->value << " at position : "
                                                                                    << posKey << " line : "<< lineNumber;                          
                            break;// we have find one match so we leave
                        }
                    }
                }
                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the alert unit type";
                //get the type of the value
                ToolsEngine::log("debug") << " [Class:AlertProcessor] "<< "unit type id :"  << alertPtr.get()->alertValue.get()->information.get()->unit.get()->unitType.id();
                switch(alertPtr.get()->alertValue.get()->information.get()->unit.get()->unitType.id())
                {
                    case number:
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the case number";
                        switch(alertPtr.get()->alertValue.get()->alertCriteria.id())
                        {
                            case lt:
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the lt comparison";
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "valuesToCheck size in lt comparison : " << valuesToCheck.size(); 
                                valuesToCheck = sessionThread.find<InformationValue>()
                                                                        .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                                                                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                                                                        .where("\"SRC_ID\" = ?").bind(sourceId)
                                                                        .where("\"SEA_ID\" = ?").bind(searchId)
                                                                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                                                                        ; 
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "processing information name : " << i->get()->information.get()->name;
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "begin of the for() lt comparison.";
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "pos key value in the for lt : " 
                                                                                            << i->get()->information.get()->pk.search.get()->pos_key_value;
                                    //it concerns an information with a key value
                                    if (i->get()->information.get()->pk.search.get()->pos_key_value == 0)
                                    {
                                        if( boost::lexical_cast<double>(i->get()->value) < valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated < : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                    else if (i->get()->information.get()->pk.search.get()->pos_key_value != 0)
                                    {
                                        if( i->get()->lineNumber == lineNumber && boost::lexical_cast<double>(i->get()->value) < valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated with key value < : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                }
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are at the end of the for() lt comparison";
                                break;
                            case le:
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the le comparison";
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "valuesToCheck size in le comparison : " << valuesToCheck.size();                                
                                valuesToCheck = sessionThread.find<InformationValue>()
                                                                        .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                                                                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                                                                        .where("\"SRC_ID\" = ?").bind(sourceId)
                                                                        .where("\"SEA_ID\" = ?").bind(searchId)
                                                                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                                                                        ; 
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "processing information name : " << i->get()->information.get()->name;
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "begin of the for() le comparison.";
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "pos key value in the for le : " 
                                                                                            << i->get()->information.get()->pk.search.get()->pos_key_value;
                                    //it concerns an information with a key value
                                    if (i->get()->information.get()->pk.search.get()->pos_key_value == 0)
                                    {
                                        if( boost::lexical_cast<double>(i->get()->value) <= valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated <= : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                    else if (i->get()->information.get()->pk.search.get()->pos_key_value != 0)
                                    {
                                        if( i->get()->lineNumber == lineNumber && boost::lexical_cast<double>(i->get()->value) <= valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated with key value <= : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    } 
                                }
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are at the end of the for() le comparison";
                                break;
                            case eq:
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the eq comparison";
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "valuesToCheck size in eq comparison : " << valuesToCheck.size();                                
                                valuesToCheck = sessionThread.find<InformationValue>()
                                                                        .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                                                                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                                                                        .where("\"SRC_ID\" = ?").bind(sourceId)
                                                                        .where("\"SEA_ID\" = ?").bind(searchId)
                                                                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                                                                        ; 
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "processing information name : " << i->get()->information.get()->name;
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "begin of the for() eq comparison.";
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "pos key value in the for eq : " 
                                                                                            << i->get()->information.get()->pk.search.get()->pos_key_value;
                                    //it concerns an information with a key value
                                    if (i->get()->information.get()->pk.search.get()->pos_key_value == 0)
                                    {
                                        if( boost::lexical_cast<double>(i->get()->value) == valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated == : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                    else if (i->get()->information.get()->pk.search.get()->pos_key_value != 0)
                                    {
                                        if( i->get()->lineNumber == lineNumber && boost::lexical_cast<double>(i->get()->value) == valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated with key value == : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                }
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are at the end of the for() eq comparison";
                                break;
                            case ne:
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the ne comparison";
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "valuesToCheck size in ne comparison : " << valuesToCheck.size();                                
                                valuesToCheck = sessionThread.find<InformationValue>()
                                                                        .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                                                                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                                                                        .where("\"SRC_ID\" = ?").bind(sourceId)
                                                                        .where("\"SEA_ID\" = ?").bind(searchId)
                                                                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                                                                        ; 
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "processing information name : " << i->get()->information.get()->name;
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "begin of the for() ne comparison.";
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "pos key value in the for ne : " 
                                                                                            << i->get()->information.get()->pk.search.get()->pos_key_value;
                                    //it concerns an information with a key value
                                    if (i->get()->information.get()->pk.search.get()->pos_key_value == 0)
                                    {
                                        if( boost::lexical_cast<double>(i->get()->value) != valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated != : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                    else if (i->get()->information.get()->pk.search.get()->pos_key_value != 0)
                                    {
                                        if( i->get()->lineNumber == lineNumber && boost::lexical_cast<double>(i->get()->value) != valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated with key value != : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                }
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are at the end of the for() ne comparison";
                                break;                            
                            case ge:
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the ge comparison";
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "valuesToCheck size in ge comparison : " << valuesToCheck.size();                                
                                valuesToCheck = sessionThread.find<InformationValue>()
                                                                        .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                                                                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                                                                        .where("\"SRC_ID\" = ?").bind(sourceId)
                                                                        .where("\"SEA_ID\" = ?").bind(searchId)
                                                                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                                                                        ; 
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "processing information name : " << i->get()->information.get()->name;
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "begin of the for() ge comparison.";
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "pos key value in the for ge : " 
                                                                                            << i->get()->information.get()->pk.search.get()->pos_key_value;
                                    //it concerns an information with a key value
                                    if (i->get()->information.get()->pk.search.get()->pos_key_value == 0)
                                    {
                                        if( boost::lexical_cast<double>(i->get()->value) >= valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated >= : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                    else if (i->get()->information.get()->pk.search.get()->pos_key_value != 0)
                                    {
                                        if( i->get()->lineNumber == lineNumber && boost::lexical_cast<double>(i->get()->value) >= valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated with key value >= : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                }
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are at the end of the for() ge comparison";
                                break;
                            case gt:
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are entering in the switch of the gt comparison";
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "valuesToCheck size in gt comparison : " << valuesToCheck.size();                                
                                valuesToCheck = sessionThread.find<InformationValue>()
                                                                        .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                                                                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                                                                        .where("\"SRC_ID\" = ?").bind(sourceId)
                                                                        .where("\"SEA_ID\" = ?").bind(searchId)
                                                                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                                                                        ; 
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "processing information name : " << i->get()->information.get()->name;
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << "begin of the for() gt comparison.";
                                    ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "pos key value in the for gt : " 
                                                                                            << i->get()->information.get()->pk.search.get()->pos_key_value;
                                    //it concerns an information with a key value
                                    if (i->get()->information.get()->pk.search.get()->pos_key_value == 0)
                                    {
                                        if( boost::lexical_cast<double>(i->get()->value) > valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated > : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                    else if (i->get()->information.get()->pk.search.get()->pos_key_value != 0)
                                    {
                                        if( i->get()->lineNumber == lineNumber && boost::lexical_cast<double>(i->get()->value) > valNum)
                                        {
                                            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " Alert generated with key value > : " << alertPtr.get()->name; 
                                            //we create the sender
                                            AlertSender alertSender;  
                                            alertSender.send(alertPtr,*i);
                                            i->modify()->state = 2;
                                        }
                                    }
                                }
                                ToolsEngine::log("debug") << " [Class:AlertProcessor] "  << "we are at the end of the for() gt comparison";
                                break;
                            default:
                                ToolsEngine::log("error") << "[Class:AlertProcessor] " << "switch operator selection failed";
                                break; 
                        }
                        break;
                    case text:
                        ToolsEngine::log("warning") << "[Class:AlertProcessor] " << "Text Alert not yet implemented";
                        
                        valuesToCheck = sessionThread.find<InformationValue>()
                                                                        .where("\"IVA_STATE\" = ?").bind("0") //we verify that the state of the information value is 0
                                                                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginId)
                                                                        .where("\"SRC_ID\" = ?").bind(sourceId)
                                                                        .where("\"SEA_ID\" = ?").bind(searchId)
                                                                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                                                                        ; 
                                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                                {
                                    ToolsEngine::log("warning") << " [Class:AlertProcessor] " << "processing information name for text alert : " << i->get()->information.get()->name;
                                    i->modify()->state = 666;//error
                                }
                        break;
                    default:
                        ToolsEngine::log("error") << "[Class:AlertProcessor] " << "switch Information unit type check failed";
                        break;               
                }
                boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadCheckAlertMilliSec)); 
                transaction.commit();
            }//fin try
            catch (Wt::Dbo::Exception e)
            {
                ToolsEngine::log("error") << " [Class:AlertProcessor] "<< "While 1 InformationValueLoop()" << e.what();
            }
        }//end while
    }
    else
    {
        ToolsEngine::log("warning") << " [Class:AlertProcessor] " << " The engine isn't able to compute complex alerts now";
    }
} 