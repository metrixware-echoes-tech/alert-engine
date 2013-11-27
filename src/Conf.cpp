/* 
 * Engine Configuration
 * @author ECHOES Technologies (FPO)
 * @date 03/06/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "Conf.h"

using namespace std;

Conf conf;

Conf::Conf()
{
    setDBPort(0);
}

Conf::Conf(const Conf& orig)
{
    setPath(orig.getPath());
    setDBHost(orig.getDBHost());
    setDBPort(orig.getDBPort());
    setDBName(orig.getDBName());
    setDBUser(orig.getDBUser());
    setDBPassword(orig.getDBPassword());
    setSessConnectParams(_dbHost, _dbPort, _dbName, _dbUser, _dbPassword);
    setCriticity(orig.getCriticity());
    setAPIHost(orig.getAPIHost());
    setAPIPort(orig.getAPIPort());
    setId(orig.getId());
}

Conf::~Conf()
{
}

bool Conf::readProgramOptions(int argc, char **argv)
{
    bool res = false;
    
    // Declare the supported options.
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("help", "That is where you are, it displays help and quits.")
            ("logfile", boost::program_options::value<string>(), "logfile path")
            ("logcriticity", boost::program_options::value<unsigned short>(), "log criticity level : debug = 1 / info = 2 / warning = 3 / secure = 4 / error = 5/ fatal = 6")
            ("conffile", boost::program_options::value<string>(), "conffile path")
            ;

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help"))
    {
        cout << desc << "\n";
    }
    else
    {
#ifdef NDEBUG
        if (vm.count("logfile"))
        {
            logger.setFile(vm["logfile"].as<std::string>());
        }
        else
        {
            logger.setFile("/var/log/echoes-alert/engine.log");
        }
#endif

        if (vm.count("logcriticity"))
        {
            logger.setType(vm["logcriticity"].as<unsigned short>());
        }

        if (vm.count("conffile"))
        {
            setPath(vm["conffile"].as<string>());
            logger.entry("debug") << "[Conf] conf file = " << _path;
        }

        res = true;
    }

    return res;
}

bool Conf::readConfFile()
{
    bool res = false;

    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;
    
    // Load the INI file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
    try
    {
        boost::property_tree::read_ini(_path, pt);
        setId(pt.get<long long>("engine.id"));
        alerter = pt.get<bool>("engine.alerter");
        cleaner = pt.get<bool>("engine.cleaner");
        calculator = pt.get<bool>("engine.calculator");
        sleepThreadCheckAlert = pt.get<int>("engine.sleep-alert-reading");
        sleepThreadRemoveOldValues = pt.get<int>("engine.sleep-remove-old-values");
        sleepThreadCalculate = pt.get<int>("engine.sleep-calculate");
        
        setDBHost(pt.get<string>("database.host"));
        setDBPort(pt.get<unsigned>("database.port"));
        setDBName(pt.get<string>("database.dbname"));
        setDBUser(pt.get<string>("database.username"));
        setDBPassword(pt.get<string>("database.password"));
        setSessConnectParams(_dbHost, _dbPort, _dbName, _dbUser, _dbPassword);

        setAPIHost(pt.get<std::string>("api.host"));
        setAPIPort(pt.get<unsigned>("api.port"));

        logger.entry("info") << "[Conf] Conf file loaded";

        res = true;
    }
    catch (boost::property_tree::ini_parser_error e)
    {
        logger.entry("error") << "[Conf] " << e.what();
        logger.entry("fatal") << "[Conf] Can't load config file";
    }

    return res;
}

bool Conf::isInDB()
{
    bool res = false;

    Echoes::Dbo::Session session(_sessConnectParams);
    try
    {
        Wt::Dbo::Transaction transaction(session);
        Wt::Dbo::ptr<Echoes::Dbo::Engine> enginePtr = session.find<Echoes::Dbo::Engine>().where("\"ENG_ID\" = ?").bind(_id).limit(1);
        if (enginePtr)
        {
            res = true;
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[Conf] " << e.what();
    }

    return res;
}

bool Conf::isAlerter() const
{
    return this->alerter;
}
bool Conf::isCleaner() const
{
    return this->cleaner;
}
bool Conf::isCalculator() const
{
    return this->calculator;
}

void Conf::setPath(std::string path)
{
    _path = path;

    return;
}

string Conf::getPath() const
{
    return _path;
}

void Conf::setId(long long id)
{
    _id = id;
    return;
}

long long Conf::getId() const
{
    return _id;
}

string Conf::getDBHost() const
{
    return _dbHost;
}

void Conf::setDBPort(unsigned dbPort)
{
    _dbPort = dbPort;

    return;
}

void Conf::setDBHost(string dbHost)
{
    _dbHost = dbHost;

    return;
}

unsigned Conf::getDBPort() const
{
    return _dbPort;
}

void Conf::setDBName(string dbName)
{
    _dbName = dbName;

    return;
}

string Conf::getDBName() const
{
    return _dbName;
}

void Conf::setDBUser(string dbUser)
{
    _dbUser = dbUser;

    return;
}

string Conf::getDBUser() const
{
    return _dbUser;
}

void Conf::setDBPassword(string dbPassword)
{
    _dbPassword = dbPassword;

    return;
}

string Conf::getDBPassword() const
{
    return _dbPassword;
}

void Conf::setSessConnectParams
(
 string dbHost,
 unsigned dbPort,
 string dbName,
 string dbUser,
 string dbPassword
 )
{   
    _sessConnectParams = "hostaddr=" + dbHost +
                         " port=" + boost::lexical_cast<string>(dbPort) +
                         " dbname=" + dbName +
                         " user=" + dbUser +
                         " password=" + dbPassword;

    return;
}

string Conf::getSessConnectParams() const
{
    return _sessConnectParams;
}

string Conf::getAPIHost() const
{
    return _apiHost;
}

void Conf::setAPIPort(unsigned apiPort)
{
    _apiPort = apiPort;

    return;
}

void Conf::setAPIHost(string apiHost)
{
    _apiHost = apiHost;

    return;
}

unsigned Conf::getAPIPort() const
{
    return _apiPort;
}


void Conf::setCriticity(unsigned short criticity)
{
    _criticity = criticity;
    return;
}

unsigned short Conf::getCriticity() const
{
    return _criticity;
}

