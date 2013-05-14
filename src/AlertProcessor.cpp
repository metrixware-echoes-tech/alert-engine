/* 
 * Engine Alert Processor
 * @author ECHOES Technologies (RHI, FPO)
 * @date 07/08/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "AlertProcessor.h"

using namespace std;

AlertProcessor::AlertProcessor() 
{
}

AlertProcessor::AlertProcessor(const AlertProcessor& orig)
{
}

AlertProcessor::~AlertProcessor()
{
}

int AlertProcessor::verifyAlerts()
{
    int res = -1;
    boost::thread_group threads;

    while (true)
    {
        try
        {
            Wt::Dbo::Transaction transaction(*(te->sessionAlertProcessor));

            Wt::Dbo::ptr<Engine> enginePtr = te->sessionAlertProcessor->find<Engine>().where("\"ENG_ID\" = ?").bind(boost::lexical_cast<string>(te->getId())).limit(1);
            
            Wt::Dbo::collection<Wt::Dbo::ptr<Alert>> alertPtrCollection = te->sessionAlertProcessor->find<Alert>()
                    .where("\"ALE_ENG_ENG_ID\" = ?").bind(boost::lexical_cast<string>(enginePtr.id()))
                    .where("\"ALE_DELETE\" IS NULL");

            ToolsEngine::log("debug") << "[Class:AlertProcessor] - We have " << alertPtrCollection.size() << " Alert(s) for this Engine in the database";

            for (Wt::Dbo::collection<Wt::Dbo::ptr<Alert>>::const_iterator it = alertPtrCollection.begin(); it != alertPtrCollection.end(); ++it)
            {
                if(_alertsMap.find(it->id()) == _alertsMap.end())
                {
                    Wt::Dbo::ptr<EngOrg> engOrgPtr = te->sessionAlertProcessor->find<EngOrg>()
                            .where("\"ENG_ID_ENG_ID\" = ?").bind(enginePtr.id())
                            .where("\"ORG_ID_ORG_ID\" = ?").bind(it->get()->alertValue->asset->organization.id())
                            .where("\"ENO_DELETE\" IS NULL")
                            .limit(1);

                    if(engOrgPtr)
                    {
                        _alertsMap[it->id()] = {
                            true,
#ifdef NDEBUG
                            "/opt/echoes-alert/engine/etc/sec-" + boost::lexical_cast<string>(it->id()) + ".conf",
#else
                            "conf/sec-" + boost::lexical_cast<string>(it->id()) + ".conf",
#endif
                            -1,
                            0,
                            0,
                            threads.create_thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id()))
                        };
                        startAlert(*it, engOrgPtr);
                    }
                    else
                        ToolsEngine::log("debug") << "[Class:AlertProcessor] - No Token for Alert: " << it->id();
                }
                else
                    _alertsMap[it->id()].check = true;
            }

            if (alertPtrCollection.size() < (unsigned)enginePtr->nbThread)
            {
                Wt::Dbo::collection<Wt::Dbo::ptr<Alert>> newAlertPtrCollection = te->sessionAlertProcessor->find<Alert>()
                        .where("\"ALE_ENG_ENG_ID\" is NULL")
                        .where("\"ALE_DELETE\" IS NULL")
                        .limit(enginePtr->nbThread - alertPtrCollection.size());

                ToolsEngine::log("debug") << "[Class:AlertProcessor] - We have " << newAlertPtrCollection.size() << " more Alert(s) for this Engine in the database";

                for (Wt::Dbo::collection<Wt::Dbo::ptr<Alert>>::const_iterator it = newAlertPtrCollection.begin(); it != newAlertPtrCollection.end(); ++it)
                {
                    Wt::Dbo::ptr<EngOrg> engOrgPtr = te->sessionAlertProcessor->find<EngOrg>()
                            .where("\"ENG_ID_ENG_ID\" = ?").bind(enginePtr.id())
                            .where("\"ORG_ID_ORG_ID\" = ?").bind(it->get()->alertValue->asset->organization.id())
                            .where("\"ENO_DELETE\" IS NULL")
                            .limit(1);

                    if(engOrgPtr)
                    {
                        it->modify()->engine = enginePtr;
                        it->flush();

                        _alertsMap[it->id()] = {
                            true,
#ifdef NDEBUG
                            "/opt/echoes-alert/engine/etc/sec-" + boost::lexical_cast<string>(it->id()) + ".conf",
#else
                            "conf/sec-" + boost::lexical_cast<string>(it->id()) + ".conf",
#endif
                            -1,
                            0,
                            0,
                            threads.create_thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id()))
                        };
                        startAlert(*it, engOrgPtr);
                    }
                    else
                        ToolsEngine::log("debug") << "[Class:AlertProcessor] - No Token for Alert: " << it->id();
                }
            }

            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << "[Class:AlertProcessor] - " << e.what();
        }

        vector<long long> alertToErase;
        for (map<long long, SecondStructure>::const_iterator it = _alertsMap.begin(); it != _alertsMap.end(); ++it)
        {
            if(it->second.check)
            {
                _alertsMap[it->first].check = false;
            }
            else
            {
                stopAlert(it->first);
                threads.remove_thread(it->second.ivaThread);
                alertToErase.push_back(it->first);
            }
        }

        for (unsigned i(0); i < alertToErase.size(); ++i)
        {
            _alertsMap.erase(alertToErase[i]);
        }
        
        boost::this_thread::sleep(boost::posix_time::seconds(10));
    }

    return res;
}

pid_t AlertProcessor::popen_sec(const string &confFilename, int *infp, int *outfp)
{
    int p_stdin[2], p_stdout[2];
    pid_t pid = 0;

    if (pipe(p_stdin) != 0 || pipe(p_stdout) != 0)
        return -1;

    pid = fork();

    if (pid < 0)
        return pid;
    else if (pid == 0)
    {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], READ);
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], WRITE);
        execl(
              "/usr/bin/sec",
              "sec",
              ("-conf=" + confFilename).c_str(),
              "-input=-",
#ifdef NDEBUG
              ("-log=" + te->logFile).c_str(),
#endif
              NULL
              );
        ToolsEngine::log("info") << "[Class:AlertProcessor] execl: " << strerror(errno);
        exit(1);
    }

    if (infp == NULL)
        close(p_stdin[WRITE]);
    else
        *infp = p_stdin[WRITE];

    if (outfp == NULL)
        close(p_stdout[READ]);
    else
        *outfp = p_stdout[READ];

    return pid;
}

void AlertProcessor::startAlert(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<EngOrg> engOrgPtr)
{
    ofstream secConfFile(_alertsMap[alertPtr.id()].secConfFilename.c_str());
    if(secConfFile)
    {
        secConfFile << "type=Single\n"
                "ptype=PerlFunc\n"
                "pattern= \\\n"
                "sub { \\\n"
                "  use strict; \\\n"
                "  if ($_[0] cmp '') \\\n"
                "  { \\\n"
                "    (my $id, my $value) = split(':', $_[0]); \\\n";

        if (alertPtr->alertValue->information->pk.unit->unitType.id() != Enums::NUMBER)
        {
            secConfFile << "    use MIME::Base64; \\\n"
                    "    $value = decode_base64($value); \\\n";
        }
        
        switch(alertPtr->alertValue->information->pk.unit->unitType.id())
        {
            case Enums::NUMBER:
                ToolsEngine::log("debug") << "[Class:AlertProcessor] - We are entering in the switch of the case number";

                secConfFile << "    if ($value =~ /^([+-]?)(?=\\d|\\.\\d)\\d*(\\.\\d*)?([Ee]([+-]?\\d+))?$/) \\\n"
                        "      { \\\n";

                switch(alertPtr->alertValue->alertCriteria.id())
                {
                    case Enums::LT: 
                        ToolsEngine::log("debug") << "[Class:AlertProcessor]- we are entering in the switch of the lt comparison";
                        secConfFile << "      if ($value < " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::LE:
                        ToolsEngine::log("debug") << "[Class:AlertProcessor] " << " - " << "we are entering in the switch of the le comparison";
                        secConfFile << "      if ($value <= " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::EQ:
                        ToolsEngine::log("debug") << "[Class:AlertProcessor] " << " - " << "we are entering in the switch of the eq comparison";
                        secConfFile << "      if ($value == " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::NE:
                        ToolsEngine::log("debug") << "[Class:AlertProcessor] " << " - " << "we are entering in the switch of the ne comparison";
                        secConfFile << "      if ($value != " << alertPtr->alertValue->value << ") \\\n";
                        break;                            
                    case Enums::GE:
                        ToolsEngine::log("debug") << "[Class:AlertProcessor] " << " - " << "we are entering in the switch of the ge comparison";
                        secConfFile << "      if ($value >= " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::GT:
                        ToolsEngine::log("debug") << "[Class:AlertProcessor] " << " - " << "we are entering in the switch of the gt comparison";
                        secConfFile << "      if ($value > " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    default:
                        ToolsEngine::log("error") << "[Class:AlertProcessor] " << " - " << "switch operator selection failed";
                        break; 
                }
                break;
            case Enums::TEXT:
                secConfFile << "    if ($value =~ /^" << alertPtr->alertValue->value << "$/) \\\n";
                break;
            default:
                ToolsEngine::log("error") << "[Class:AlertProcessor] " << " - " << "switch Information unit type check failed";
                break;               
        }

        secConfFile << "      { \\\n"
                "        my $res = '{\\\"alert_ids\\\": ['.$id.']}'; \\\n"
                "        return ($res, $value, length($res)) \\\n"
                "      }; \\\n"
                "    }; \\\n"
                "  }; \\\n"
                "}\n"
                "desc=POST /alerts/" << alertPtr.id() << "/trackings?eno_token=" << engOrgPtr->token<< " HTTP/1.1\\n"
                       "Host: " << te->apiHost << "\\n"
                       "Content-Type: application/json; charset=utf-8\\n"
                       "Content-length: $3\\n\\n"
                       "$1\\n\\n\n"
                    "action=shellcmd /usr/bin/printf \"%s\" | /usr/bin/openssl s_client -quiet -connect " << te->apiHost << ":" << te->apiPort;
        
        secConfFile.close();
    }
    else
    {
        ToolsEngine::log("error") << "[Class:AlertProcessor] - Unable to open/create file: " << _alertsMap[alertPtr.id()].secConfFilename;
    }

    _alertsMap[alertPtr.id()].secPID = popen_sec(_alertsMap[alertPtr.id()].secConfFilename, &_alertsMap[alertPtr.id()].secInFP, &_alertsMap[alertPtr.id()].secOutFP);
    if (_alertsMap[alertPtr.id()].secPID <= 0)
        ToolsEngine::log("error") << "[Class:AlertProcessor] - Unable to exec SEC: " << _alertsMap[alertPtr.id()].secConfFilename;
}

void AlertProcessor::stopAlert(const long long idAlert)
{
    close(_alertsMap[idAlert].secInFP);
    kill(_alertsMap[idAlert].secPID, SIGTERM);
    waitpid(_alertsMap[idAlert].secPID, NULL, 0);
    _alertsMap[idAlert].secPID = -1;
    
    if(remove(_alertsMap[idAlert].secConfFilename.c_str()) < 0)
        ToolsEngine::log("info") << "[Class:AlertProcessor]" << _alertsMap[idAlert].secConfFilename << ": " << strerror(errno);
}

void AlertProcessor::informationValueLoop(const long long idAlert)
{
    if (idAlert == 0)
    {
        ToolsEngine::log("info") << "[Class:AlertProcessor] - No alert";
        return;
    }

    unsigned idx = 0;
    // Waiting for SEC instance creation
    while(_alertsMap[idAlert].secPID <= 0)
    {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        idx++;
        if (idx % 10 == 0)
            ToolsEngine::log("info") << "[Class:AlertProcessor] - No SEC instance after " << boost::lexical_cast<string>(idx) << "s for idAlert " << idAlert;
        if(idx == 30)
        {
            ToolsEngine::log("info") << "[Class:AlertProcessor] - Stop IVA Collect for idAlert " << idAlert;
            return;
        }
    }
    ToolsEngine::log("info") << "[Class:AlertProcessor] - SEC instance after " << boost::lexical_cast<string>(idx) << "s for idAlert " << idAlert;

    Session sessionThread(te->sqlCredentials);
    
    try 
    {
        ToolsEngine::log("debug") << "[Class:AlertProcessor] - Retrieve Alert in InformationValueLoop";
        Wt::Dbo::Transaction transaction(sessionThread);

        Wt::Dbo::ptr<Alert> alertPtr = sessionThread.find<Alert>()
                .where("\"ALE_ID\" = ?").bind(boost::lexical_cast<string>(idAlert))
                .where("\"ALE_DELETE\" IS NULL")
                .limit(1);

        if(alertPtr)
        {
            const string sPluginID = boost::lexical_cast<string>(alertPtr->alertValue->information->pk.search->pk.source->pk.plugin.id()),
                    sSourceID = boost::lexical_cast<string>(alertPtr->alertValue->information->pk.search->pk.source->pk.id),
                    sSearchID = boost::lexical_cast<string>(alertPtr->alertValue->information->pk.search->pk.id),
                    sINFValueNum = boost::lexical_cast<string>(alertPtr->alertValue->information->pk.subSearchNumber),
                    sInfoUnitID = boost::lexical_cast<string>(alertPtr->alertValue->information->pk.unit.id()),
                    sAssetID = boost::lexical_cast<string>(alertPtr->alertValue->asset.id());

            // Arbitrary definition
            const unsigned period = 60;

            Wt::WDateTime searchDateTime = Wt::WDateTime::currentDateTime().addSecs(-period);

            Wt::Dbo::ptr<InformationValue> ivaPtr;

            if(alertPtr->alertValue->information->pk.search->pos_key_value)
            {
                Wt::Dbo::ptr<InformationValue> ivaKeyPtr;

                while(!ivaKeyPtr)
                {
                    ToolsEngine::log("debug") << "[Class:AlertProcessor] - Retrieve IVA Key";
                    ivaKeyPtr = sessionThread.find<InformationValue>()
                            .where("\"PLG_ID_PLG_ID\" = ?").bind(sPluginID)
                            .where("\"SRC_ID\" = ?").bind(sSourceID)
                            .where("\"SEA_ID\" = ?").bind(sSearchID)
                            .where("\"INF_VALUE_NUM\" = ?").bind(sINFValueNum)
                            .where("\"INU_ID_INU_ID\" = ?").bind(sInfoUnitID)
                            .where("\"IVA_AST_AST_ID\" = ?").bind(sAssetID)
                            .where("\"IVA_VALUE\" = ?").bind(alertPtr->alertValue->keyValue.get().toUTF8())
                            .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString().toUTF8())
                            .orderBy("\"IVA_ID\" DESC")
                            .limit(1);
                    if (!ivaKeyPtr)
                    {
                        searchDateTime = searchDateTime.addSecs(period);
                        informationValueSleep(period, searchDateTime);
                    }
                    if (_alertsMap[idAlert].secPID <= 0)
                    {
                        return;
                    }
                }

                ToolsEngine::log("debug") << "[Class:AlertProcessor] - Retrieve IVA";
                ivaPtr = sessionThread.find<InformationValue>()
                        .where("\"PLG_ID_PLG_ID\" = ?").bind(sPluginID)
                        .where("\"SRC_ID\" = ?").bind(sSourceID)
                        .where("\"SEA_ID\" = ?").bind(sSearchID)
                        .where("\"INF_VALUE_NUM\" = ?").bind(sINFValueNum)
                        .where("\"INU_ID_INU_ID\" = ?").bind(sInfoUnitID)
                        .where("\"IVA_AST_AST_ID\" = ?").bind(sAssetID)
                        .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString().toUTF8())
                        .where("\"IVA_LOT_NUM\" = ?").bind(boost::lexical_cast<string>(ivaKeyPtr->lotNumber))
                        .where("\"IVA_LINE_NUM\" = ?").bind(boost::lexical_cast<string>(ivaKeyPtr->lineNumber))
                        .orderBy("\"IVA_ID\" DESC")
                        .limit(1);
            }
            else
            {
                while(!ivaPtr)
                {
                    ToolsEngine::log("debug") << "[Class:AlertProcessor] - Retrieve IVA";
                    ivaPtr = sessionThread.find<InformationValue>()
                            .where("\"PLG_ID_PLG_ID\" = ?").bind(sPluginID)
                            .where("\"SRC_ID\" = ?").bind(sSourceID)
                            .where("\"SEA_ID\" = ?").bind(sSearchID)
                            .where("\"INF_VALUE_NUM\" = ?").bind(sINFValueNum)
                            .where("\"INU_ID_INU_ID\" = ?").bind(sInfoUnitID)
                            .where("\"IVA_AST_AST_ID\" = ?").bind(sAssetID)
                            .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString().toUTF8())
                            .orderBy("\"IVA_ID\" DESC")
                            .limit(1);
                    if (!ivaPtr)
                    {
                        searchDateTime = searchDateTime.addSecs(period);
                        informationValueSleep(period, searchDateTime);
                    }
                    if (_alertsMap[idAlert].secPID <= 0)
                    {
                        return;
                    }
                }
            }

            searchDateTime = searchDateTime.addSecs(period);
            informationValueSleep(period, searchDateTime);

            while(_alertsMap[idAlert].secPID > 0)
            {
                const string sIVAID = boost::lexical_cast<string>(ivaPtr.id());
                if (ivaPtr)
                {
                    string inputSEC = sIVAID;

                    switch(alertPtr->alertValue->information->pk.unit->unitType.id())
                    {
                        case Enums::NUMBER:
                            inputSEC += ":" + ivaPtr->value.toUTF8();
                            break;
                        default:
                            inputSEC += ":" + Wt::Utils::base64Encode(ivaPtr->value.toUTF8());
                            break;
                    }
                    inputSEC += "\n";

                    ToolsEngine::log("debug") << "[Class:AlertProcessor] - Send IVA to SEC";
                     write(_alertsMap[alertPtr.id()].secInFP, inputSEC.c_str(), inputSEC.size());
                }

                ToolsEngine::log("debug") << "[Class:AlertProcessor]" << " - Retrieve IVA";

                if(alertPtr->alertValue->information->pk.search->pos_key_value)
                {
                    ivaPtr = sessionThread.find<InformationValue>()
                            .where("\"IVA_ID\" > ?").bind(sIVAID)
                            .where("\"PLG_ID_PLG_ID\" = ?").bind(sPluginID)
                            .where("\"SRC_ID\" = ?").bind(sSourceID)
                            .where("\"SEA_ID\" = ?").bind(sSearchID)
                            .where("\"INF_VALUE_NUM\" = ?").bind(sINFValueNum)
                            .where("\"INU_ID_INU_ID\" = ?").bind(sInfoUnitID)
                            .where("\"IVA_AST_AST_ID\" = ?").bind(sAssetID)
                            .where("\"IVA_LINE_NUM\" = ?").bind(boost::lexical_cast<string>(ivaPtr->lineNumber))
                            .limit(1);
                }
                else
                {
                    ivaPtr = sessionThread.find<InformationValue>()
                            .where("\"IVA_ID\" > ?").bind(sIVAID)
                            .where("\"PLG_ID_PLG_ID\" = ?").bind(sPluginID)
                            .where("\"SRC_ID\" = ?").bind(sSourceID)
                            .where("\"SEA_ID\" = ?").bind(sSearchID)
                            .where("\"INF_VALUE_NUM\" = ?").bind(sINFValueNum)
                            .where("\"INU_ID_INU_ID\" = ?").bind(sInfoUnitID)
                            .where("\"IVA_AST_AST_ID\" = ?").bind(sAssetID)
                            .limit(1);
                }

                searchDateTime = searchDateTime.addSecs(period);
                informationValueSleep(period, searchDateTime);
            }
        }
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << "[Class:AlertProcessor] - " << e.what();
    }
    
    return;
}

void AlertProcessor::informationValueSleep(const unsigned period, Wt::WDateTime &previousDateTime)
{
    boost::this_thread::sleep(boost::posix_time::seconds(period - previousDateTime.secsTo(Wt::WDateTime::currentDateTime())));
    return;
}

