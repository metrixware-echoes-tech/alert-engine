#include "ToolsEngine.h"


bool ToolsEngine::alreadyCreated = false;


ToolsEngine::ToolsEngine(std::string confFile) {
    if (alreadyCreated)
    {
        logger.entry("error") << "[Tools Engine] Can't create a second instance of the singleton class";
    }
    // Sinon, on construit la classe et on déclare l'objet créé
    alreadyCreated = true;
    
    //loading config file
    if (configFileLoad(confFile) == -1)
    {
        logger.entry("fatal") << "[Tools Engine] Can't load config file";
        exit(1);
    }
    else
    {
        logger.entry("info") << "[Tools Engine] Conf file loaded";
    }
    //creating SQL sessions
    sessionParser = new Session(sqlCredentials);
    sessionAlertProcessor = new Session(sqlCredentials);
    sessionOldValues = new Session(sqlCredentials);
    sessionCalculate = new Session(sqlCredentials);
}

ToolsEngine::~ToolsEngine() {
    // Si on veut pouvoir recréer la classe plus tard, on déclare l'objet non-existant
    alreadyCreated = false;
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
        setId(pt.get<long long>("engine.id"));
        alerter = pt.get<bool>("engine.alerter");
        cleaner = pt.get<bool>("engine.cleaner");
        calculator = pt.get<bool>("engine.calculator");
        sleepThreadCheckAlert = pt.get<int>("engine.sleep-alert-reading");
        sleepThreadRemoveOldValues = pt.get<int>("engine.sleep-remove-old-values");
        sleepThreadCalculate = pt.get<int>("engine.sleep-calculate");
        sqlCredentials = "hostaddr=" + pt.get<std::string>("database.host") + 
                     " port=" + pt.get<std::string>("database.port") + 
                     " dbname=" + pt.get<std::string>("database.dbname") +
                     " user=" + pt.get<std::string>("database.username") +
                     " password=" + pt.get<std::string>("database.password");
        apiHost = pt.get<std::string>("api.host");
        apiPort = pt.get<unsigned>("api.port");
        result = 1;
    }
    catch (boost::property_tree::ini_parser_error e)
    {
        logger.entry("error") << "[Tools Engine] " << e.what();
    }

    return result;
}

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

void ToolsEngine::setId(long long id)
{
    _id = id;
    return;
}

long long ToolsEngine::getId() const
{
    return _id;
}
    

bool ToolsEngine::isInDB()
{
    bool res = false;

    Session session(sqlCredentials);
    try
    {
        Wt::Dbo::Transaction transaction(session);
        Wt::Dbo::ptr<Engine> enginePtr = session.find<Engine>().where("\"ENG_ID\" = ?").bind(_id).limit(1);
        if (enginePtr)
        {
            res = true;
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[Tools Engine] " << e.what();
    }

    return res;
}


