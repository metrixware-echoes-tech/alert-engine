
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/Session>

#include "ToolsEngine.h"

#include "Parser.h"

Parser::Parser() {
}

Parser::~Parser() {
}

int Parser::unserializeStructuredData(long long ptrSyslogId)
{
    ToolsEngine::log("debug") << " [Class:Parser] " << " Unserialize StructuredData begin" ;    
    //[prop@5875 ver=1 probe=12]
    //[res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"][res1@5875 offset=75 8-4-5-6-2="123" 8-4-5-6-1="pojl"]
    
    size_t oBracket=-1; //sucessives positions of the open bracket
    size_t cBracket=-1; //sucessives positions of the closed bracket
    posBrackets.clear();

    
    std::string tempString; //the substring that contains the sd-element passed in argument
    bool prop=false; //we know if the properties sd-element is parsed

    
    //result
    int res=-1;
    
    //we search and save the different positions of the brackets in the rawStructuredData
    do
    {
        //SQL session
        try
        {
            Wt::Dbo::Transaction transaction1(*(te->sessionParser));
            //we fill the local copy of the syslo pointer with the id of the received syslog
            Wt::Dbo::ptr<Syslog> ptrSyslogTmp = te->sessionParser->find<Syslog>().where("\"SLO_ID\" = ?").bind(ptrSyslogId).limit(1);
            if (ptrSyslogTmp)
            {
                oBracket = ptrSyslogTmp.get()->sd.value().find('[',oBracket+1);
                cBracket = ptrSyslogTmp.get()->sd.value().find(']',cBracket+1);
            }
            else
            {
                ToolsEngine::log("error") << " [Class:Parser] " << "syslog id not found : " << ptrSyslogId;
            }
            transaction1.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:Parser] " << e.what();
        }
        
        if ( oBracket != -1 || cBracket != -1 )
        {
                posBrackets.push_back(oBracket) ; //we save the position of the open bracket in the list
                posBrackets.push_back(cBracket) ; //we save the position of the close bracket in the list
        }   
    }while (oBracket != -1); 

    for (int i = 0 ; i < posBrackets.size() ; i +=2 )
    {   
        //SQL session
        try
        {
            Wt::Dbo::Transaction transaction2(*(te->sessionParser));
            Wt::Dbo::ptr<Syslog> ptrSyslogTmp = te->sessionParser->find<Syslog>().where("\"SLO_ID\" = ?").bind(ptrSyslogId).limit(1);
            if (ptrSyslogTmp)
            {
                tempString.assign(ptrSyslogTmp.get()->sd.toUTF8().substr(posBrackets.at(i)+1,posBrackets.at(i+1)-posBrackets.at(i)-1));
            }
            else
            {
                ToolsEngine::log("error") << " [Class:Parser] " << "syslog id not found : " << ptrSyslogId;
            }
            transaction2.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:Parser] " << e.what();
        }
        
        if (posBrackets.at(i) == 0 && prop==false )
        {     
            //we parse the first sd-element containing the properties of the message
            if (unserializeProperties(tempString, ptrSyslogId) == 0)
            {
                tempString.clear();
                //we have parsed the properties sd-element
                prop=true;
            }
            else
            {
                return res;
            }
        }
        else
        {
            if (unserializeSDElement(tempString, ptrSyslogId) == 0)
            {
                tempString.clear();
                res = 0;
            }
            else
            {
                return res;
            }
        }
    }
    return res;
}

int Parser::unserializeProperties(std::string& strProperties, long long ptrSyslogId)
{
    ToolsEngine::log("debug") << " [Class:Parser] " << " Unserialize properties begin" ;
    //example of string to parse : prop@5875 ver=1 probe=12 token="tokentokentokentokentoken"
    
    //we parse the first sd-element
    std::vector<std::string> globalSplitResult;
    boost::split(globalSplitResult, strProperties, boost::is_any_of(" "), boost::token_compress_on);
    
    // 0 prop@5875
    // 1 ver=1 
    //2 probe=12 
    //3 token="tokentokentokentokentoken"
    
    std::vector<std::string> keyValueProbeIdSplitResult;
    boost::split(keyValueProbeIdSplitResult, globalSplitResult[2], boost::is_any_of("="), boost::token_compress_on);
    
    std::vector<std::string> keyValueVersionSplitResult;
    boost::split(keyValueVersionSplitResult, globalSplitResult[1], boost::is_any_of("="), boost::token_compress_on);
    
    std::vector<std::string> keyValueTokenSplitResult;
    boost::split(keyValueTokenSplitResult, globalSplitResult[3], boost::is_any_of("="), boost::token_compress_on);
    
    int idProbeTmp;
    std::string probeToken;
    
    //result
    int res = -1;

    //parse idProbe :
    idProbeTmp = boost::lexical_cast<int>(keyValueProbeIdSplitResult[1]);
    probeToken = boost::lexical_cast<std::string>(keyValueTokenSplitResult[1]);
    
    //SQL session
    try 
    {
        ToolsEngine::log("debug") << " [Class:Parser] " << " check token" ;
        Wt::Dbo::Transaction transaction(*(te->sessionParser));
        Wt::Dbo::ptr<Probe> ptrProbe = te->sessionParser->find<Probe>().where("\"PRB_ID\" = ?").bind(idProbeTmp).limit(1);
        
        if (ptrProbe.id() < 0)
        {
            ToolsEngine::log("error") << " [Class:Parser] Unknown probe.";
            transaction.commit();
            return res;
        }
        ToolsEngine::log("debug") << " [Class:Parser] Token received : " << probeToken;
        ToolsEngine::log("debug") << " [Class:Parser] Token organization : " << ptrProbe.get()->organization.get()->token.toUTF8();
                
        if (probeToken.compare("\"" + ptrProbe.get()->organization.get()->token.toUTF8() + "\"") != 0)
        {
            ToolsEngine::log("error") << " [Class:Parser] Token not matching organization token.";
            transaction.commit();
            return res;
        }
        else
        {
            ToolsEngine::log("debug") << " [Class:Parser] Token matching.";
        }
        
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        res = -1;
        ToolsEngine::log("error") << " [Class:Parser] " << e.what();           
    }
    
    //SQL session
    try 
    {
        ToolsEngine::log("debug") << " [Class:Parser] " << " transaction update slo opened" ;
        Wt::Dbo::Transaction transaction3(*(te->sessionParser));
        //we fill the local copy of the syslo pointer with the id of the received syslog
        Wt::Dbo::ptr<Syslog> ptrSyslogTmp = te->sessionParser->query<Wt::Dbo::ptr<Syslog> >("SELECT slo FROM \"T_SYSLOG_SLO\" slo WHERE \"SLO_ID\" = ? LIMIT 1 FOR UPDATE").bind(ptrSyslogId);
//        ptrSyslogTmp = te->sessionParser->find<Syslog>().where("\"SLO_ID\" = ?").bind(ptrSyslogId).limit(1);
        ptrSyslogTmp.modify()->version = boost::lexical_cast<int>(keyValueVersionSplitResult[1]);      

        //we find the probe that have the id of the received syslog and get its pointer
//            ptrProbe = te->sessionParser->find<Probe>().where("\"PRB_ID\" = ? FOR UPDATE").bind(idProbeTmp).limit(1);
        Wt::Dbo::ptr<Probe> ptrProbe = te->sessionParser->query<Wt::Dbo::ptr<Probe> >("SELECT prb FROM \"T_PROBE_PRB\" prb WHERE \"PRB_ID\" = ? LIMIT 1 FOR UPDATE").bind(idProbeTmp);

        //we modify the probe in the local copy of the syslog pointer with the getted object
        ptrSyslogTmp.modify()->probe = ptrProbe;

        Wt::Dbo::ptr<SyslogHistory> ptrSyslogHistoryTmp = te->sessionParser->query<Wt::Dbo::ptr<SyslogHistory> >("SELECT slh FROM \"T_SYSLOG_HISTORY_SLH\" slh WHERE \"SLH_ID\" = ? LIMIT 1 FOR UPDATE").bind(ptrSyslogId);
//        ptrSyslogHistoryTmp = te->sessionParser->find<SyslogHistory>().where("\"SLH_ID\" = ?").bind(ptrSyslogId).limit(1);
        if (ptrSyslogHistoryTmp)
        {
            ptrSyslogHistoryTmp.modify()->version = boost::lexical_cast<int>(keyValueVersionSplitResult[1]);      
            //we modify the probe in the local copy of the syslog pointer with the getted object
            ptrSyslogHistoryTmp.modify()->probe = ptrProbe;

            res = 0;
        }
        else
        {
            ToolsEngine::log("error") << " [Class:Parser] " << " slhnot found, id : " << ptrSyslogId ;
        }

        res = 0;
        transaction3.commit();
        ToolsEngine::log("debug") << " [Class:Parser] " << " transaction update slo commited" ;
    }
    catch (Wt::Dbo::Exception e)
    {
        res = -1;
        ToolsEngine::log("error") << " [Class:Parser] " << e.what();           
    }
        
    return res;
}

int Parser::unserializeSDElement(std::string& strSDElement, long long ptrSyslogId)
{
    ToolsEngine::log("debug") << " [Class:Parser] " << " Unserialize SDElement begin" ;
    //string to parse : res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"
    int offset=0;
    size_t space=-1; //sucessives positions of the space
    std::string tempString; //temp string to save the value parsed before adding to the vector
    
    idsPlusValue.clear();
    spaces.clear();
    
  //  std::cout << "SDElement : " << strSDElement <<"\n";
    
    //result
    int res = -1;
    
    //we search and save the different positions of the spaces in the strSDElement
    do
    {
        space = strSDElement.find(" ",space+1);

        if ( space != -1 )
        {
                spaces.push_back(space) ; //we save the position of the space in the list
        }   
    }while (space != -1); 
    
    offset = boost::lexical_cast<int>(strSDElement.substr(strSDElement.find("=",spaces.at(0))+1,(spaces.at(1)-1)-strSDElement.find("=",spaces.at(0))));
    ToolsEngine::log("debug") << " [Class:Parser] "<< "offset : " << offset;
    
    
    //we add the only element to the vector
    if (spaces.size() == 2)
    {
        idsPlusValue.push_back(strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()));
        ToolsEngine::log("debug") << " [Class:Parser] "<< "idsPlusValue : " << strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()); 
    }
    //
    else
    {
        for ( int i= 1 ; i < spaces.size()-1 ; i ++)
        {  
            idsPlusValue.push_back(strSDElement.substr(spaces.at(i)+1,spaces.at(i+1)-spaces.at(i)));
            ToolsEngine::log("debug") << " [Class:Parser] " << strSDElement.substr(spaces.at(i)+1,spaces.at(i+1)-spaces.at(i));
        }
        idsPlusValue.push_back(strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()));
        ToolsEngine::log("debug") << " [Class:Parser] " << strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()); 
    }
   
    //we unserialize each value
    for ( int i= 0 ; i < idsPlusValue.size() ; i ++)
    {  
        try
        {
            if ( unserializeValue(idsPlusValue.at(i),offset, ptrSyslogId) == -1)
            {
                res = -1;
            }
            else
            {
                res = 0;
            }
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:Parser] " << e.what() ;
            res = -1;
        }
    }
    return res;
}

int Parser::unserializeValue(std::string& strValue, int offset, long long ptrSyslogId)
{  
    ToolsEngine::log("debug") << " [Class:Parser] " << " Unserialize value begin" ;
    Wt::WDateTime creaDate;
    sValue.clear();
    int posKeyValue;
    
    //string to parse : 
    // 2-1-1-2-1-1-1="QXVnIDIxIDEwOg=="
  
    //result
    int res = -1;
    
    std::vector<std::string> keyValueSplitResult;
    boost::split(keyValueSplitResult, strValue, boost::is_any_of("="), boost::token_compress_on);
    
    std::string key = keyValueSplitResult[0];
    std::string value = keyValueSplitResult[1];
    
    //we remove the " in the value
    boost::erase_all(value, "\"");
    
    std::vector<std::string> keySplitResult;
    boost::split(keySplitResult, key, boost::is_any_of("-"), boost::token_compress_on);
    
      //parsing of the value and the corresponding id(s)
    idPlugin = boost::lexical_cast<int>(keySplitResult[0]);
    idAsset = boost::lexical_cast<int>(keySplitResult[1]);
    idSource = boost::lexical_cast<int>(keySplitResult[2]);
    idSearch = boost::lexical_cast<int>(keySplitResult[3]);
    valueNum = boost::lexical_cast<int>(keySplitResult[4]);
    lineNumber = boost::lexical_cast<int>(keySplitResult[6]);

    sValue = Wt::Utils::base64Decode(value);
   
    //SQL session
    {
        InformationValue *informationValueToAdd = new InformationValue();
        InformationHistoricalValue *informationHistoricalValueToAdd = new InformationHistoricalValue();
        long long ivaAddedId = -1;
        Wt::WString calculate = Wt::WString::Empty;
        try 
        {   
            ToolsEngine::log("debug") << " [Class:Parser] " << "Starting transaction to get values to process." ;
            Wt::Dbo::Transaction transaction5(*(te->sessionParser));
            // we have to check wether the asset exists or not (been deleted ?)
            Wt::Dbo::ptr<Asset> ptrAstTmp = te->sessionParser->find<Asset>()
                    .where("\"AST_ID\" = ?").bind(idAsset).where("\"AST_DELETE\" IS NULL").limit(1);
            
            if (!ptrAstTmp)
            {
                ToolsEngine::log("error") << " [Class:Parser] " << "Asset with id : " << idAsset << " doesn't exist." ;
                res = -1;
                transaction5.commit();
                return res;
            }
            
            Wt::Dbo::ptr<Syslog> ptrSyslogTmp = te->sessionParser->find<Syslog>().where("\"SLO_ID\" = ?").bind(ptrSyslogId);
            if (!ptrSyslogTmp)
            {
                ToolsEngine::log("error") << " [Class:Parser] " << "Syslog with id : " << ptrSyslogId << " doesn't exist." ;
                res = -1;
                transaction5.commit();
                return res;
            }
            
            
            //we verify the unit of the collected information before saving it linked ton an information entry.   
            Wt::Dbo::ptr<SearchUnit> ptrSearchUnit = te->sessionParser->find<SearchUnit>()
                    .where("\"PLG_ID_PLG_ID\" = ?").bind(idPlugin)
                    .where("\"SRC_ID\" = ?").bind(idSource)
                    .where("\"SEA_ID\" = ?").bind(idSearch)
                    .where("\"INF_VALUE_NUM\" = ?").bind(valueNum).limit(1); 
        
//            Wt::Dbo::Transaction transaction(*(te->sessionParser));
            Wt::Dbo::ptr<Information2> ptrInfTmp;
            ToolsEngine::log("debug") << " [Class:Parser] " << "looking for INF";
            if (ptrSearchUnit.get())
            {
                ToolsEngine::log("debug") << " [Class:Parser] " << "search unit : " << ptrSearchUnit.id() << "information_unit_id : " << ptrSearchUnit.get()->informationUnit.id();
                ptrInfTmp = te->sessionParser->find<Information2>()
                        .where("\"PLG_ID_PLG_ID\" = ?").bind(idPlugin)
                        .where("\"SRC_ID\" = ?").bind(idSource)
                        .where("\"SEA_ID\" = ?").bind(idSearch)
                        .where("\"INF_VALUE_NUM\" = ?").bind(valueNum)
                        .where("\"INU_ID_INU_ID\" = ?").bind(ptrSearchUnit.get()->informationUnit.id()).limit(1);
            }
            else
            {
                ToolsEngine::log("error") << " [Class:Parser] " << "No search unit retrieved." ;
                res = -1;
                transaction5.commit();
                return res;
            }
            ToolsEngine::log("debug") << " [Class:Parser] " << "Get calculate." ;
            //here we check whether we have to calculate something about the information
            ToolsEngine::log("debug") << " [Class:Parser] " << "Calculate this info ? : "<< ptrInfTmp.get();


            if (ptrInfTmp.get())
            {
                ToolsEngine::log("debug") << " [Class:Parser] " << "Info exists. Looking for : " 
                        << idSearch << "-"
                        << idSource << "-"
                        << idPlugin << "-"
                        << valueNum << "-"
                        << ptrSearchUnit.get()->informationUnit.id();
                ToolsEngine::log("debug") << " [Class:Parser] " << "calculate found.";
                if (ptrInfTmp.get()->calculate)
                {
                    if (!ptrInfTmp.get()->calculate.get().empty())
                    {
                        calculate = ptrInfTmp.get()->calculate.get();
                    }
                }
            }
            else
            {
                ToolsEngine::log("error") << " [Class:Parser] " << "No information retrieved." ;
                res = -1;
                transaction5.commit();
                return res;
            } 
            
            //get SLH
            Wt::Dbo::ptr<SyslogHistory> ptrSyslogHistory = te->sessionParser->find<SyslogHistory>().where("\"SLH_ID\" = ?").bind(ptrSyslogId);
                
            //get sent date of the the associated syslog
            creaDate = ptrSyslogTmp.get()->sentDate.addSecs(offset) ;
            informationValueToAdd->information = ptrInfTmp;
            informationValueToAdd->value = sValue;
            informationValueToAdd->creationDate = creaDate;
            informationValueToAdd->syslogHistory = ptrSyslogHistory;
            informationValueToAdd->lotNumber = lotNumber;
            informationValueToAdd->lineNumber = lineNumber;            
            informationValueToAdd->asset = ptrAstTmp;

            informationHistoricalValueToAdd->information = ptrInfTmp;
            informationHistoricalValueToAdd->value = sValue;
            informationHistoricalValueToAdd->creationDate = creaDate;
            informationHistoricalValueToAdd->syslogHistory = ptrSyslogHistory;
            informationHistoricalValueToAdd->lotNumber = lotNumber;
            informationHistoricalValueToAdd->lineNumber = lineNumber;            
            informationHistoricalValueToAdd->asset = ptrAstTmp;
            
            if (!calculate.empty())
            {
                informationHistoricalValueToAdd->state = 9;
                posKeyValue = ptrInfTmp.get()->pk.search.get()->pos_key_value;
                if (posKeyValue == 0)
                {
                    informationValueToAdd->state = 9;
                    
                }
                else
                {
                    // state : -1= lot not complete, 0 = pending, 1 = processing, 2 = done    
                    informationValueToAdd->state = 9;
                }
            }   
            else
            {
                informationHistoricalValueToAdd->state = 0;
                posKeyValue = ptrInfTmp.get()->pk.search.get()->pos_key_value;
                if (posKeyValue == 0)
                {
                    informationValueToAdd->state = 0;
                }
                else
                {
                    // state : -1= lot not complete, 0 = pending, 1 = processing, 2 = done    
                    informationValueToAdd->state = 0;
                }
            }
            
            Wt::Dbo::ptr<InformationValue> ptrIvaRes = te->sessionParser->add<InformationValue>(informationValueToAdd);
            Wt::Dbo::ptr<InformationHistoricalValue> ptrIhvRes = te->sessionParser->add<InformationHistoricalValue>(informationHistoricalValueToAdd);
            ptrIvaRes.flush();
            ivaAddedId = ptrIvaRes.id();
            transaction5.commit();


            res = 0; 
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:Parser] " << e.what() ;
            res = -1;
            return res;
        }
        
        
    } 
    ToolsEngine::log("debug") << " [Class:Parser] " << "End of value unserialization." ;  
    return res;
}