/* 
 * Main
 * @author ECHOES Technologies (RHI)
 * @date 20/02/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS
 * WITHOUT COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include <tools/SessionPool.h>

#include "Logger.h"
#include "EAEngine.h"

using namespace std;

SessionPool* SessionPool::instance = 0;
string SessionPool::credentials = "";
boost::mutex SessionPool::mutex;

/**
 * Main function
 * @param argc Number of arguments passed to the program
 * @param argv Array of arguments passed to the program
 * @return Exit status
 */
int main(int argc, char **argv)
{
    int res = EXIT_FAILURE, signum = 0;
    const string name = "ECHOES Alert - Engine", version = "0.1.0";

    do {
        res = EXIT_FAILURE;
        signum = 0;

        EAEngine engine(name, version);
        engine.setServerConfiguration(argc, argv);
        
        if (engine.start())
        {
            signum = engine.waitForShutdown();

            logger.entry("info") << "[Main] Shutdown (signal = " << signum << ")";

            engine.stop();

            res = EXIT_SUCCESS;
        }
    } while (signum == SIGHUP);

    return res;
}

