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
#include <Wt/WLogger>

class ToolsEngine {
public:
    /**
     * class' builder
     */       
    ToolsEngine();
    virtual ~ToolsEngine();

    static Session session;
    static Wt::WLogger logger;
    static int wstringToInt(std::wstring str);
    static int stringToInt(std::string str);
    static Wt::WLogEntry log(std::string criticity);
};


#endif	/* TOOLS_H */

