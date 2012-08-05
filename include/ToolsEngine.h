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

#include <tools/Session.h>

class ToolsEngine {
public:
    /**
     * class' builder
     */       
    ToolsEngine();
    virtual ~ToolsEngine();

    static Session session;      
    static int wstringToInt(std::wstring str);
    static int stringToInt(std::string str);
};


#endif	/* TOOLS_H */

