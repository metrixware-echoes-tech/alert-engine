#include "PostgresConnector.h"
//#include "User.h"

namespace odb = Wt::Dbo;
using namespace std;

PostgresConnector::PostgresConnector(string databaseName,string userName,string databaseURL,string databasePort,string userPwd)
{
    this->databaseName = databaseName;
    this->userName = userName;
    this->databaseURL = databaseURL;
    this->databasePort = databasePort;
    this->userPwd = userPwd;

    this->session = new odb::Session();

    this->connect();
}

PostgresConnector::~PostgresConnector()
{
    //dtor
}


void PostgresConnector::connect()
{
    odb::backend::Postgres pg("hostaddr=127.0.0.1 port=5432 dbname=echoes user=echoes password=toto");
    pg.setProperty("show-queries", "true");
    this->session->setConnection(pg);

    //string classShortName = "_USER_";
    //string className = User::TABLE_PREFIX.c_str()+classShortName+User::getTrigram().c_str();

    //this->session->mapClass<User>(className.c_str());

    /*
     * Try to create the schema (will fail if already exists).
     */
    //this->session->dropTables();
    //this->session->createTables();
}

odb::Session * PostgresConnector::getSession()
{
    return this->session;
}
