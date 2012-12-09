#include "AlertProcessor.h"
#include "CompareMethods.h"

AlertProcessor::AlertProcessor() {
}

AlertProcessor::~AlertProcessor() {
}

int AlertProcessor::verifyAlerts()
{
    typedef Wt::Dbo::collection< Wt::Dbo::ptr<Alert> > Alerts;
    boost::thread_group threadsVerifyAlerts;
    //int threadNumber=0;
    //std::vector<pthread_t> threadList;
    boost::mutex::scoped_lock scoped_lock(mutex);
    Alerts alerts;
    //SQL session
    while (true)
    {
        try
        {
            Wt::Dbo::Transaction transaction(*(te->sessionAlertProcessor));        

            //we get the list of all defined alerts in the database
            alerts = te->sessionAlertProcessor->find<Alert>().where("\"ALE_DELETE\" IS NULL");
            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << "We have " << alerts.size() << " Alert(s) in the database";

            for (Alerts::const_iterator i = alerts.begin(); i != alerts.end(); ++i)
            {
               ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " the Alert : " << (*i)->name << " is in the database.";
               //we instanciate a thread for each alert           
               //this : instance de la classe (l'objet lui même) dans laquelle est exécuté bind()
               threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::InformationValueLoop,this,(*i).id()));
               boost::this_thread::sleep(boost::posix_time::milliseconds(100));
            }
            transaction.commit();
            threadsVerifyAlerts.join_all();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
        }
    }
    return 0;
    boost::mutex::scoped_lock scoped_unlock(mutex);
}

//TODO: avec le fonctionnement actuel de la méthode, il n'est pas possible de définir deux alertes sur la même information
//TODO: car le state de l'info est passé a 2 ( donc traité) au 1er passage d'une verification d'une alerte, du coup une 2ème alerte ne retraitera pas cette info
void AlertProcessor::InformationValueLoop(long long idAlert)
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadCheckAlertMilliSec));
    //creation of a new SQL session
    Session sessionThread(te->sqlCredentials);
    
//    int alertId;
    
    //parameters from the alert         
    int pluginId;            
    int sourceId;
    int searchId;
    double infValueNum;
    int unitId;
    Wt::Dbo::collection<Wt::Dbo::ptr<Asset> > assets;
    std::string assetList = "";
    std::string keyValue;
    //list of iva to process
    std::string informationValueListSqlPrepared = "()";
    
    //value of the alert set by the user in the database (need to be converted)
    double alertValueToCompare; 
    
    //the line number we search if the information value has a key
    int lineNumber;
    
    //define the pointer of the operators functions
    bool (*ltPtr)(double, double);
    ltPtr = ltMethod;
    
    bool (*lePtr) (double, double);
    lePtr = leMethod;
    
    bool (*eqPtr)(double, double);
    eqPtr = eqMethod;
    
    bool (*nePtr) (double, double);
    nePtr = neMethod;
    
    bool (*gePtr)(double, double);
    gePtr = geMethod;  
    
    bool (*gtPtr)(double, double);
    gtPtr = gtMethod;
    
    
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " New Thread created, the Alert : " << idAlert 
            << " is now processed by the engine.";
    //we check if it's a simple or a complex alert (complex <=> AVA_ID doesn't exist)
    // TSA : where do we check that ?
    
    // we get all the datas about the current alert
    try //SQL transaction
    {
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Getting alert data";
        Wt::Dbo::Transaction transaction(sessionThread);
        Wt::Dbo::ptr<Alert> alertPtr = sessionThread.query<Wt::Dbo::ptr<Alert> >
                ("SELECT ale FROM \"T_ALERT_ALE\" ale WHERE \"ALE_ID\" = ? AND \"ALE_DELETE\" IS NULL FOR UPDATE")
                .bind(idAlert).limit(1);

        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Alert fetched";

        
        //value of the alert that will be processed     
        Wt::WString val =  alertPtr.get()->alertValue.get()->value;
        alertValueToCompare = boost::lexical_cast<double>(val);
        
        if (alertPtr.get()->alertValue.get()->keyValue)
        {
            keyValue = alertPtr.get()->alertValue.get()->keyValue.get().toUTF8();
        }

        //we get the data related to the alert : plg_id src_id sea_id infValNum unt_id list of assets
        pluginId = alertPtr->alertValue.get()->information.get()->pk.search.get()->pk.source.get()->pk.plugin.id();            
        sourceId = alertPtr.get()->alertValue.get()->information.get()->pk.search.get()->pk.source.get()->pk.id;
        searchId = alertPtr.get()->alertValue.get()->information.get()->pk.search.get()->pk.id;
        infValueNum = alertPtr.get()->alertValue.get()->information.get()->pk.subSearchNumber;
        unitId = alertPtr.get()->alertValue.get()->information.get()->pk.unit.id();
        assets = alertPtr.get()->assets;
        
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "plid = " << pluginId
                                    << "souid = " << sourceId
                                    << "seaid = " << searchId
                                    << "ivn = " << infValueNum
                                    << "unitId = " << unitId;
        if (assets.size() < 1)
        {
            ToolsEngine::log("error") << " [Class:AlertProcessor] " 
                    << " - " << "Impossible to send an alert : no asset associated";
            transaction.commit();
            return;
        }
        assetList = getAssetListSqlPrepared(assets);
        
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "assetList = " << assetList;
        
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Alert data fetched";
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
        return;
    }
    
    //we select the value that concern our alert
    typedef Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > tbInformationValue;

    int posKey = 0;

    try //SQL transaction
    {
        ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Updating last attempt";
        Wt::Dbo::Transaction transaction(sessionThread);
        Wt::Dbo::ptr<Alert> alertPtr = sessionThread.query<Wt::Dbo::ptr<Alert> >
                ("SELECT ale FROM \"T_ALERT_ALE\" ale WHERE \"ALE_ID\" = ? AND \"ALE_DELETE\" IS NULL FOR UPDATE")
                .bind(idAlert).limit(1);
        alertPtr.modify()->lastAttempt = Wt::WDateTime::currentDateTime();
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }

    
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Launching loop";
    

    // TSA : maybe put the sleep at the beginning to avoid any risk to miss it in a unexpected case
    posKey = getPosKey(&sessionThread, pluginId,sourceId,searchId,infValueNum, unitId,assetList);

    // GET THE LINE VALUE IF NECESSARY
    if (posKey > 0)
    {
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - posKey found : " << posKey;
        try
        {
            Wt::Dbo::Transaction transaction(sessionThread);
            std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
            " WHERE \"SEA_ID\" = " + boost::lexical_cast<std::string>(searchId) + 
            " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>(sourceId) + 
            " AND \"PLG_ID_PLG_ID\" = " + boost::lexical_cast<std::string>(pluginId) + 
            " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>(posKey) + 
            " AND \"IVA_VALUE\" = '" + keyValue + "'"
            " AND \"IVA_AST_AST_ID\" IN " + assetList + 
            " LIMIT 1";
            ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " -  Query : " << queryString;
            Wt::Dbo::ptr<InformationValue> ptrIva = sessionThread.query<Wt::Dbo::ptr<InformationValue> >(queryString);
            lineNumber = ptrIva.get()->lineNumber;
            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << "Failed to find the line corresponding to posKey" << "-" << e.what();
            return;
        }
    } 
    else if (posKey == 0)
    {
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - posKey == 0";
        lineNumber = 0;
    }
    else //posKey < 0 
    {
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "Couldn't get pos key value";
        return;
    }
    // END OF GETTING LINE NUMBER


    // GET THE VALUES TO PROCESS    
    try //SQL transaction
    {
        Wt::Dbo::Transaction transaction(sessionThread);
        Wt::Dbo::ptr<Alert> alertPtr = sessionThread.query<Wt::Dbo::ptr<Alert> >
            ("SELECT ale FROM \"T_ALERT_ALE\" ale WHERE \"ALE_ID\" = ? AND \"ALE_DELETE\" IS NULL FOR UPDATE")
            .bind(idAlert).limit(1);
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "switch : alert unit type";
        //get the type of the value
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "unit type id :"  
                << alertPtr->alertValue->information->pk.unit->unitType.get();


        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "asset list : " << assetList;
        std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva "
                " WHERE \"IVA_STATE\" = 0 "
                " AND \"PLG_ID_PLG_ID\" = " + boost::lexical_cast<std::string>(pluginId) + ""
                " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>(sourceId) + ""
                " AND \"SEA_ID\" = " + boost::lexical_cast<std::string>(searchId) + ""
                " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>(infValueNum) + ""
                " AND \"INU_ID_INU_ID\" = " + boost::lexical_cast<std::string>(unitId) + ""
                " AND \"IVA_AST_AST_ID\" IN " + assetList + " FOR UPDATE";
        tbInformationValue valuesToCheck = sessionThread.query<Wt::Dbo::ptr<InformationValue> >(queryString).limit(10);

        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "valuesToCheck size : " << valuesToCheck.size();
        if (valuesToCheck.size() < 1)
        {
            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << "Nothing to check";
            transaction.commit();
            return;
        }
        informationValueListSqlPrepared = getInformationValueListSqlPrepared(valuesToCheck, 1);
        sessionThread.execute("UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = 1 WHERE \"IVA_ID\" IN " + informationValueListSqlPrepared);
        transaction.commit();
    }//fin try
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << "getting iva list 1 : " << e.what();
    }

    int unitType = 0;
    int alertCriteria = 0;
    try //SQL transaction
    {
        Wt::Dbo::Transaction transaction(sessionThread);
        Wt::Dbo::ptr<Alert> alertPtr = sessionThread.query<Wt::Dbo::ptr<Alert> >
            ("SELECT ale FROM \"T_ALERT_ALE\" ale WHERE \"ALE_ID\" = ? AND \"ALE_DELETE\" IS NULL FOR UPDATE")
            .bind(idAlert).limit(1);
        unitType = alertPtr->alertValue->information->pk.unit->unitType.id();
        alertCriteria = alertPtr->alertValue->alertCriteria.id();
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << "getting iva list 2 : " << e.what();
        return;
    }
    switch(unitType)
    {
        case number:
            ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the case number";
            switch(alertCriteria)
            {          
                case lt: 
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the lt comparison";
                    AlertProcessor::compareNumberValue(informationValueListSqlPrepared, ltPtr, alertValueToCompare, idAlert, lineNumber);
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the lt comparison";  
                    break;
                case le:
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the le comparison";
                    AlertProcessor::compareNumberValue(informationValueListSqlPrepared, lePtr, alertValueToCompare, idAlert, lineNumber);
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the le comparison";
                    break;
                case eq:
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the eq comparison";
                    AlertProcessor::compareNumberValue(informationValueListSqlPrepared, eqPtr, alertValueToCompare, idAlert, lineNumber);
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the eq comparison";
                    break;
                case ne:
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the ne comparison";
                    AlertProcessor::compareNumberValue(informationValueListSqlPrepared, nePtr, alertValueToCompare, idAlert, lineNumber);
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the ne comparison";
                    break;                            
                case ge:
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the ge comparison";
                    AlertProcessor::compareNumberValue(informationValueListSqlPrepared, gePtr, alertValueToCompare, idAlert, lineNumber);
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the ge comparison";
                    break;
                case gt:
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the gt comparison";
                    AlertProcessor::compareNumberValue(informationValueListSqlPrepared, gtPtr, alertValueToCompare, idAlert, lineNumber);
                    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the gt comparison";
                    break;
                default:
                    ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << "switch operator selection failed";
                    break; 
            }
            break;
        case text:
            ToolsEngine::log("warning") << " [Class:AlertProcessor] " << " - " << "Text Alert not yet implemented";
            try
            {
                Wt::Dbo::Transaction transaction(sessionThread);
                std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva WHERE \"IVA_ID\" IN " + informationValueListSqlPrepared;
                tbInformationValue valuesToCheck = sessionThread.query<Wt::Dbo::ptr<InformationValue> >(queryString);
                for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
                {
                    ToolsEngine::log("warning") << " [Class:AlertProcessor] " << " - " << "processing information name for text alert : " << i->get()->information.get()->name;
                    i->modify()->state = 666;//error
                }
                transaction.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << " text fail : " << e.what();
            }
            break;
        default:
            ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << "switch Information unit type check failed";
            break;               
    }
}

int AlertProcessor::getPosKey(Session *sessionThread, int pluginId,int sourceId,int searchId,double valueNum, int unitId, std::string assetList)
{
    int res = -1;
    try 
    {
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " Getting pos key";
        Wt::Dbo::Transaction transaction(*sessionThread);
        
        std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva "
                " WHERE \"IVA_STATE\" = 0 "
                " AND \"PLG_ID_PLG_ID\" = " + boost::lexical_cast<std::string>(pluginId) + ""
                " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>(sourceId) + ""
                " AND \"SEA_ID\" = " + boost::lexical_cast<std::string>(searchId) + ""
                " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>(valueNum) + ""
                " AND \"INU_ID_INU_ID\" = " + boost::lexical_cast<std::string>(unitId) + ""
                " AND \"IVA_AST_AST_ID\" IN " + assetList + "";
        Wt::Dbo::Query<Wt::Dbo::ptr<InformationValue>,Wt::Dbo::DynamicBinding> query = sessionThread->query<Wt::Dbo::ptr<InformationValue> >(queryString).limit(1);
        Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > valuesToCheck = query.resultList();
        
        
        if (valuesToCheck.size() < 1) 
        {
            ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " nowhere to search for a pos key";
        } 
        else
        {
            Wt::Dbo::ptr<InformationValue> valueToCheck = valuesToCheck.front();
            if (valueToCheck.id() != -1) 
            {
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " The thread found a pos key";
                res = valueToCheck.get()->information.get()->pk.search.get()->pos_key_value;

            } 
            else 
            {
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " The thread didn't find a pos key";
            }
        }
        
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << "Couldn't get pos key value : " << e.what();;
    }
    return res;
}

std::string AlertProcessor::getAssetListSqlPrepared(Wt::Dbo::collection<Wt::Dbo::ptr<Asset> > assets)
{
    std::string res = "(";
    int idx = 0;
    for (Wt::Dbo::collection<Wt::Dbo::ptr<Asset> >::const_iterator i = assets.begin(); i != assets.end(); i++) 
    {
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " For asset list : " << (*i).id();
        res += boost::lexical_cast<std::string,long long>((*i).id()) + ",";
        idx++;
    }
    res.replace(res.size()-1, 1, "");
    if (idx == 0)
    {
        res += "0";
    }
    res += ")";
    return res;
}

std::string AlertProcessor::getInformationValueListSqlPrepared(Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > informationValues, int state)
{
    std::string res = "(";
    int idx = 0;
    for (Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> >::const_iterator i = informationValues.begin(); i != informationValues.end(); i++) 
    {
        i->modify()->state = state;
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " For iva list : " << (*i).id();
        res += boost::lexical_cast<std::string,long long>((*i).id()) + ",";
        i->flush();
        idx++;
    }
    res.replace(res.size()-1, 1, "");
    if (idx == 0)
    {
        res += "0";
    }
    res += ")";
    return res;
}

int AlertProcessor::compareNumberValue(std::string stringValuesToCheck,bool (*mathOperator)(double,double), double valueSetInDb, long long idAlert, int lineNumber)
{
    Session compareSession(te->sqlCredentials);
    
    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the comparingNumberValue method";
    try
    {
        Wt::Dbo::Transaction transaction(compareSession);
        std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva WHERE \"IVA_ID\" IN " + stringValuesToCheck + " FOR UPDATE";
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - Compare number value query String : " << queryString;
        tbInformationValue valuesToCheck = compareSession.query<Wt::Dbo::ptr<InformationValue> >(queryString);
        for (tbInformationValue::const_iterator i = valuesToCheck.begin(); i != valuesToCheck.end(); ++i) 
        {
            ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "processing information name : " << i->get()->information.get()->name;
            ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "begin of the for() comparison";
            ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "pos key value in the for : " 
                                                                    << i->get()->information.get()->pk.search.get()->pos_key_value;
            //it concerns an information without a key value
            if (i->get()->information.get()->pk.search.get()->pos_key_value == 0)
            {
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " alert treatment on an information without a key value ";
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "output of calcul : " 
                                                                        << mathOperator(boost::lexical_cast<double>(i->get()->value), valueSetInDb)
                                                                        << " for : " << i->get()->value << " and alert value : " << valueSetInDb
                                                                        ;
                
                if( mathOperator(boost::lexical_cast<double>(i->get()->value), valueSetInDb) == true )
                {
                    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Alert generated  : " << idAlert; 
                    //we create the sender
                    AlertSender *alertSender = new AlertSender();  
                    alertSender->send(idAlert,*i);
                    i->modify()->state = 2;
                }
                else
                {
                    i->modify()->state = 3;
                }
            }
            else if (i->get()->information.get()->pk.search.get()->pos_key_value != 0)
            {
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " alert treatment on an information with a key value ";
                if( i->get()->lineNumber == lineNumber && mathOperator(boost::lexical_cast<double>(i->get()->value),valueSetInDb) == true)
                {
                    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Alert generated with key value < : " << idAlert; 
                    //we create the sender
                    AlertSender alertSender;  
                    alertSender.send(idAlert,*i);
                    i->modify()->state = 2;
                }
                else
                {
                    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Error while comparing alert value with iva value";
                    i->modify()->state = 3;
                }
            }
            else
            {
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " Alert not generated with the information : " << i->get()->value;
            }
        }
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << " comparing numbervalue catch " << e.what();
    }
            
    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the for()";
}