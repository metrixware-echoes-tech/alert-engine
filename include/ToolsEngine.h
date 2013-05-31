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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

#include "Logger.h"

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
    Session *sessionAlertProcessor;
    Session *sessionOldValues;
    Session *sessionCalculate;
//    void reloadSessionCalculate();
    static int criticity; //log criticity
    std::string sqlCredentials;
    std::string apiHost;
    unsigned apiPort;
    int sleepThreadCheckAlert; //the seconds to wait between each loop in our process ( calculate alerts)
    int sleepThreadRemoveOldValues; //the seconds to wait between each old values cleaning
    int sleepThreadCalculate;
    bool isAlerter();
    bool isCleaner();
    bool isCalculator();
    
    long long getId() const;
    bool isInDB();

protected:
    static bool alreadyCreated;
    enum logCriticity{debug = 1,info = 2, warning = 3, secure = 4, error = 5, fatal = 6};
    bool alerter;
    bool cleaner;
    bool calculator;

    private:
        long long _id;

        void setId(long long id);

};

// extern tells the compiler this variable is declared elsewhere


#endif	/* TOOLS_H */

