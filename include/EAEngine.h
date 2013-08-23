/* 
 * Header of Engine
 * @author ECHOES Technologies (FPO)
 * @date 21/08/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS
 * WITHOUT COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef EAENGINE_H
#define	EAENGINE_H

#include <csignal>

#include "Conf.h"
#include "Logger.h"
#include "AlertProcessor.h"

class EAEngine
{
    public:
        EAEngine(const std::string& name, const std::string& version);
        EAEngine(const EAEngine& orig);
        virtual ~EAEngine();

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
        
    private:
        /**
         * Set up signals handler for every signals
         */
        void signalsHangler();
        /**
         * Unix Signal Handling
         * @param signum Signal number
         */
        static void signalHandling(int signum);

        void checkNewAlerts();
        void removeOldValues();
        void calculate();

        bool _confOK;
        std::string _name, _version;
        
        static boost::thread_group _threads;
        static int _signum;
};

#endif	/* EAENGINE_H */

