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

int Message::unserializeValue(std::string& strValue)
{
    //string that gets the list of ids
    std::string ids;
    //table to save the quote positions in the value field
    size_t tbQuotes[3]; 
    //table to save the dashs positions in the value field
    size_t tbDashs[4];
 
    //string to parse : [ids="1-2-1-2" value="lkihazaz"]  
    //we search the quotes positions in the string
    tbQuotes[0] = strValue.find("\"",0);
    for( int i=1; i<=3;i++)
    {
        tbQuotes[i] = strValue.find("\"",tbQuotes[i-1]+1);
    }
    
    //extracting the ids and the value
    ids = strValue.substr(tbQuotes[0]+1,tbQuotes[1]-(tbQuotes[0]+1));
    
    objValue.value = strValue.substr(tbQuotes[2]+1,tbQuotes[3]-(tbQuotes[2]+1));
    
    //string to parse : 1-2-1-2
    //we search the dashs that separates the differents ids
    tbDashs[0] = ids.find("-",0);
    for( int i=1; i<=4;i++)
    {
        tbDashs[i] = ids.find("-",tbDashs[i-1]+1);
    }
    
    //extracting the ids    
    //extracting idPlugin
    objValue.idPlugin= stringToInt(ids.substr(0,tbDashs[0]));
    //extracting idAsset
    objValue.idAsset= stringToInt(ids.substr(tbDashs[0]+1,tbDashs[1]-(tbDashs[0]+1)));   
    //extracting idSource 
    objValue.idSource = stringToInt(ids.substr(tbDashs[1]+1,tbDashs[2]-(tbDashs[1]+1))); 
    //extracting idSearch
    objValue.idSearch = stringToInt(ids.substr(tbDashs[2]+1,tbDashs[3]-(tbDashs[2]+1)));
    
    return EXIT_SUCCESS;
}