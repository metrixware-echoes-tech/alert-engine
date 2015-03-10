/* 
 * Header of Engine Server
 * @author ECHOES Technologies (RHI, FPO)
 * @date 24/02/2014
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2014 BY ECHOES TECHNOLGIES SAS
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
        
        void sendHttpRequestGet(string resource, vector<string> listParameter, boost::function<void (Wt::Json::Value)> functor, Wt::WString enoToken);
        void getResourceCallback(boost::system::error_code err, const Wt::Http::Message& response, Wt::Http::Client *client, boost::function<void (Wt::Json::Value)> functor);
        
        void sendHttpRequestPost(string resource, Wt::Http::Message *message, Wt::WString enoToken);
        void postResourceCallback(boost::system::error_code err, const Wt::Http::Message& response, Wt::Http::Client *client);

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

        void checkProbes();
        void isProbeAlive(Wt::Json::Value result);
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
        
        boost::thread * m_probeCheckingThread;
};

#endif	/* SERVER_H */

