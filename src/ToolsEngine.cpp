#include "ToolsEngine.h"


bool ToolsEngine::alreadyCreated = false;


ToolsEngine::ToolsEngine() {
    if (alreadyCreated)
    {
            std::cout << "Vous ne pouvez pas créer une seconde instance de la classe Singleton.\n";
    }
    // Sinon, on construit la classe et on déclare l'objet créé
    alreadyCreated = true;
    
    //loading config file
    configFileLoad("engine.conf");
    //creating SQL sessions
    sessionParser = new Session(sqlCredentials);
    sessionAlertProcessor = new Session(sqlCredentials);
    
    ioService = new Wt::WIOService();
    ioService->start();
}

ToolsEngine::~ToolsEngine() {
    // Si on veut pouvoir recréer la classe plus tard, on déclare l'objet non-existant
    alreadyCreated = false;    
    ioService->stop();
}

Wt::WLogEntry ToolsEngine::log(std::string criticity)
{
    boost::mutex::scoped_lock scoped_lock(ToolsEngine::mutex);
    return ToolsEngine::logger.entry(criticity) << criticity << Wt::WLogger::sep << Wt::WLogger::timestamp << Wt::WLogger::sep;
    boost::mutex::scoped_lock scoped_unlock(ToolsEngine::mutex);
}


void ToolsEngine::configFileLoad(std::string fileLocation)
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
                ToolsEngine::log("info") << " [Class:main] "<< " Config file reading :" << i->string_key <<"  " << i->value[0];
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
      sleepThreadReadDatasMilliSec = boost::lexical_cast<int>(parameters["sleep-database-reading"]);
      sleepThreadCheckAlertMilliSec = boost::lexical_cast<int>(parameters["sleep-alert-reading"]);
      
//      ToolsEngine::log("info") << " [Class:main] "<< sqlCredentials;
//      ToolsEngine::log("info") << " [Class:main] "<< sleepThreadReadDatasMilliSec;
//      ToolsEngine::log("info") << " [Class:main] "<< sleepThreadCheckAlertMilliSec;
      
   //   return result;
}