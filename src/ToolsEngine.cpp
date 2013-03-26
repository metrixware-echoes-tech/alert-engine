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
        exit(1);
    }
    else
    {
        ToolsEngine::log("info") << " [Class:ToolsEngine] " << "conf file loaded";
    }
    //creating SQL sessions
    sessionParser = new Session(sqlCredentials);
    sessionAlertProcessor = new Session(sqlCredentials);
    sessionOldValues = new Session(sqlCredentials);
    sessionCalculate = new Session(sqlCredentials);
    
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
    ToolsEngine::mutex.lock();
    Wt::WLogEntry log = ToolsEngine::logger.entry(logCriticity) << logCriticity << Wt::WLogger::sep << Wt::WLogger::timestamp << Wt::WLogger::sep << (unsigned int)pthread_self() << Wt::WLogger::sep;
    ToolsEngine::mutex.unlock();
    return log;
}


int ToolsEngine::configFileLoad(std::string fileLocation)
{
    int result = -1;
    
    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;
    
    // Load the INI file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
    try
    {
        boost::property_tree::read_ini(fileLocation, pt);
        sqlCredentials = "hostaddr=" + pt.get<std::string>("database-hostname") + 
                     " port=" + pt.get<std::string>("database-port") + 
                     " dbname=" + pt.get<std::string>("database-name") +
                     " user=" + pt.get<std::string>("database-login") +
                     " password=" + pt.get<std::string>("database-password");
        apiUrl = pt.get<std::string>("api-url");
        sleepThreadCheckAlertMilliSec =pt.get<int>("sleep-alert-reading");
        sleepThreadRemoveOldValues = pt.get<int>("sleep-remove-old-values");
        sleepThreadCalculate = pt.get<int>("sleep-calculate");
        alerter = pt.get<bool>("alerter");
        cleaner = pt.get<bool>("cleaner");
        calculator = pt.get<bool>("calculator");
        result = 1;
    }
    catch (boost::property_tree::ini_parser_error e)
    {
        Wt::log("error") << "[TE] " << e.what();
    }
    

    switch (ToolsEngine::criticity)
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
                ToolsEngine::logger.configure("* -debug -info");
                break;
        } 
        case secure:
        {
                ToolsEngine::logger.configure("* -debug -info -warning");
                break;
        } 
        case error:
        {
                ToolsEngine::logger.configure("* -debug -info -warning -secure");
                break;
        }  
        case fatal:
        {
                ToolsEngine::logger.configure("* -debug -info -warning -secure -error");
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

//void ToolsEngine::reloadSessionCalculate()
//{
//    {
//        boost::lock_guard<boost::recursive_mutex> lock(mutexCalculate);
//        sessionCalculate->~Session();
//        sessionCalculate = new Session(sqlCredentials);
//    }
//    return;
//}

bool ToolsEngine::isAlerter()
{
    return this->alerter;
}
bool ToolsEngine::isCleaner()
{
    return this->cleaner;
}
bool ToolsEngine::isCalculator()
{
    return this->calculator;
}