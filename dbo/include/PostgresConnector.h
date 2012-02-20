#ifndef POSTGRESCONNECTOR_H
#define POSTGRESCONNECTOR_H

#include <string>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>


class PostgresConnector
{
    public:
        PostgresConnector(std::string databaseName,std::string userName,std::string databaseURL,std::string databasePort,std::string userPwd);
        virtual ~PostgresConnector();
        void connect();
        Wt::Dbo::Session * getSession();
    protected:
    private:
        std::string databaseName;
        std::string userName;
        std::string databaseURL;
        std::string databasePort;
        std::string userPwd;
        Wt::Dbo::Session * session;

};

#endif // POSTGRESCONNECTOR_H
