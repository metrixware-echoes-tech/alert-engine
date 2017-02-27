/**
 * @file main.cpp
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

            log("info") << "Shutdown (signal = " << signum << ")";

            server.stop();

            res = EXIT_SUCCESS;
        }
    } while (signum == SIGHUP);

    return res;
}
