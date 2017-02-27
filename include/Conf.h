/**
 * @file Conf.h
 * @author Thomas Saquet, Florent Poinsaut
 * @date 
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Alert - Engine is a part of the Alert software
 * Copyright (C) 2013-2017
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
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
        bool isInDB(Echoes::Dbo::Session &session);
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
