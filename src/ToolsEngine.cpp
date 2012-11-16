#include "ToolsEngine.h"


bool ToolsEngine::alreadyCreated = false;


ToolsEngine::ToolsEngine(std::string confFile) {
    if (alreadyCreated)
    {
            ToolsEngine::log("error") << " [Class:ToolsEngine] " << "Can't create a second instance of the singleton class";
    }
    // Sinon, on construit la classe et on déclare l'objet créé
    alreadyCreated = true;
    
    //loading config file
    if (configFileLoad(confFile) == -1)
    {
        ToolsEngine::log("fatal") << " [Class:ToolsEngine] " << "Can't load config file";
        exit(0);
    }
    //creating SQL sessions
    sessionParser = new Session(sqlCredentials);
    sessionParserGlobal = new Session(sqlCredentials);
    sessionAlertProcessor = new Session(sqlCredentials);
    sessionOldValues = new Session(sqlCredentials);
    
    ioService = new Wt::WIOService();
    ioService->start();
}

ToolsEngine::~ToolsEngine() {
    // Si on veut pouvoir recréer la classe plus tard, on déclare l'objet non-existant
    alreadyCreated = false;    
    ioService->stop();
}

Wt::WLogEntry ToolsEngine::log(std::string logCriticity)
{
    boost::mutex::scoped_lock scoped_lock(ToolsEngine::mutex);
    return ToolsEngine::logger.entry(logCriticity) << logCriticity << Wt::WLogger::sep << Wt::WLogger::timestamp << Wt::WLogger::sep << (unsigned int)pthread_self() << Wt::WLogger::sep;
    boost::mutex::scoped_lock scoped_unlock(ToolsEngine::mutex);
}


int ToolsEngine::configFileLoad(std::string fileLocation)
{
    int result = -1;
    
    //load the config file
    std::ifstream configFile(fileLocation.data());
    if(!configFile)
    {
        ToolsEngine::log("error") << " [Class:ToolsEngine] "<< " Config file not found";
    }
    std::set<std::string> options;
    std::map<std::string, std::string> parameters;
    options.insert("*");
    
    //reading the config file
    try
    {
        for(boost::program_options::detail::config_file_iterator i(configFile, options), e; i != e ; ++i)
        {
            ToolsEngine::log("debug") << " [Class:main] "<< " Config file reading :" << i->string_key <<"  " << i->value[0];
            parameters[i->string_key] = i->value[0];
        }
        result = 0;
    }
    catch(std::exception& e)
    {
            ToolsEngine::log("error") << " [Class:main] "<< "Config file reading failed : " << e.what();
    }  
    //filling variables with the collected datas in the config file
    //parcourir la map !!       
    sqlCredentials = "hostaddr=" + parameters["database-hostname"] + 
                     " port=" + parameters["database-port"] + 
                     " dbname=" + parameters["database-name"] +
                     " user=" + parameters["database-login"] +
                     " password=" + parameters["database-password"];
    apiUrl = parameters["api-url"];
    sleepThreadReadDatasMilliSec = boost::lexical_cast<int>(parameters["sleep-database-reading"]);
    sleepThreadCheckAlertMilliSec = boost::lexical_cast<int>(parameters["sleep-alert-reading"]);
    sleepThreadRemoveOldValues = boost::lexical_cast<int>(parameters["sleep-remove-old-values"]);
    //criticity = boost::lexical_cast<int>(parameters["log-criticity"]);
    //set the log criticity
    
    switch (criticity)
    {
        case debug:
        {
                ToolsEngine::logger.configure("*");
                break;
        }
        case info:
        {
                ToolsEngine::logger.configure("* -debug");
                break;
        } 
        case warning:
        {
                ToolsEngine::logger.configure("* -debug - info");
                break;
        } 
        case secure:
        {
                ToolsEngine::logger.configure("* -debug - info -warning");
                break;
        } 
        case error:
        {
                ToolsEngine::logger.configure("* -debug - info -warning -secure");
                break;
        }  
        case fatal:
        {
                ToolsEngine::logger.configure("* -debug - info -warning -secure -error");
                break;
        }
        default:
        {
                ToolsEngine::logger.configure("* -debug");
                break;
        }               
      }
//      ToolsEngine::log("info") << " [Class:main] "<< sqlCredentials;
//      ToolsEngine::log("info") << " [Class:main] "<< sleepThreadReadDatasMilliSec;
//      ToolsEngine::log("info") << " [Class:main] "<< sleepThreadCheckAlertMilliSec;
      
      return result;
}