#include "Message.h"
#include <iostream>
#include <string>

Value Message::unserializeValue(std::string& strValue)
{
    unsigned int IdPlugin;
    unsigned int IdAsset;
    unsigned int IdSource;
    unsigned int IdSearch;
    std::string Value;
    
//in : [ids="1-2-1-2-4-2" value="lkihazaz"]
    std::cout << "before parsing data : " << strValue << std::endl;
    size_t foundIdFirst = strValue.find("\"",0,5);
    std::cout << "position 1er guillemet ids : " << foundIdFirst << std::endl;
    size_t foundIdSecond = strValue.find("\"",foundIdFirst+1);    
    std::cout << "position 2eme guillemet ids : " << foundIdSecond << std::endl;    
    
    
}

