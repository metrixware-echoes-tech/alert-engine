/** 
 * Toolbox
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-05-01
 */

#ifndef TOOLS_H
#define	TOOLS_H

#include <string>
#include <cstring>
#include <stdlib.h>

//Converting an string into int
int stringToInt(std::string str)
{
    int intConv;
    size_t size = str.size() + 1;
    char * buffer = new char[ size ];
    strncpy( buffer, str.c_str(), size );
    intConv= atoi(buffer);
    delete [] buffer;
    size = 0;
    return intConv;
}

#endif	/* TOOLS_H */

