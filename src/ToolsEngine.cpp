#include "ToolsEngine.h"

ToolsEngine::ToolsEngine() {
}

ToolsEngine::~ToolsEngine() {
}

//Converting an wstring into int
int ToolsEngine::wstringToInt(std::wstring str)
{
    int intConv;
    size_t size = str.size() + 1;
    char * buffer = new char[ size ];
    //strncpy( buffer, str.c_str(), size );
    wcstombs(buffer,str.c_str(), size );
    intConv= atoi(buffer);
    delete [] buffer;
    size = 0;
    return intConv;
}

//Converting an string into int
int ToolsEngine::stringToInt(std::string str)
{
    int intConv;
    size_t size = str.size() + 1;
    char * buffer = new char[ size ];
    strncpy( buffer, str.c_str(), size );
    //wcstombs(buffer,str.c_str(), size );
    intConv= atoi(buffer);
    delete [] buffer;
    size = 0;
    return intConv;
}