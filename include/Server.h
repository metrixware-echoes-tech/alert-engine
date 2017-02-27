/**
 * @file Server.h
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

#ifndef SERVER_H
#define	SERVER_H

#include <csignal>

#include "Conf.h"
#include "AlertProcessor.h"

class Server
{
    public:
        Server(const std::string& name, const std::string& version);
        virtual ~Server();
        /**
         * Configures the ECHOES Alert Engine.
         * @param argc Number of arguments passed to the program
         * @param argv Array of arguments passed to the program
         */
        void setServerConfiguration(int argc, char **argv);
        /**
         * Starts the ECHOES Alert Engine in the background.
         * @return true if the ECHOES Alert Engine starts, false otherwise.
         */
        bool start();
        /**
         * 
         * @return 
         */
        int waitForShutdown();
        /**
         * Stop the ECHOES Alert Engine.
         */
        void stop();
        /**
         * A utility method to restart the ECHOES Alert Engine.
         * @param argc Number of arguments passed to the program
         * @param argv Array of arguments passed to the program
         * @param envp NULL-terminated array of "NAME=VALUE" environment variables
         */
        static void restart(int argc, char **argv, char **envp);

    private:
        /**
         * Set up signals handler for every signals
         */
        void signalsHandler();
        /**
         * Unix Signal Handling
         * @param signum Signal number
         */
        static void signalHandling(int signum);

        void checkNewAlerts();
        void removeOldValues();
        void calculate();

        bool m_optionsOK;
        const std::string m_name;
        const std::string m_version;
        const std::string m_pidPath;
        Echoes::Dbo::Session m_session;

        static boost::thread_group m_threads;
        static int m_signum;
};

#endif	/* SERVER_H */
