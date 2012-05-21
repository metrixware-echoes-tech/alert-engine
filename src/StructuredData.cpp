#include "StructuredData.h"
#include "tools.h"
#include <vector>
#include <ctime>

StructuredData::StructuredData() {

Syslog syslogHeader("2012-05-08 10:17:01",
                "mymachine.example.com",
                "echoes-alert-probe",
                "3216",
                "ID47"
                );
time_t now;
now = time(NULL);


//calc reception date
syslogHeader.setReceptionDate(ctime(&now));
}



StructuredData::~StructuredData() {
}

int StructuredData::unserializeStructuredData(std::string& rawStructuredData)
{
    //[prop@5875 ver=1 probe=12]
    //[res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"][res1@5875 offset=75 8-4-5-6-2="123" 8-4-5-6-1="pojl"]

    size_t oBracket=-1; //sucessives positions of the open bracket
    size_t cBracket=-1; //sucessives positions of the closed bracket
    std::vector<size_t> posBrackets; // the list of the brackets positions
    //TODO: we may be use the -1 value of the previous closed bracket to know the value of the open next one
    std::string tempString; //the substring that contains the sd-element passed in argument
    bool prop=false; //we know if the properties sd-element is parsed
     
    //we search and save the different positions of the brackets in the rawStructuredData
    do
    {
        oBracket = rawStructuredData.find("[",oBracket+1);
        cBracket = rawStructuredData.find("]",cBracket+1);
        if ( oBracket != -1 || cBracket != -1 )
        {
                posBrackets.push_back(oBracket) ; //we save the position of the open bracket in the list
                posBrackets.push_back(cBracket) ; //we save the position of the close bracket in the list
        }   
    }while (oBracket != -1); 

    for (int i = 0 ; i < posBrackets.size() ; i +=2 )
    {   
        tempString.assign(rawStructuredData.substr(posBrackets.at(i)+1,posBrackets.at(i+1)-posBrackets.at(i)-1));           
        
        if (posBrackets.at(i) == 0 && prop==false )
        {     
            //we parse the first sd-element containing the properties of the message
            unserializeProperties(tempString);
            tempString.clear();
            //we have parsed the properties sd-element
            prop=true;
        }
        else{
            unserializeSDElement(tempString);
            tempString.clear();
        }     
    }
}

int StructuredData::unserializeProperties(std::string& strProperties)
{
    //example of string to parse : prop@5875 ver=1 probe=12
    //we parse the first sd-element
    //table to save the equal positions in the first sd-element
    size_t tbEquals[1];
    size_t space;
    tbEquals[0] = strProperties.find("=",0);
    space = strProperties.find(" ",tbEquals[0]+1);
    tbEquals[1] = strProperties.find("=",space);
    
    syslogHeader.setVersion(stringToInt(strProperties.substr(tbEquals[0]+1,space-(tbEquals[0]+1))));
    syslogHeader.setPrbId(stringToInt(strProperties.substr(tbEquals[1]+1,strProperties.length()-(tbEquals[1]+1))));  
    std::cout << "Version : " << syslogHeader.getVersion() <<std::endl;
    std::cout << "ProbeId : " << syslogHeader.getPrbId() << std::endl;     
    return 0;
}

int StructuredData::unserializeSDElement(std::string& strSDElement)
{
    //string to parse : res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"
    int offset=0;
    std::vector<std::string> idsPlusValue; // the list of 8-4-5-6-2="543" ids="val"
    std::vector<size_t> spaces; // the list of the spaces in the sub string
    size_t space=-1; //sucessives positions of the space
    std::string tempString; //temp string to save the value parsed before adding to the vector
    
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
    offset = stringToInt(strSDElement.substr(strSDElement.find("=",spaces.at(0))+1,spaces.at(1)-1));
    std::cout << "offset : " << offset << std::endl;
    
    for ( int i= 1 ; i < spaces.size()-1 ; i ++)
    {  
        idsPlusValue.push_back(strSDElement.substr(spaces.at(i)+1,spaces.at(i+1)-spaces.at(i)));
        std::cout << "idsPlusValue : " << strSDElement.substr(spaces.at(i)+1,spaces.at(i+1)-spaces.at(i)) <<std::endl;
    }
    //we add the last element to the vector
    idsPlusValue.push_back(strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()));
    std::cout << "idsPlusValue : " << strSDElement.substr(spaces.back()+1,strSDElement.size()-spaces.back()) <<std::endl; 

    //we unserialize each value
    for ( int i= 0 ; i < idsPlusValue.size() ; i ++)
    {  
        unserializeValue(idsPlusValue.at(i),offset);
    }
    return 0;
}

int StructuredData::unserializeValue(std::string& strValue, int offset)
{
    //reinit the temp Value
    tempValue.setIdAsset(0);
    tempValue.setIdPlugin(0);
    tempValue.setIdSearch(0);
    tempValue.setIdSource(0);
    tempValue.setNumSubSearch(0);
    tempValue.setValueCreatedDate("");
    tempValue.setValue("");
    
    //string to parse : 8-4-5-6-2="543"  
   
    //table to save the dashs positions between the ids
    size_t tbDashs[3];
    size_t dash=-1;
    
    //table to save the quote positions in the value field
    size_t tbQuotes[1]; 
    size_t quote=-1;    
    
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
    
    //idPlugin-idAsset-idSource-idSearch-numSubSearch="value"
    tempValue.setIdPlugin(stringToInt(strValue.substr(0,tbDashs[0])));
    tempValue.setIdAsset(stringToInt(strValue.substr(tbDashs[0]+1,tbDashs[1]-(tbDashs[0]+1))));   
    tempValue.setIdSource(stringToInt(strValue.substr(tbDashs[1]+1,tbDashs[2]-(tbDashs[1]+1)))); 
    tempValue.setIdSearch(stringToInt(strValue.substr(tbDashs[2]+1,tbDashs[3]-(tbDashs[2]+1))));
    tempValue.setNumSubSearch(stringToInt(strValue.substr(tbDashs[3]+1,tbDashs[4]-(tbDashs[3]+1))));
    tempValue.setValue(strValue.substr(tbQuotes[0]+1,tbQuotes[1]-(tbQuotes[0]+1)));
    
    std::cout << "Value unserialized : " << tempValue.getIdPlugin() << "-" << tempValue.getIdAsset() << "-" << tempValue.getIdSource() << "-" << tempValue.getIdSearch() << "-" << tempValue.getNumSubSearch() << "=" << "\""<< tempValue.getValue() << "\""<< std::endl; 
    valuesFifo.push(tempValue);
    return 0;
}