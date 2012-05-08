#include "StructuredData.h"
#include "tools.h"

StructuredData::StructuredData() {

Syslog syslogHeader("2012-05-08 10:17:01",
                "2012-05-08 10:17:03",
                "mymachine.example.com",
                "echoes-alert-probe",
                "3216",
                "ID47"
                );
}



StructuredData::~StructuredData() {
}

int StructuredData::unserializeStructuredData(std::string& rawStructuredData)
{
    //[prop@5875 ver=1 probe=12]
    //[res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"][res1@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"]

    //we parse the first block
    //table to save the equal positions in the first block
    size_t tbEquals[1];
    size_t space;
    size_t cBracket;
    tbEquals[0] = rawStructuredData.find("=",0);
    space = rawStructuredData.find(" ",tbEquals[0]+1);
    tbEquals[1] = rawStructuredData.find("=",space);
    cBracket = rawStructuredData.find("]",tbEquals[1]+1);
    
    syslogHeader.setVersion(stringToInt(rawStructuredData.substr(tbEquals[0]+1,space-(tbEquals[0]+1))));
    syslogHeader.setPrbId(stringToInt(rawStructuredData.substr(tbEquals[1]+1,cBracket-(tbEquals[1]+1))));    
    
    //we count the open bracket to know the number of blocks
    int countBracket=0;
    size_t oBracket; //sucessives positions of the bracket
    oBracket = rawStructuredData.find("[");
    while (oBracket != -1)
    {
        countBracket ++;
        std::cout << oBracket << std::endl;
        oBracket = rawStructuredData.find("[",oBracket+1);
    }
    //we substract the bracket of the first block that concerns properties
    countBracket = countBracket -1;
    std::cout << countBracket;
    return 1;
    
    for(int i=0; i=countBracket; i++)
    {
        
    }
}

int StructuredData::unserializeValue(std::string& strValue)
{
 /*
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
    
    return EXIT_SUCCESS;*/
}