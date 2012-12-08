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
#include <boost/program_options/detail/config_file.hpp>
#include <boost/config.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <Wt/WIOService>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

class ToolsEngine;

extern ToolsEngine *te;


class ToolsEngine {
public:
    /**
     * class' builder
     */       
    ToolsEngine(std::string confFile);
    virtual ~ToolsEngine();
    
   /**
    * method to load the config file
    * @param file location
    * @return success 0 or error -1
    */     
    int configFileLoad(std::string fileLocation);

    Session *sessionParser;
    Session *sessionParserGlobal;
    Session *sessionAlertProcessor;
    Session *sessionOldValues;
    Session *sessionCalculate;
    void reloadSessionCalculate();
    static Wt::WLogger logger;
    static Wt::WLogEntry log(std::string criticity);
    static int criticity; //log criticity
    std::string sqlCredentials;
    std::string apiUrl;
    std::string logFile;
    int sleepThreadReadDatasMilliSec; //the milliseconds to wait between each loop in our process (reading the database for new info)
    int sleepThreadCheckAlertMilliSec; //the milliseconds to wait between each loop in our process ( calculate alerts)
    int sleepThreadRemoveOldValues; //the milliseconds to wait between each old values cleaning
    int sleepThreadCalculate;
    Wt::WIOService *ioService; //ioservice used for the http client
    bool isParser();
    bool isAlerter();
    bool isCleaner();
    bool isCalculator();
protected:
    static bool alreadyCreated;
    static boost::mutex mutex;
    static boost::recursive_mutex mutexCalculate;
    enum logCriticity{debug = 1,info = 2, warning = 3, secure = 4, error = 5, fatal = 6};
    bool parser;
    bool alerter;
    bool cleaner;
    bool calculator;


};

// extern tells the compiler this variable is declared elsewhere


#endif	/* TOOLS_H */

