/* 
 * Header of Engine Configuration
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

#ifndef CONF_H
#define	CONF_H

#include <boost/config.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <tools/Session.h>

#include "Logger.h"

class Conf {
    public:
        Conf();
        Conf(const Conf& orig);
        virtual ~Conf();

        int sleepThreadCheckAlert; //the seconds to wait between each loop in our process ( calculate alerts)
        int sleepThreadRemoveOldValues; //the seconds to wait between each old values cleaning
        int sleepThreadCalculate;
        
        std::string getPath() const;
        long long getId() const;
        std::string getDBHost() const;
        unsigned getDBPort() const;
        std::string getDBName() const;
        std::string getDBUser() const;
        std::string getDBPassword() const;
        std::string getSessConnectParams() const;
        std::string getAPIHost() const;
        unsigned getAPIPort() const;
        unsigned short getCriticity() const;

        /**
         * Read the program options
         * @return Success: true or Error: false
         */
        bool readProgramOptions(int argc, char **argv);    
        /**
         * Read the config file
         * @return Success: true or Error: false
         */
        bool readConfFile();
        /**
         * Check if Engine ID is in database
         * @return True or False
         */
        bool isInDB();
        bool isAlerter() const;
        bool isCleaner() const;
        bool isCalculator() const;

    protected:
        std::string m_path;
        unsigned short m_criticity;

        long long m_id;

        std::string m_dbHost;
        unsigned m_dbPort;
        std::string m_dbName;
        std::string m_dbUser;
        std::string m_dbPassword;
        std::string m_sessConnectParams;

        std::string m_apiHost;
        unsigned m_apiPort;

        bool m_alerter;
        bool m_cleaner;
        bool m_calculator;

        void setPath(std::string path);
        void setId(long long id);
        void setDBPort(unsigned dbPort);
        void setDBPassword(std::string dbPassword);
        void setDBUser(std::string dbUser);
        void setDBName(std::string dbName);
        void setDBHost(std::string dbHost);
        void setSessConnectParams
        (
                std::string dbHost,
                unsigned dbPort,
                std::string dbName,
                std::string dbUser,
                std::string dbPassword
        );
        void setAPIHost(std::string apiHost);
        void setAPIPort(unsigned apiPort);
        void setCriticity(unsigned short criticity);
};

extern Conf conf;

#endif	/* CONF_H */

