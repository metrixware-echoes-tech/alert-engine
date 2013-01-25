#include "AlertProcessor.h"
#include "CompareMethods.h"

AlertProcessor::AlertProcessor() {
    ltPtr = ltMethod;
    lePtr = leMethod;
    eqPtr = eqMethod;
    nePtr = neMethod;
    gePtr = geMethod;  
    gtPtr = gtMethod;
}

AlertProcessor::~AlertProcessor() {
}

int AlertProcessor::verifyAlerts()
{
    boost::mutex::scoped_lock scoped_lock(mutex);
    while (true)
    {
        try
        {
            bool res = true;
            launchUpdateDataThread();
            launchIvaThread();
            launchAlertThread();
            launchCleanThread();
            
            threadsVerifyAlerts.join_all();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
        }
    }
    boost::mutex::scoped_lock scoped_unlock(mutex);
    return 0;
    
}

bool AlertProcessor::launchUpdateDataThread()
{
    threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::updateData,this));
}

void AlertProcessor::launchIvaThread()
{
    threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::collectIva,this));
}

void AlertProcessor::launchAlertThread()
{
    threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::prepareAlertComputing,this));
}

void AlertProcessor::launchCleanThread()
{
    threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::cleanMaps,this));
}

// fill the maps and vector with data collected in the db
void AlertProcessor::updateData()
{
    //    std::map<long long, Wt::Dbo::ptr<Alert>*> mapAlerts;
    //    std::map<InformationId, std::vector<long long>*> mapInfsAlertId;
    while (true)
    {
        try
        { 
            bool res = false;
            res = res & setAlerts();
            res = res & setInfos();
            res = res & setAlertsByInfo();
           
            //Todo : sleep
        }
        catch(Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
        }
    }
}


// fills the mapAlert and mapAlertIdInfs
bool AlertProcessor::setAlerts()
{
    bool res = false;
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        Wt::Dbo::Transaction transaction(*session);
        Wt::Dbo::collection< Wt::Dbo::ptr<Alert> > colAlerts = session->find<Alert>()
                    .where("\"ALE_DELETE\" IS NULL");
            
        for(Wt::Dbo::collection<Wt::Dbo::ptr<Alert>>::const_iterator i = colAlerts.begin(); i != colAlerts.end(); ++i)
        {
            mutex.lock();
            mapAlerts[(*i).id()] = i;
            mutex.unlock();
            
            std::string qryStringInf = "SELECT inf FROM \"T_INFORMATION_INF\" inf, \"T_ALERT_VALUE_AVA\" ava WHERE "
            " ava.\"SEA_ID\" = inf.\"SEA_ID\" "
            "AND ava.\"SRC_ID\" = inf.\"SRC_ID\" "
            "AND ava.\"PLG_ID_PLG_ID\" = inf.\"PLG_ID_PLG_ID\" "
            "AND ava.\"INU_ID_INU_ID\" = inf.\"INU_ID_INU_ID\" "
            "AND ava.\"INF_VALUE_NUM\" = inf.\"INF_VALUE_NUM\" "
            " AND ava.\"AVA_ID\" IN "
            "( SELECT \"ALE_AVA_AVA_ID\" FROM \"T_ALERT_ALE\" "
            " WHERE \"ALE_ID\" = " + boost::lexical_cast<std::string>((*i).id()) + 
            ")";
            Wt::Dbo::collection<Wt::Dbo::ptr<Information2>> colInfs = session->query<Wt::Dbo::collection<Wt::Dbo::ptr<Information2>>>(qryStringInf);
            std::vector<InformationId> vInfIds;
            for(Wt::Dbo::collection<Wt::Dbo::ptr<Information2>>::const_iterator j = colInfs.begin(); j != colInfs.end(); ++j)
            {
                vInfIds.push_back((*j)->pk);
            }
            mapAlertIdInfs[(*i).id()] = vInfIds;
            
        }
        
        
        
        transaction.commit();
        res = true;
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
    return res;
}

// fill vInfos 
bool AlertProcessor::setInfos()
{
    bool res = false;
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        Wt::Dbo::Transaction transaction(*session);
        Wt::Dbo::collection< Wt::Dbo::ptr<Information2> > infos = session->find<Information2>()
                .where("\"INF_DELETE\" IS NULL");
        
        mutex.lock();
        for(Wt::Dbo::collection<Wt::Dbo::ptr<Information2>>::const_iterator i = infos.begin(); i != infos.end(); ++i)
        {
            vInfos.push_back(*i);
        }
        mutex.unlock();
        transaction.commit();
        res = true;
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
    return res;
}

// fill mapInfsAlertId
bool AlertProcessor::setAlertsByInfo()
{
    bool res = false;
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        Wt::Dbo::Transaction transaction(*session);
        mutex.lock();
        for (std::vector<Wt::Dbo::ptr<Information2>>::const_iterator i = vInfos.begin(); i != vInfos.end(); ++i)
        {
            std::string queryString = 
                "SELECT ale FROM \"T_ALERT_ALE\" ale WHERE "
                "\"ALE_AVA_AVA_ID\" IN "
                "(SELECT \"AVA_ID\" FROM \"T_ALERT_VALUE_AVA\" "
                " WHERE \"PLG_ID_PLG_ID\" = " 
                    + boost::lexical_cast<std::string>((*i)->pk.search->pk.source->pk.plugin.id()) +
                " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>((*i)->pk.search->pk.source->pk.id) +
                " AND \"SEA_ID\" = " + boost::lexical_cast<std::string>((*i)->pk.search->pk.id) +
                " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>((*i)->pk.subSearchNumber) +
                ")"
                " AND \"ALE_DELETE\" IS NULL";
            
            std::cout << queryString << std::endl;
                    
            Wt::Dbo::Query<Wt::Dbo::ptr<Alert>> query = session->query<Wt::Dbo::ptr<Alert>>(queryString);
            Wt::Dbo::collection<Wt::Dbo::ptr<Alert>> alertList = query.resultList();
            
            if (alertList.size() > 0)
            {
                std::vector vAlerts;
                for (Wt::Dbo::collection<Wt::Dbo::ptr<Alert>>::const_iterator j = alertList.begin(); j != alertList.end(); ++j)
                {
                    //std::map<InformationId, std::vector<long long>*> mapInfsAlertId
                    vAlerts.push_back((*j).id());
                }
                mapInfsAlertId[(*i)->pk] = *vAlerts;
            }
        }
        mutex.unlock();
        res = true;
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
    return res;
}



void AlertProcessor::collectIva()
{
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        // std::map<long long, std::map<InformationId,std::map<long long, std::map<long long, bool*>*>*>*> mapIvasSortedByAssetsByInfos;
        Wt::Dbo::Transaction transaction(*session);
        long long idAsset;
        InformationId infId;
        std::map<long long, bool*> mapAlerts;
        
        
        
        // prise en compte du line number

                std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\"  iva"
                " WHERE \"SEA_ID\" = " + boost::lexical_cast<std::string>(searchId) + 
                " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>(sourceId) + 
                " AND \"PLG_ID_PLG_ID\" = " + boost::lexical_cast<std::string>(pluginId) + 
                " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>(posKey) + 
                " AND \"IVA_VALUE\" = '" + keyValue + "'"
                " AND \"IVA_AST_AST_ID\" IN " + assetList + 
                " LIMIT 1";
                ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " -  Query : " << queryString;
                Wt::Dbo::ptr<InformationValue> ptrIva = sessionThread->query<Wt::Dbo::ptr<InformationValue> >(queryString);
                if (!ptrIva)
                {
                    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " No iva";
                    return;
                }
                lineNumber = ptrIva.get()->lineNumber;
        
        
        
        
        
        std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva "
                " WHERE \"IVA_STATE\" = 0 FOR UPDATE";
        Wt::Dbo::ptr<InformationValue> ptrIva = session->query<Wt::Dbo::ptr<InformationValue> >(queryString).limit(1);
        
        idAsset = ptrIva->asset.id();
        infId = ptrIva->information->pk;
        
        // TODO : ajouter les alertes complexes qui ont des iva organisées en séquences
        std::string queryString = "SELECT ale FROM \"T_ALERT_ALE\" ale "
                " WHERE \"ALE_AVA_AVA_ID\" IN "
                "(SELECT \"AVA_ID\" FROM \"T_ALERT_VALUE_AVA\" "
                " WHERE \"SEA_ID\" = " + boost::lexical_cast<std::string>(ptrIva->information->pk.search->pk.id)
                " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>(ptrIva->information->pk.search->pk.source->pk.id)
                " AND \"PLG_ID_PLG_ID\" = " + boost::lexical_cast<std::string>(ptrIva->information->pk.search->pk.source->pk.plugin.id())
                " AND \"INU_ID_INU_ID\" = " + boost::lexical_cast<std::string>(ptrIva->information->pk.unit.id())
                " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>(ptrIva->information->pk.subSearchNumber)
                ")"
                ;
        
                
        
        
        // besoin de toutes les alertes concernées par ça oO
        Wt::Dbo::collection<Wt::Dbo::ptr<Alert>> colAlerts = session->query<Wt::Dbo::collection<Wt::Dbo::ptr<Alert>>>(queryString);
        
        for (Wt::Dbo::collection<Wt::Dbo::ptr<Alert>>::const_iterator i = colAlerts.begin(); i != colAlerts.end(); ++i) 
        {
            mapAlerts[(*i).id()] = false;
        }
        
        mapIvasSortedByAssetsByInfos[ptrIva.id()][ptrIva->information->pk] = *mapAlerts; 
        
        ptrIva.modify()->state = 1;
        
        transaction.commit();
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
}

void AlertProcessor::prepareAlertComputing()
{
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        // std::map<long long, std::map<InformationId,std::map<long long, std::map<long long, bool*>*>*>*> mapIvasSortedByAssetsByInfos;
        Wt::Dbo::Transaction transaction(*session);
        mutex.lock();
        for (std::map<long long, Wt::Dbo::ptr<Alert>*>::const_iterator i = this->mapAlerts.begin(); i != this->mapAlerts.end(); ++i) 
        {
            threadsPrepareAlertComputing.create_thread(boost::bind(&AlertProcessor::prepareAlertComputingFromId,this,mapAlertIdInfs[(*i).second.id()]));
        }
        mutex.unlock();
        threadsPrepareAlertComputing.join_all();
        transaction.commit();
        //todo: sleep
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
}

void AlertProcessor::prepareAlertComputingFromId(long long alertId)
{
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        // std::map<long long, std::map<InformationId,std::map<long long, std::map<long long, bool*>*>*>*> mapIvasSortedByAssetsByInfos;
        Wt::Dbo::Transaction transaction(*session);
        Wt::Dbo::ptr<Alert> ptrAlert = session->find<Alert>.where("\"ALE_ID\" = ?").bind(alertId);
        Wt::Dbo::collection<Wt::Dbo::ptr<Asset>> colAssets = ptrAlert->assets;
        std::vector vInfosToCheck = mapAlertIdInfs[alertId];
        std::vector vIvaToCheck;
        for (Wt::Dbo::collection<Wt::Dbo::ptr<Asset>>::const_iterator i = colAssets.begin(); i != colAssets.end(); ++i) 
        {
            for (std::vector<InformationId>::const_iterator j = vInfosToCheck.begin(); j != vInfosToCheck.end(); ++j) 
            {
                mutex.lock();
                for (std::map<long long, std::map<long long, bool*>*>::const_iterator k = mapIvasSortedByAssetsByInfos[(*i).id()][(*j)].begin() ; k != mapIvasSortedByAssetsByInfos[(*i).id()][(*j)].end() ; ++k)
                {
                    if ((*k)[alertId] == true)
                    {
                        vIvaToCheck.push_back((*k).first);
                        (*k)[alertId] = false;
                        break;
                    }
                }
                
                mutex.unlock();
            }
        }
        
        mapAlertIvasToCheck[alertId] = vInfosToCheck;
        
        transaction.commit();
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
}

void AlertProcessor::computeAlerts()
{
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        Wt::Dbo::Transaction transaction(*session);
        for (std::map<long long, std::vector<long long>*>::const_iterator i = this->mapAlerts.begin(); i != this->mapAlerts.end(); ++i) 
        {
            threadsPrepareAlertComputing.create_thread(boost::bind(&AlertProcessor::computeAlertFromId,this,(*i).first));
        }
        mutex.unlock();
        threadsPrepareAlertComputing.join_all();
        transaction.commit();
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
    
}

void AlertProcessor::computeAlertFromId(long long alertId)
{
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        Wt::Dbo::Transaction transaction(*session);
        //set last attempt
        Wt::Dbo::ptr<Alert> alertPtr = session->query<Wt::Dbo::ptr<Alert> >
                ("SELECT ale FROM \"T_ALERT_ALE\" ale WHERE \"ALE_ID\" = ? AND \"ALE_DELETE\" IS NULL FOR UPDATE")
                .bind(alertId).limit(1);
        if (!alertPtr)
        {
            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " No alert for id : " << idAlert;
            return;
        }
        alertPtr.modify()->lastAttempt = Wt::WDateTime::currentDateTime();
        
        for (std::vector<long long>::const_iterator i = mapAlertIvasToCheck[alertId].begin() ; i != mapAlertIvasToCheck[alertId].end() ; ++i)
        {
            Wt::Dbo::ptr<InformationValue> ivaPtr = session->find<InformationValue>.where("\"IVA_ID\" = ?").bind(*i);
            
            //get poskey & line num
            int posKey = 0;
            int lineNumber = 0;
            posKey = ivaPtr->information->pk.search->pos_key_value;
            
            if (posKey > 0)
            {
                lineNumber = ivaPtr->lineNumber;
            }
            else if (posKey == 0)
            {
                lineNumber = 0;
            }
                    
        }
        transaction.commit();
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    SessionPool::getInstance()->returnSession(session);
        
        
        
        
        // ToDo
        

        // calcul
        // Set iva to "used"
        // Fill structure with alerts to send
}


//ToDo
// compute
// clean
// mutexs
// sleeps
// logs

void AlertProcessor::cleanMaps()
{
    
}

bool AlertProcessor::createIvaMaps()
{
    bool res = false;
    Session *session = SessionPool::getInstance()->getSession();
    try
    {

    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    
    SessionPool::getInstance()->returnSession(session);
    return res;
}

bool AlertProcessor::launchCalculationThreadForEachGroup()
{
    bool res = false;
    Session *session = SessionPool::getInstance()->getSession();
    try
    {
        for (std::vector<std::vector<Wt::Dbo::ptr<Alert>>>::const_iterator i = vAlertGroups.begin(); i != vAlertGroups.end(); ++i)
        {
            for (std::vector<Wt::Dbo::ptr<Alert>>::const_iterator j = (*i).begin(); j != (*i).end(); ++j)
            {
                threadsVerifyAlerts.create_thread(boost::bind(&AlertProcessor::InformationValueLoop,this,(*j).id()));
                boost::this_thread::sleep(boost::posix_time::milliseconds(100));
            }
        }
        res = true;
    }
    catch(Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << e.what();
    }
    threadsVerifyAlerts.join_all();
    SessionPool::getInstance()->returnSession(session);
    return res;
}

bool AlertProcessor::sendAlerts()
{
    
}

//TODO: avec le fonctionnement actuel de la méthode, il n'est pas possible de définir deux alertes sur la même information
//TODO: car le state de l'info est passé a 2 ( donc traité) au 1er passage d'une verification d'une alerte, du coup une 2ème alerte ne retraitera pas cette info
void AlertProcessor::InformationValueLoop(long long idAlert)
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(te->sleepThreadCheckAlertMilliSec));
    //creation of a new SQL session
    Session *sessionThread = SessionPool::getInstance()->getSession();
    
//    int alertId;
    
    //parameters from the alert         
    int pluginId;            
    int sourceId;
    int searchId;
    double infValueNum;
    int unitId;
    Wt::WDateTime alertCreaDate;
    Wt::Dbo::collection<Wt::Dbo::ptr<Asset> > assets;
    std::string assetList("");
    std::string keyValue;
    //list of iva to process
    std::string informationValueListSqlPrepared("()");
    
    //value of the alert set by the user in the database (need to be converted)
    double alertValueToCompare; 
    
    //the line number we search if the information value has a key
    int lineNumber;
    
    
    
    
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " New Thread created, the Alert : " << idAlert 
            << " is now processed by the engine.";
    //we check if it's a simple or a complex alert (complex <=> AVA_ID doesn't exist)
    // TSA : where do we check that ?
    
    // we get all the datas about the current alert
    
    
    //we select the value that concern our alert
    typedef Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > tbInformationValue;

    

    
    ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " Launching loop";
    


    // GET THE VALUES TO PROCESS    
    try //SQL transaction
    {
        Wt::Dbo::Transaction transaction(*sessionThread);
        
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "asset list : " << assetList;
        std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva "
                " WHERE \"IVA_STATE\" = 0 "
                " AND \"PLG_ID_PLG_ID\" = " + boost::lexical_cast<std::string>(pluginId) + ""
                " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>(sourceId) + ""
                " AND \"SEA_ID\" = " + boost::lexical_cast<std::string>(searchId) + ""
                " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>(infValueNum) + ""
                " AND \"INU_ID_INU_ID\" = " + boost::lexical_cast<std::string>(unitId) + ""
                " AND \"IVA_CREA_DATE\" >= '" + alertCreaDate.toString().toUTF8() + "'" +
                " AND \"IVA_AST_AST_ID\" IN " + assetList + " FOR UPDATE";
        Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > valuesToCheck = sessionThread->query<Wt::Dbo::ptr<InformationValue> >(queryString).limit(10);

        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "valuesToCheck size : " << valuesToCheck.size();
        if (valuesToCheck.size() < 1)
        {
            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << "Nothing to check";
            transaction.commit();
            return;
        }
        informationValueListSqlPrepared = getInformationValueListSqlPrepared(valuesToCheck, 1);
        sessionThread->execute("UPDATE \"T_INFORMATION_VALUE_IVA\" SET \"IVA_STATE\" = 1 WHERE \"IVA_ID\" IN " + informationValueListSqlPrepared);
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
        Wt::Dbo::Transaction transaction(*sessionThread);
        Wt::Dbo::ptr<Alert> alertPtr = sessionThread->query<Wt::Dbo::ptr<Alert> >
            ("SELECT ale FROM \"T_ALERT_ALE\" ale WHERE \"ALE_ID\" = ? AND \"ALE_DELETE\" IS NULL FOR UPDATE")
            .bind(idAlert).limit(1);
        if (!alertPtr)
        {
            ToolsEngine::log("info") << " [Class:AlertProcessor] " << " - " << " No alert for id : " << idAlert;
            return;
        }
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
            try
            {
                switch(alertCriteria)
                {          
                    case lt: 
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the lt comparison";
                        compareNumberValue(sessionThread,informationValueListSqlPrepared, ltPtr, alertValueToCompare, idAlert, lineNumber);
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the lt comparison";  
                        break;
                    case le:
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the le comparison";
                        compareNumberValue(sessionThread,informationValueListSqlPrepared, lePtr, alertValueToCompare, idAlert, lineNumber);
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the le comparison";
                        break;
                    case eq:
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the eq comparison";
                        compareNumberValue(sessionThread,informationValueListSqlPrepared, eqPtr, alertValueToCompare, idAlert, lineNumber);
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the eq comparison";
                        break;
                    case ne:
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the ne comparison";
                        compareNumberValue(sessionThread,informationValueListSqlPrepared, nePtr, alertValueToCompare, idAlert, lineNumber);
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the ne comparison";
                        break;                            
                    case ge:
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the ge comparison";
                        compareNumberValue(sessionThread,informationValueListSqlPrepared, gePtr, alertValueToCompare, idAlert, lineNumber);
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the ge comparison";
                        break;
                    case gt:
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the switch of the gt comparison";
                        compareNumberValue(sessionThread,informationValueListSqlPrepared, gtPtr, alertValueToCompare, idAlert, lineNumber);
                        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the gt comparison";
                        break;
                    default:
                        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << "switch operator selection failed";
                        break; 
                }
                break;
            }
            catch (Wt::Dbo::Exception e)
            {
                ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << " number fail : " << e.what();
            }
        case text:
            ToolsEngine::log("warning") << " [Class:AlertProcessor] " << " - " << "Text Alert not yet implemented";
            try
            {
                Wt::Dbo::Transaction transaction(*sessionThread);
                std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva WHERE \"IVA_ID\" IN " + informationValueListSqlPrepared;
                tbInformationValue valuesToCheck = sessionThread->query<Wt::Dbo::ptr<InformationValue> >(queryString);
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
    SessionPool::getInstance()->returnSession(sessionThread);
    
}

int AlertProcessor::getPosKey(int pluginId,int sourceId,int searchId,double valueNum, int unitId, std::string assetList)
{
    int res = -1;
    Session *session = SessionPool::getInstance()->getSession();
    try 
    {
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << " Getting pos key";
        Wt::Dbo::Transaction transaction(*session);
        
        std::string queryString("SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva "
                " WHERE \"IVA_STATE\" = 0 "
                " AND \"PLG_ID_PLG_ID\" = " + boost::lexical_cast<std::string>(pluginId) + ""
                " AND \"SRC_ID\" = " + boost::lexical_cast<std::string>(sourceId) + ""
                " AND \"SEA_ID\" = " + boost::lexical_cast<std::string>(searchId) + ""
                " AND \"INF_VALUE_NUM\" = " + boost::lexical_cast<std::string>(valueNum) + ""
                " AND \"INU_ID_INU_ID\" = " + boost::lexical_cast<std::string>(unitId) + ""
                " AND \"IVA_AST_AST_ID\" IN " + assetList + "");
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
    SessionPool::getInstance()->returnSession(session);
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

int AlertProcessor::compareNumberValue(Session * sessionCompare, std::string stringValuesToCheck,bool (*mathOperator)(double,double), double valueSetInDb, long long idAlert, int lineNumber)
{
    
    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are entering in the comparingNumberValue method";
    try
    {
        Transaction transaction(*sessionCompare);
        std::string queryString = "SELECT iva FROM \"T_INFORMATION_VALUE_IVA\" iva WHERE \"IVA_ID\" IN " + stringValuesToCheck + " FOR UPDATE";
        ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - Compare number value query String : " << queryString;
        tbInformationValue valuesToCheck = sessionCompare->query<Wt::Dbo::ptr<InformationValue> >(queryString);
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
                    alertSender->send(sessionCompare,idAlert,*i);
                    i->modify()->state = 2;
                    delete alertSender;
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
                    alertSender.send(sessionCompare,idAlert,*i);
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
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertProcessor] " << " - " << " comparing numbervalue catch " << e.what();
    }
            
    ToolsEngine::log("debug") << " [Class:AlertProcessor] " << " - " << "we are at the end of the for()";
}