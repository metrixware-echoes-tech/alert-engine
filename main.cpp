#include "Parser.h"
#include "AlertProcessor.h"
#include <stdlib.h>
#include <stdio.h>
#include <Wt/Dbo/Dbo>
#include <tools/Session.h>
#include "ToolsEngine.h"
#include <boost/thread/thread.hpp>
//include for config file
#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

 
void checkNewDatas();
void checkNewAlerts();

std::string ToolsEngine::sqlCredentials = "hostaddr=172.16.3.101 port=5432 dbname=echoes user=echoes password=toto";
int ToolsEngine::sleepThreadMilliSec = 10;

Session ToolsEngine::sessionParser(ToolsEngine::sqlCredentials);
Session ToolsEngine::sessionAlertProcessor(ToolsEngine::sqlCredentials);
Wt::WLogger ToolsEngine::logger;


int main()
{
   /* Parser a;
    std::string toto;
    toto.assign("[prop@5875 ver=1 probe=12][res2@5875 offset=15 81-4-15-6-2=\"543\" 8-4-51-6-1=\"54546\"][res1@5875 offset=75 844-4-5-456-2=\"129873\" 8-445-5-645-1=\"pojl\"]");
    a.unserializeStructuredData(toto); */
    
    
    //création des tables de la bdd (to remove)
    try 
        {
            ToolsEngine::sessionParser.createTables();
            std::cerr << "Created database." << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Using existing database";
        }
    
    ToolsEngine::logger.setFile("/tmp/engine.log");
    ToolsEngine::logger.addField("type",false);
    ToolsEngine::logger.addField("datetime",false);
    ToolsEngine::logger.addField("message", true);
    
    //load the config file
    std::ifstream configFile("engine.conf");
    if(!configFile)
    {
        ToolsEngine::log("error") << " [Class:main] "<< " Config file not found";
        return 1;
    }
    std::set<std::string> options;
    std::map<std::string, std::string> parameters;
    options.insert("*");
    
    //reading the config file
    try
    {
        for(boost::program_options::detail::config_file_iterator i(configFile, options), e; i != e ; ++i)
            {
                ToolsEngine::log("info") << " [Class:main] "<< " Config file reading :" << i->string_key <<"  " << i->value[0];
                parameters[i->string_key] = i->value[0];
            }
    }
    catch(std::exception& e)
    {
            ToolsEngine::log("error") << " [Class:main] "<< "config file reading failed : " << e.what();
    }  
    
    
    // thread's creation
    boost::thread_group threadsEngine;
   // boost::thread threadCheckNewDatas; 
    //boost::thread threadCheckNewAlerts;
    
    // execute the method checkNewDatas() et checkNewAlerts() in parallel
    threadsEngine.create_thread(&checkNewDatas);
    threadsEngine.create_thread(&checkNewAlerts);
 
    // wait the end of the created thread
    threadsEngine.join_all();
    
    return 0;
}

void checkNewDatas()
{
    Parser *parser = new Parser();
    //result
    int res = -1;
    
    while (true)
    {
        //SQL session
        {
            Wt::Dbo::Transaction transaction(ToolsEngine::sessionParser);
            Wt::Dbo::ptr<Syslog> receivedSyslog = ToolsEngine::sessionParser.find<Syslog>().where("\"SLO_STATE\" = ?").limit(1).bind("0");
            if (receivedSyslog )
            {
                // state is 0 is "new entry" state = 1 is "processing"
                receivedSyslog.modify()->state = 1;
                try
                {
                    res = parser->unserializeStructuredData(receivedSyslog);
                    if (res == 0)
                    {
                        //state = 2 is "processing complete"
                        receivedSyslog.modify()->state = 2;                     
                    }
                    else if ( res == -1)
                    {
                        //state = 3 is "error"
                        receivedSyslog.modify()->state = 3;
                    }
                }
                catch (Wt::Dbo::Exception e)
                {   
                        ToolsEngine::log("info") << " [Class:main] "<< e.what();
                }      
            }

        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(ToolsEngine::sleepThreadMilliSec));
    };
}

void checkNewAlerts()
{
    AlertProcessor alertProcessor;
    alertProcessor.VerifyAlerts();
}