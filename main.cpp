/* 
 * Main
 * @author ECHOES Technologies (RHI-FPO)
 * @date 20/02/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS
 * WITHOUT COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013-2014 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "Server.h"

using namespace std;

/**
 * Main function
 * @param argc Number of arguments passed to the program
 * @param argv Array of arguments passed to the program
 * @return Exit status
 */
int main(int argc, char **argv)
{
    int res = EXIT_FAILURE;
    int signum = 0;
    const string name = "ECHOES Alert - Engine";
    const string version = "0.1.0";

    do {
        res = EXIT_FAILURE;
        signum = 0;

        Server server(name, version);
        server.setServerConfiguration(argc, argv);

        if (server.start())
        {
            signum = server.waitForShutdown();

            logger.entry("info") << "[Main] Shutdown (signal = " << signum << ")";

            server.stop();

            res = EXIT_SUCCESS;
        }
    } while (signum == SIGHUP);

    return res;
}

