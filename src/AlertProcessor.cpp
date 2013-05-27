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

            ToolsEngine::log("debug") << "[Alert Processor] - We have " << alertPtrCollection.size() << " Alert(s) for this Engine in the database";

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
                        ToolsEngine::log("debug") << "[Alert Processor] - No Token for Alert: " << it->id();
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

                ToolsEngine::log("debug") << "[Alert Processor] - We have " << newAlertPtrCollection.size() << " more Alert(s) for this Engine in the database";

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
                        ToolsEngine::log("debug") << "[Alert Processor] - No Token for Alert: " << it->id();
                }
            }

            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << "[Alert Processor] - " << e.what();
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
        
        boost::this_thread::sleep(boost::posix_time::seconds(te->sleepThreadCheckAlert));
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
        ToolsEngine::log("info") << "[Alert Processor] execl: " << strerror(errno);
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
                ToolsEngine::log("debug") << "[Alert Processor] - We are entering in the switch of the case number";

                secConfFile << "    if ($value =~ /^([+-]?)(?=\\d|\\.\\d)\\d*(\\.\\d*)?([Ee]([+-]?\\d+))?$/) \\\n"
                        "    { \\\n";

                switch(alertPtr->alertValue->alertCriteria.id())
                {
                    case Enums::LT: 
                        ToolsEngine::log("debug") << "[Alert Processor]- we are entering in the switch of the lt comparison";
                        secConfFile << "      if ($value < " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::LE:
                        ToolsEngine::log("debug") << "[Alert Processor] " << " - " << "we are entering in the switch of the le comparison";
                        secConfFile << "      if ($value <= " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::EQ:
                        ToolsEngine::log("debug") << "[Alert Processor] " << " - " << "we are entering in the switch of the eq comparison";
                        secConfFile << "      if ($value == " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::NE:
                        ToolsEngine::log("debug") << "[Alert Processor] " << " - " << "we are entering in the switch of the ne comparison";
                        secConfFile << "      if ($value != " << alertPtr->alertValue->value << ") \\\n";
                        break;                            
                    case Enums::GE:
                        ToolsEngine::log("debug") << "[Alert Processor] " << " - " << "we are entering in the switch of the ge comparison";
                        secConfFile << "      if ($value >= " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    case Enums::GT:
                        ToolsEngine::log("debug") << "[Alert Processor] " << " - " << "we are entering in the switch of the gt comparison";
                        secConfFile << "      if ($value > " << alertPtr->alertValue->value << ") \\\n";
                        break;
                    default:
                        ToolsEngine::log("error") << "[Alert Processor] " << " - " << "switch operator selection failed";
                        break; 
                }
                break;
            case Enums::TEXT:
                secConfFile << "    if ($value =~ /^" << alertPtr->alertValue->value << "$/) \\\n";
                break;
            default:
                ToolsEngine::log("error") << "[Alert Processor] " << " - " << "switch Information unit type check failed";
                break;               
        }

        if (alertPtr->alertValue->information->pk.unit->unitType.id() == Enums::NUMBER)
            secConfFile << "  ";
        
        secConfFile << "    { \\\n"
                "        my $res = '{\\\"alert_ids\\\": ['.$id.']}'; \\\n"
                "        return ($res, $value, length($res)) \\\n";

        if (alertPtr->alertValue->information->pk.unit->unitType.id() == Enums::NUMBER)
            secConfFile << "      }; \\\n";

        secConfFile << "    }; \\\n"
                "  }; \\\n"
                "}\n"
                "desc=POST /alerts/" << alertPtr.id() << "/trackings?eno_token=" << engOrgPtr->token<< " HTTP/1.1\\n"
                       "Host: " << te->apiHost << "\\n"
                       "Content-Type: application/json; charset=utf-8\\n"
                       "Content-length: $3\\n\\n"
                       "$1\\n\\n\n"
                "action=shellcmd /usr/bin/printf \"%s\" | /usr/bin/openssl s_client -quiet -connect " << te->apiHost << ":" << te->apiPort << "\n";
        
        secConfFile.close();
    }
    else
    {
        ToolsEngine::log("error") << "[Alert Processor] - Unable to open/create file: " << _alertsMap[alertPtr.id()].secConfFilename;
    }

    _alertsMap[alertPtr.id()].secPID = popen_sec(_alertsMap[alertPtr.id()].secConfFilename, &_alertsMap[alertPtr.id()].secInFP, &_alertsMap[alertPtr.id()].secOutFP);
    if (_alertsMap[alertPtr.id()].secPID <= 0)
        ToolsEngine::log("error") << "[Alert Processor] - Unable to exec SEC: " << _alertsMap[alertPtr.id()].secConfFilename;
}

void AlertProcessor::stopAlert(const long long alertID)
{
    close(_alertsMap[alertID].secInFP);
    kill(_alertsMap[alertID].secPID, SIGTERM);
    waitpid(_alertsMap[alertID].secPID, NULL, 0);
    _alertsMap[alertID].secPID = -1;
    
    if(remove(_alertsMap[alertID].secConfFilename.c_str()) < 0)
        ToolsEngine::log("info") << "[Alert Processor]" << _alertsMap[alertID].secConfFilename << ": " << strerror(errno);
}

void AlertProcessor::informationValueLoop(const long long alertID)
{
    if (alertID < 1)
    {
        ToolsEngine::log("error") << "[Alert Processor] - " << alertID << ": alert ID invalid";
        return;
    }

    unsigned idx = 0;
    // Waiting for SEC instance creation
    while(_alertsMap[alertID].secPID <= 0)
    {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        idx++;
        if (idx % 10 == 0)
            ToolsEngine::log("warning") << "[Alert Processor] - No SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;
        if(idx == 30)
        {
            ToolsEngine::log("error") << "[Alert Processor] - Stop IVA Collect for alert ID: " << alertID;
            return;
        }
    }
    ToolsEngine::log("info") << "[Alert Processor] - SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;

    Session sessionThread(te->sqlCredentials);
    long long pluginID = 0, sourceID = 0, searchID = 0, infoUnitID = 0, infoUnitTypeID = 0, assetID = 0;
    int infValueNum = 0, posKeyValue = 0;
    string keyValue = "";

    try 
    {
        ToolsEngine::log("debug") << "[Alert Processor] - Retrieve Alert in InformationValueLoop";
        Wt::Dbo::Transaction transaction(sessionThread);

        Wt::Dbo::ptr<Alert> alertPtr = sessionThread.find<Alert>()
                .where("\"ALE_ID\" = ?").bind(boost::lexical_cast<string>(alertID))
                .where("\"ALE_DELETE\" IS NULL")
                .limit(1);

        if(alertPtr)
        {
            pluginID = alertPtr->alertValue->information->pk.search->pk.source->pk.plugin.id();
            sourceID = alertPtr->alertValue->information->pk.search->pk.source->pk.id;
            searchID = alertPtr->alertValue->information->pk.search->pk.id;
            infoUnitID = alertPtr->alertValue->information->pk.unit.id();
            infoUnitTypeID = alertPtr->alertValue->information->pk.unit->unitType.id();
            assetID = alertPtr->alertValue->asset.id();

            infValueNum = alertPtr->alertValue->information->pk.subSearchNumber;
            posKeyValue = alertPtr->alertValue->information->pk.search->pos_key_value;
            
            keyValue = alertPtr->alertValue->keyValue.get().toUTF8();
        }
        else
        {
            ToolsEngine::log("warning") << "[Alert Processor] - " << alertID << ": no alert in database for this ID";
            transaction.commit();
            return;
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << "[Alert Processor] - " << e.what();
        return;
    }

    // Arbitrary definition
    const unsigned period = 60;

    Wt::WDateTime searchDateTime = Wt::WDateTime::currentDateTime().addSecs(-period);

    long long ivaID = 0;
    string ivaValue = "";
    int lineNumber = 0;

    if(posKeyValue)
    {
        long long ivaKeyID = 0;
        int lotNumber = 0;

        while(ivaKeyID < 1)
        {
            ToolsEngine::log("debug") << "[Alert Processor] - Retrieve IVA Key";
            try 
            {
                Wt::Dbo::Transaction transaction(sessionThread);

                Wt::Dbo::ptr<InformationValue> ivaKeyPtr = sessionThread.find<InformationValue>()
                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginID)
                        .where("\"SRC_ID\" = ?").bind(sourceID)
                        .where("\"SEA_ID\" = ?").bind(searchID)
                        .where("\"INF_VALUE_NUM\" = ?").bind(infValueNum)
                        .where("\"INU_ID_INU_ID\" = ?").bind(infoUnitID)
                        .where("\"IVA_AST_AST_ID\" = ?").bind(assetID)
                        .where("\"IVA_VALUE\" = ?").bind(keyValue)
                        .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString().toUTF8())
                        .orderBy("\"IVA_ID\" DESC")
                        .limit(1);

                ivaKeyID = ivaKeyPtr.id();
                if (ivaKeyPtr)
                {
                    lotNumber = ivaKeyPtr->lotNumber;
                    lineNumber = ivaKeyPtr->lineNumber;
                }

                transaction.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                ToolsEngine::log("error") << "[Alert Processor] - " << e.what();
            }
            if (ivaKeyID < 1)
            {
                searchDateTime = searchDateTime.addSecs(period);
                informationValueSleep(period, searchDateTime);
            }
            if (_alertsMap[alertID].secPID <= 0)
            {
                return;
            }
        }

        ToolsEngine::log("debug") << "[Alert Processor] - Retrieve IVA";
        try 
        {
            Wt::Dbo::Transaction transaction(sessionThread);
            Wt::Dbo::ptr<InformationValue> ivaPtr = sessionThread.find<InformationValue>()
                    .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginID)
                    .where("\"SRC_ID\" = ?").bind(sourceID)
                    .where("\"SEA_ID\" = ?").bind(searchID)
                    .where("\"INF_VALUE_NUM\" = ?").bind(infValueNum)
                    .where("\"INU_ID_INU_ID\" = ?").bind(infoUnitID)
                    .where("\"IVA_AST_AST_ID\" = ?").bind(assetID)
                    .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString().toUTF8())
                    .where("\"IVA_LOT_NUM\" = ?").bind(lotNumber)
                    .where("\"IVA_LINE_NUM\" = ?").bind(lineNumber)
                    .orderBy("\"IVA_ID\" DESC")
                    .limit(1);

            ivaID = ivaPtr.id();
            if (ivaPtr)
                ivaValue = ivaPtr->value.toUTF8();
            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << "[Alert Processor] - " << e.what();
        }
    }
    else
    {
        while(ivaID < 1)
        {
            ToolsEngine::log("debug") << "[Alert Processor] - Retrieve IVA";
            try
            {
                Wt::Dbo::Transaction transaction(sessionThread);

                Wt::Dbo::ptr<InformationValue> ivaPtr = sessionThread.find<InformationValue>()
                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginID)
                        .where("\"SRC_ID\" = ?").bind(sourceID)
                        .where("\"SEA_ID\" = ?").bind(searchID)
                        .where("\"INF_VALUE_NUM\" = ?").bind(infValueNum)
                        .where("\"INU_ID_INU_ID\" = ?").bind(infoUnitID)
                        .where("\"IVA_AST_AST_ID\" = ?").bind(assetID)
                        .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString().toUTF8())
                        .orderBy("\"IVA_ID\" DESC")
                        .limit(1);
                ivaID = ivaPtr.id();
                if (ivaPtr)
                    ivaValue = ivaPtr->value.toUTF8();

                transaction.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                ToolsEngine::log("error") << "[Alert Processor] - " << e.what();
            }
            if  (ivaID < 1)
            {
                searchDateTime = searchDateTime.addSecs(period);
                informationValueSleep(period, searchDateTime);
            }
            if (_alertsMap[alertID].secPID <= 0)
            {
                return;
            }
        }
    }

    searchDateTime = searchDateTime.addSecs(period);
    informationValueSleep(period, searchDateTime);

    while(_alertsMap[alertID].secPID > 0)
    {
        if (ivaID > 0)
        {
            string inputSEC = boost::lexical_cast<string>(ivaID);

            switch(infoUnitTypeID)
            {
                case Enums::NUMBER:
                    inputSEC += ":" + ivaValue;
                    break;
                default:
                    inputSEC += ":" + Wt::Utils::base64Encode(ivaValue);
                    break;
            }
            inputSEC += "\n";

            ToolsEngine::log("debug") << "[Alert Processor] - Send IVA to SEC";
             write(_alertsMap[alertID].secInFP, inputSEC.c_str(), inputSEC.size());
        }

        ToolsEngine::log("debug") << "[Alert Processor]" << " - Retrieve IVA";

        try
        {
            Wt::Dbo::Transaction transaction(sessionThread);

            Wt::Dbo::ptr<InformationValue> ivaPtr;
            if(posKeyValue)
            {
                ivaPtr = sessionThread.find<InformationValue>()
                        .where("\"IVA_ID\" > ?").bind(ivaID)
                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginID)
                        .where("\"SRC_ID\" = ?").bind(sourceID)
                        .where("\"SEA_ID\" = ?").bind(searchID)
                        .where("\"INF_VALUE_NUM\" = ?").bind(infValueNum)
                        .where("\"INU_ID_INU_ID\" = ?").bind(infoUnitID)
                        .where("\"IVA_AST_AST_ID\" = ?").bind(assetID)
                        .where("\"IVA_LINE_NUM\" = ?").bind(lineNumber)
                        .limit(1);
            }
            else
            {
                ivaPtr = sessionThread.find<InformationValue>()
                        .where("\"IVA_ID\" > ?").bind(ivaID)
                        .where("\"PLG_ID_PLG_ID\" = ?").bind(pluginID)
                        .where("\"SRC_ID\" = ?").bind(sourceID)
                        .where("\"SEA_ID\" = ?").bind(searchID)
                        .where("\"INF_VALUE_NUM\" = ?").bind(infValueNum)
                        .where("\"INU_ID_INU_ID\" = ?").bind(infoUnitID)
                        .where("\"IVA_AST_AST_ID\" = ?").bind(assetID)
                        .limit(1);
            }

            ivaID = ivaPtr.id();

            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            ToolsEngine::log("error") << "[Alert Processor] - " << e.what();
        }

        searchDateTime = searchDateTime.addSecs(period);
        informationValueSleep(period, searchDateTime);
    }

    return;
}

void AlertProcessor::informationValueSleep(const unsigned period, Wt::WDateTime &previousDateTime)
{
    boost::this_thread::sleep(boost::posix_time::seconds(period - previousDateTime.secsTo(Wt::WDateTime::currentDateTime())));
    return;
}

