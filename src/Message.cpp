#include "Message.h"
#include "Value.h"
#include "tools.h"
#include <iostream>
#include <string>

Message::Message()
{
}

Message::~Message()
{
}

//Value Message::unserializeValue(std::string& strValue)
void Message::unserializeValue(std::string& strValue)
{
    //components of a value object
    int offset=0;
    unsigned int idPlugin;
    unsigned int idAsset;
    unsigned int idSource;
    unsigned int idSearch;
    std::string value;

    //string that gets the list of ids
    std::string ids;
    //table to save the quote positions in the value field
    size_t tbQuotes[3]; 
    //table to save the dashs positions in the value field
    size_t tbDashs[4];
 
    //string to parse : [ids="1-2-1-2" value="lkihazaz"]  
    //we search the quotes positions in the string
    tbQuotes[0] = strValue.find("\"",0);
    std::cout << "quote position "<< 1 << " : " << tbQuotes[0] << std::endl;
    for( int i=1; i<=3;i++)
    {
        tbQuotes[i] = strValue.find("\"",tbQuotes[i-1]+1);
        std::cout << "quote position "<< i+1 << " : " << tbQuotes[i] << std::endl;
    }
    
    //extracting the ids and the value
    ids = strValue.substr(tbQuotes[0]+1,tbQuotes[1]-(tbQuotes[0]+1));
    std::cout << "ids : "<< ids << std::endl; 
    
    value = strValue.substr(tbQuotes[2]+1,tbQuotes[3]-(tbQuotes[2]+1));
    std::cout << "value : "<< value << std::endl;
    
    //string to parse : 1-2-1-2
    //we search the dashs that separates the differents ids
    tbDashs[0] = ids.find("-",0);
    std::cout << "dash position "<< 1 << " : " << tbDashs[0] << std::endl;
    for( int i=1; i<=4;i++)
    {
        tbDashs[i] = ids.find("-",tbDashs[i-1]+1);
        std::cout << "dash position "<< i+1 << " : " << tbDashs[i] << std::endl;
    }
    
    //extracting the ids    
    //extracting idPlugin
    idPlugin= stringToInt(ids.substr(0,tbDashs[0]));
    std::cout << "idPlugin : "<< idPlugin << std::endl;

    //extracting idAsset
    idAsset= stringToInt(ids.substr(tbDashs[0]+1,tbDashs[1]-(tbDashs[0]+1)));
    std::cout << "idAsset : "<< idAsset << std::endl;
    
    //extracting idSource 
    idSource = stringToInt(ids.substr(tbDashs[1]+1,tbDashs[2]-(tbDashs[1]+1)));
    std::cout << "idSource : "<< idSource << std::endl;
    
    //extracting idSearch
    idSearch = stringToInt(ids.substr(tbDashs[2]+1,tbDashs[3]-(tbDashs[2]+1)));
    std::cout << "idSearch : "<< idSearch << std::endl;
    
    //the object to return
    //Value objValue(offset,idPlugin,idAsset,idSource,idSearch);
}