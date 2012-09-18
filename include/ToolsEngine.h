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
#include <stdio.h>

#include <tools/Session.h>
#include <Wt/WLogger>

//include for config file
#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <boost/thread/mutex.hpp>
#include <Wt/WIOService>

class ToolsEngine;

extern ToolsEngine *te;


class ToolsEngine {
public:
    /**
     * class' builder
     */       
    ToolsEngine();
    virtual ~ToolsEngine();
    
   /**
    * method to load the config file
    * @param file location
    * @return success 0 or error -1
    */     
    int configFileLoad(std::string fileLocation);

    Session *sessionParser;
    Session *sessionAlertProcessor;    
    static Wt::WLogger logger;
    static Wt::WLogEntry log(std::string criticity);
    static int criticity; //log criticity
    std::string sqlCredentials;
    int sleepThreadReadDatasMilliSec; //the milliseconds to wait between each loop in our process (reading the database for new info
    int sleepThreadCheckAlertMilliSec; //the milliseconds to wait between each loop in our process ( calculate alerts)
    Wt::WIOService *ioService; //ioservice used for the http client
protected:
    static bool alreadyCreated;
    static boost::mutex mutex;
    enum logCriticity{debug = 1,info = 2, warning = 3, secure = 4, error = 5, fatal = 6};


};

// extern tells the compiler this variable is declared elsewhere


#endif	/* TOOLS_H */

