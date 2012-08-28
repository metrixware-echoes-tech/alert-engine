#include "Parser.h"

Parser::Parser() {
}

Parser::~Parser() {
}

int Parser::unserializeStructuredData(Wt::Dbo::ptr<Syslog> ptrSyslog)
{
    //[prop@5875 ver=1 probe=12]
    //[res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"][res1@5875 offset=75 8-4-5-6-2="123" 8-4-5-6-1="pojl"]
    
    size_t oBracket=-1; //sucessives positions of the open bracket
    size_t cBracket=-1; //sucessives positions of the closed bracket
    posBrackets.clear();
    //TODO: we may be use the -1 value of the previous closed bracket to know the value of the open next one
    std::string tempString; //the substring that contains the sd-element passed in argument
    bool prop=false; //we know if the properties sd-element is parsed
    Wt::Dbo::ptr<Syslog> ptrSyslogTmp;
    
    //result
    int res=-1;
    
    //we search and save the different positions of the brackets in the rawStructuredData
    do
    {
        //SQL session
        {
            Wt::Dbo::Transaction transaction(ToolsEngine::sessionParser);
            //we fill the local copy of the syslo pointer with the id of the received syslog
            ptrSyslogTmp = ToolsEngine::sessionParser.find<Syslog>().where("\"SLO_ID\" = ?").bind(ptrSyslog.id());
            oBracket = ptrSyslogTmp.get()->sd.value().find('[',oBracket+1);
            cBracket = ptrSyslogTmp.get()->sd.value().find(']',cBracket+1);
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
        {
            Wt::Dbo::Transaction transaction(ToolsEngine::sessionParser);
            tempString.assign(ptrSyslogTmp.get()->sd.toUTF8().substr(posBrackets.at(i)+1,posBrackets.at(i+1)-posBrackets.at(i)-1));                   
        }
        
        if (posBrackets.at(i) == 0 && prop==false )
        {     
            //we parse the first sd-element containing the properties of the message
            if (unserializeProperties(tempString, ptrSyslogTmp) == 0)
            {
                tempString.clear();
                //we have parsed the properties sd-element
                prop=true;
            }
            
        }
        else
        {
            if (unserializeSDElement(tempString, ptrSyslog) == 0)
            {
                tempString.clear();
                res = 0;
            }
        }
    }
    return res;
}

int Parser::unserializeProperties(std::string& strProperties, Wt::Dbo::ptr<Syslog> ptrSyslog)
{
    //example of string to parse : prop@5875 ver=1 probe=12
    //we parse the first sd-element
    //table to save the equal positions in the first sd-element
    size_t tbEquals[1];
    size_t space;
    tbEquals[0] = strProperties.find('=',0);
    space = strProperties.find(' ',tbEquals[0]+1);
    tbEquals[1] = strProperties.find('=',space);
    Wt::Dbo::ptr<Probe> ptrProbe;
    int idProbeTmp;
    Wt::Dbo::ptr<Syslog> ptrSyslogTmp;
    
    //result
    int res = -1;
    
    
    //parse idProbe :
    idProbeTmp = ToolsEngine::stringToInt(strProperties.substr(tbEquals[1]+1,strProperties.length()-(tbEquals[1]+1)));
    
    //SQL session
    {
        try 
        {                         
            Wt::Dbo::Transaction transaction(ToolsEngine::sessionParser);
            //we fill the local copy of the syslo pointer with the id of the received syslog
            ptrSyslogTmp = ToolsEngine::sessionParser.find<Syslog>().where("\"SLO_ID\" = ?").bind(ptrSyslog.id());
            ptrSyslogTmp.modify()->version = ToolsEngine::stringToInt(strProperties.substr(tbEquals[0]+1,space-(tbEquals[0]+1)));      

            //we find the probe that have the id of the received syslog and get its pointer
            ptrProbe = ToolsEngine::sessionParser.find<Probe>().where("\"PRB_ID\" = ?").bind(idProbeTmp);             

            //we modify the probe in the local copy of the syslog pointer with the getted object
            ptrSyslogTmp.modify()->probe = ptrProbe;
            res = 0;
        }
        catch (Wt::Dbo::Exception e)
        {
            res = -1;
            ToolsEngine::log("error") << " [Class:Parser] " << e.what();           
        }
    } 
    return res;
}

int Parser::unserializeSDElement(std::string& strSDElement, Wt::Dbo::ptr<Syslog> ptrSyslog)
{
    //string to parse : res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"
    int offset=0;
    size_t space=-1; //sucessives positions of the space
    std::string tempString; //temp string to save the value parsed before adding to the vector
    
    idsPlusValue.clear();
    spaces.clear();
    
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
    
    //get the offset
    offset = ToolsEngine::stringToInt(strSDElement.substr(strSDElement.find("=",spaces.at(0))+1,spaces.at(1)-1));
    ToolsEngine::log("info") << " [Class:Parser] "<< "offset : " << offset;
    
    
    //we add the only element to the vector
    if (spaces.size() == 2)
    {
        idsPlusValue.push_back(strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()));
        ToolsEngine::log("info") << " [Class:Parser] "<< "idsPlusValue : " << strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()); 
    }
    //
    else
    {
        for ( int i= 1 ; i < spaces.size()-1 ; i ++)
        {  
            idsPlusValue.push_back(strSDElement.substr(spaces.at(i)+1,spaces.at(i+1)-spaces.at(i)));
            ToolsEngine::log("info") << " [Class:Parser] " << strSDElement.substr(spaces.at(i)+1,spaces.at(i+1)-spaces.at(i));
        }
        idsPlusValue.push_back(strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()));
        ToolsEngine::log("info") << " [Class:Parser] " << strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()); 
    }
   
    //we unserialize each value
    for ( int i= 0 ; i < idsPlusValue.size() ; i ++)
    {  
        try
        {
            if ( unserializeValue(idsPlusValue.at(i),offset, ptrSyslog) == -1)
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

int Parser::unserializeValue(std::string& strValue, int offset, Wt::Dbo::ptr<Syslog> ptrSyslog)
{  
    Wt::WDateTime creaDate;
    sValue.clear();
    
    //string to parse : 8-4-5-6-2="543"  
   
    //table to save the dashs positions between the ids
    size_t tbDashs[3];
    size_t dash=-1;
    
    //table to save the quote positions in the value field
    size_t tbQuotes[1]; 
    size_t quote=-1; 
    
    //result
    int res = -1;
    
    //we search and save the different positions of the dashs in the strValue
    for(int i = 0 ; i < 4 ; i ++)
    {
        dash = strValue.find("-",dash+1);
        
        if ( dash != -1 )
        {
                tbDashs[i]=dash ; //we save the position of the space in the list
        }
    }
    
    //we search and save the different positions of the quotes in the strValue
    for(int i = 0 ; i < 2 ; i ++)
    {
        quote = strValue.find("\"",quote+1);
        
        if ( quote != -1 )
        {
                tbQuotes[i]=quote ; //we save the position of the space in the list
        }
    }
    
      //parsing of the value and the corresponding id(s)
      idPlugin = ToolsEngine::stringToInt(strValue.substr(0,tbDashs[0]));
      idAsset = ToolsEngine::stringToInt(strValue.substr(tbDashs[0]+1,tbDashs[1]-(tbDashs[0]+1)));   
      idSource = ToolsEngine::stringToInt(strValue.substr(tbDashs[1]+1,tbDashs[2]-(tbDashs[1]+1))); 
      idSearch = ToolsEngine::stringToInt(strValue.substr(tbDashs[2]+1,tbDashs[3]-(tbDashs[2]+1)));
      valueNum = ToolsEngine::stringToInt(strValue.substr(tbDashs[3]+1,tbDashs[4]-(tbDashs[3]+1)));
      sValue = Wt::Utils::base64Decode(strValue.substr(tbQuotes[0]+1,tbQuotes[1]-(tbQuotes[0]+1)));
   
   
    //SQL session
    { 
        try 
        {   
            Wt::Dbo::Transaction transaction(ToolsEngine::sessionParser);
            informationValueTmp = new InformationValue();
            Wt::Dbo::ptr<Information2> ptrInfTmp = ToolsEngine::sessionParser.find<Information2>()
                    .where("\"PLG_ID_PLG_ID\" = ?").bind(idPlugin)
                    .where("\"SRC_ID\" = ?").bind(idSource)
                    .where("\"SEA_ID\" = ?").bind(idSearch)
                    .where("\"INF_VALUE_NUM\" = ?").bind(valueNum);

            informationValueTmp->information = ptrInfTmp;
            informationValueTmp->value = sValue;

            //get sent date of the the associated syslog
            creaDate = ptrSyslog.get()->sentDate.addSecs(offset) ;

            informationValueTmp->creationDate = creaDate;

            informationValueTmp->syslog = ptrSyslog;

            Wt::Dbo::ptr<Asset> ptrAstTmp = ToolsEngine::sessionParser.find<Asset>()
                    .where("\"AST_ID\" = ?").bind(idAsset);

            informationValueTmp->asset = ptrAstTmp;
            
            // state : 0 = pending, 1 = processing, 2 = done    
            informationValueTmp->state = 0;

            ToolsEngine::sessionParser.add(informationValueTmp);
            res = 0;           
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << " [Class:Parser] " << e.what() ;
            res = -1;
        }
    } 
    return res;
}