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
#include "Conf.h"

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
    Echoes::Dbo::Session session(conf.getSessConnectParams());

    while (true)
    {
        try
        {
            Wt::Dbo::Transaction transaction(session);

            Wt::Dbo::ptr<Echoes::Dbo::Engine> enginePtr = session.find<Echoes::Dbo::Engine>().where("\"ENG_ID\" = ?").bind(conf.getId()).limit(1);

            Wt::Dbo::collection < Wt::Dbo::ptr < Echoes::Dbo::Alert >> alertPtrCollection = session.find<Echoes::Dbo::Alert>()
                    .where("\"ALE_ENG_ENG_ID\" = ?").bind(enginePtr.id())
                    .where("\"ALE_DELETE\" IS NULL");

            logger.entry("debug") << "[Alert Processor] We have " << alertPtrCollection.size() << " Alert(s) for this Engine in the database";

            for (Wt::Dbo::collection < Wt::Dbo::ptr < Echoes::Dbo::Alert >> ::const_iterator it = alertPtrCollection.begin(); it != alertPtrCollection.end(); ++it)
            {
                if (_alertsMap.find(it->id()) == _alertsMap.end())
                {
                    Wt::Dbo::ptr<Echoes::Dbo::EngOrg> engOrgPtr = session.find<Echoes::Dbo::EngOrg>()
                            .where("\"ENG_ID_ENG_ID\" = ?").bind(enginePtr.id())
                            .where("\"ORG_ID_ORG_ID\" = ?").bind(it->get()->alertValue->informationData->asset->organization.id())
                            .where("\"ENO_DELETE\" IS NULL")
                            .limit(1);

                    if (engOrgPtr)
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
                            0,
                            new boost::thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id()))
                        };
                        startAlert(*it, engOrgPtr);
                    }
                    else
                        logger.entry("debug") << "[Alert Processor] No Token for Alert: " << it->id();
                }
                else
                    _alertsMap[it->id()].check = true;
            }

            if (alertPtrCollection.size() < (unsigned) enginePtr->nbThread)
            {
                Wt::Dbo::collection < Wt::Dbo::ptr < Echoes::Dbo::Alert >> newAlertPtrCollection = session.find<Echoes::Dbo::Alert>()
                        .where("\"ALE_ENG_ENG_ID\" is NULL")
                        .where("\"ALE_DELETE\" IS NULL")
                        .limit(enginePtr->nbThread - alertPtrCollection.size());

                logger.entry("debug") << "[Alert Processor] We have " << newAlertPtrCollection.size() << " more Alert(s) for this Engine in the database";

                for (Wt::Dbo::collection < Wt::Dbo::ptr < Echoes::Dbo::Alert >> ::const_iterator it = newAlertPtrCollection.begin(); it != newAlertPtrCollection.end(); ++it)
                {
                    Wt::Dbo::ptr<Echoes::Dbo::EngOrg> engOrgPtr = session.find<Echoes::Dbo::EngOrg>()
                            .where("\"ENG_ID_ENG_ID\" = ?").bind(enginePtr.id())
                            .where("\"ORG_ID_ORG_ID\" = ?").bind(it->get()->alertValue->informationData->asset->organization.id())
                            .where("\"ENO_DELETE\" IS NULL")
                            .limit(1);

                    if (engOrgPtr)
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
                            0,
                            new boost::thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id()))
                        };
                        startAlert(*it, engOrgPtr);
                    }
                    else
                        logger.entry("debug") << "[Alert Processor] No Token for Alert: " << it->id();
                }
            }

            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[Alert Processor] " << e.what();
        }

        vector<long long> alertToErase;
        for (map<long long, SecondStructure>::const_iterator it = _alertsMap.begin(); it != _alertsMap.end(); ++it)
        {
            if (it->second.check)
            {
                _alertsMap[it->first].check = false;
            }
            else
            {
                stopAlert(it->first);
                it->second.ivaThread->interrupt();
                delete it->second.ivaThread;
                alertToErase.push_back(it->first);
            }
        }

        for (unsigned i(0); i < alertToErase.size(); ++i)
        {
            _alertsMap.erase(alertToErase[i]);
        }

        boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCheckAlert));
    }

    return res;
}

pid_t AlertProcessor::popen_sec(const string &confFilename, int *infp, int *outfp, int *errfp)
{
    int p_stdin[2] = {0}, p_stdout[2] = {0}, p_stderr[2] = {0};
    pid_t pid = 0;

    if (pipe(p_stdin) != 0 || pipe(p_stdout) != 0 || pipe(p_stderr) != 0)
        return -1;

    pid = fork();

    if (pid == 0) // Child process
    {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], 0); // Standard input
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], 1); // Standard output
        close(p_stderr[READ]);
        dup2(p_stderr[WRITE], 2); // Standard error
        execl(
              "/usr/bin/sec",
              "sec",
              ("-conf=" + confFilename).c_str(),
              "-input=-",
#ifdef NDEBUG
                ("-log=" + logger.getPath()).c_str(),
#endif
                //              Not supported before SEC 2.7.4
              //              "--childterm",
              NULL
              );
        logger.entry("info") << "[Alert Processor] execl: " << strerror(errno);
        _exit(EXIT_FAILURE);
    }
    else if (pid > 0) // Parent
    {
        if (infp == NULL)
            close(p_stdin[WRITE]);
        else
            *infp = p_stdin[WRITE];

        if (outfp == NULL)
            close(p_stdout[READ]);
        else
            *outfp = p_stdout[READ];

        if (errfp == NULL)
            close(p_stderr[READ]);
        else
            *errfp = p_stderr[READ];
    }
    else
        logger.entry("error") << "[Alert Processor] fork: " << strerror(errno);

    return pid;
}

void AlertProcessor::startAlert(Wt::Dbo::ptr<Echoes::Dbo::Alert> alertPtr, Wt::Dbo::ptr<Echoes::Dbo::EngOrg> engOrgPtr)
{
    ofstream secConfFile(_alertsMap[alertPtr.id()].secConfFilename.c_str());
    if (secConfFile)
    {
        secConfFile << "type=Single\n"
                "ptype=PerlFunc\n"
                "pattern= \\\n"
                "sub { \\\n"
                "  use strict; \\\n"
                "  if ($_[0] cmp '') \\\n"
                "  { \\\n"
                "    (my $id, my $value) = split(':', $_[0]); \\\n";

        if (alertPtr->alertValue->informationData->informationUnit->unitType.id() != Echoes::Dbo::EInformationUnitType::NUMBER)
        {
            secConfFile << "    use MIME::Base64; \\\n"
                    "    $value = decode_base64($value); \\\n";
        }

        switch (alertPtr->alertValue->informationData->informationUnit->unitType.id())
        {
        case Echoes::Dbo::EInformationUnitType::NUMBER:
            logger.entry("debug") << "[Alert Processor] We are entering in the switch of the case number";

            secConfFile << "    if ($value =~ /^([+-]?)(?=\\d|\\.\\d)\\d*(\\.\\d*)?([Ee]([+-]?\\d+))?$/) \\\n"
                    "    { \\\n"
                    "      if ($value ";

            switch (alertPtr->alertValue->alertCriteria.id())
            {
            case Echoes::Dbo::EAlertCriteria::LT:
                logger.entry("debug") << "[Alert Processor] We are entering in the switch of the lt comparison";
                secConfFile << "<";
                break;
            case Echoes::Dbo::EAlertCriteria::LE:
                logger.entry("debug") << "[Alert Processor] We are entering in the switch of the le comparison";
                secConfFile << "<=";
                break;
            case Echoes::Dbo::EAlertCriteria::EQ:
                logger.entry("debug") << "[Alert Processor] We are entering in the switch of the eq comparison";
                secConfFile << "==";
                break;
            case Echoes::Dbo::EAlertCriteria::NE:
                logger.entry("debug") << "[Alert Processor] We are entering in the switch of the ne comparison";
                secConfFile << "!=";
                break;
            case Echoes::Dbo::EAlertCriteria::GE:
                logger.entry("debug") << "[Alert Processor] We are entering in the switch of the ge comparison";
                secConfFile << ">=";
                break;
            case Echoes::Dbo::EAlertCriteria::GT:
                logger.entry("debug") << "[Alert Processor] We are entering in the switch of the gt comparison";
                secConfFile << ">";
                break;
            default:
                logger.entry("error") << "[Alert Processor] Switch operator selection failed";
                break;
            }
            secConfFile << " " << alertPtr->alertValue->value << ") \\\n";
            break;
        case Echoes::Dbo::EInformationUnitType::TEXT:
            secConfFile << "    if ($value =~ /^" << alertPtr->alertValue->value << "$/) \\\n";
            break;
        default:
            logger.entry("error") << "[Alert Processor] Switch Information unit type check failed";
            break;
        }

        if (alertPtr->alertValue->informationData->informationUnit->unitType.id() == Echoes::Dbo::EInformationUnitType::NUMBER)
            secConfFile << "  ";

        secConfFile << "    { \\\n"
                "        my $res = '{\\\\\\\\\\\\\"alert_ids\\\\\\\\\\\\\": ['.$id.']}'; \\\n"
                "        return ($res, $value, (length($res) - 6)) \\\n";

        if (alertPtr->alertValue->informationData->informationUnit->unitType.id() == Echoes::Dbo::EInformationUnitType::NUMBER)
            secConfFile << "      }; \\\n";

        secConfFile << "    }; \\\n"
                "  }; \\\n"
                "}\n"
                "desc=POST /alerts/" << alertPtr.id() << "/trackings?eno_token=" << engOrgPtr->token << " HTTP/1.1\\n"
                "Host: " << conf.getAPIHost() << "\\n"
                "Content-Type: application/json; charset=utf-8\\n"
                "Content-length: $3\\n"
                "Connection: close\\n\\n"
                "$1\\n\\n\n"
                "action=shellcmd (/usr/bin/perl -e \"alarm(2); exec(\\\"/usr/bin/printf \\'%s\\' | /usr/bin/openssl s_client -quiet -connect " << conf.getAPIHost() << ":" << conf.getAPIPort() << "\\\")\")\n";

        secConfFile.close();
    }
    else
    {
        logger.entry("error") << "[Alert Processor] Unable to open/create file: " << _alertsMap[alertPtr.id()].secConfFilename;
    }

    _alertsMap[alertPtr.id()].secPID = popen_sec(_alertsMap[alertPtr.id()].secConfFilename, &_alertsMap[alertPtr.id()].secInFP, &_alertsMap[alertPtr.id()].secOutFP, &_alertsMap[alertPtr.id()].secErrFP);
    if (_alertsMap[alertPtr.id()].secPID <= 0)
        logger.entry("error") << "[Alert Processor] Unable to exec SEC: " << _alertsMap[alertPtr.id()].secConfFilename;
}

void AlertProcessor::stopAlert(const long long alertID)
{
    kill(_alertsMap[alertID].secPID, SIGTERM);
    close(_alertsMap[alertID].secInFP);
    close(_alertsMap[alertID].secOutFP);
    close(_alertsMap[alertID].secErrFP);
    waitpid(_alertsMap[alertID].secPID, NULL, 0);
    _alertsMap[alertID].secPID = -1;

    if (remove(_alertsMap[alertID].secConfFilename.c_str()) < 0)
        logger.entry("info") << "[Alert Processor] " << _alertsMap[alertID].secConfFilename << ": " << strerror(errno);
}

void AlertProcessor::informationValueLoop(const long long alertID)
{
    if (alertID < 1)
    {
        logger.entry("error") << "[Alert Processor] " << alertID << ": alert ID invalid";
        return;
    }

    unsigned idx = 0;
    // Waiting for SEC instance creation
    while (_alertsMap[alertID].secPID <= 0)
    {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        idx++;
        if (idx % 10 == 0)
            logger.entry("warning") << "[Alert Processor] No SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;
        if (idx == 30)
        {
            logger.entry("error") << "[Alert Processor] Stop IVA Collect for alert ID: " << alertID;
            return;
        }
    }
    logger.entry("info") << "[Alert Processor] SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;

    boost::thread(boost::bind(&AlertProcessor::secLogLoop, this, _alertsMap[alertID].secOutFP, "info"));
    boost::thread(boost::bind(&AlertProcessor::secLogLoop, this, _alertsMap[alertID].secErrFP, "error"));

    Echoes::Dbo::Session sessionThread(conf.getSessConnectParams());

    long long idaId = 0;
    long long filId = 0;
    long long astId = 0;
    long long infId = 0;
    long long iutId = 0;
//    int fieldFilterIndex = 0;
    int posKeyValue = 0;
    string keyValue = "";
    Wt::Dbo::ptr<Echoes::Dbo::InformationData> idakeyPtr;

    // We get the data to be able to find all the IVAs needed
    try
    {
        logger.entry("debug") << "[Alert Processor] Retrieve Alert in InformationValueLoop";
        Wt::Dbo::Transaction transaction(sessionThread);

        // Getting the dbo ptr on the alert currently processed
        Wt::Dbo::ptr<Echoes::Dbo::Alert> alertPtr = sessionThread.find<Echoes::Dbo::Alert>()
                .where("\"ALE_ID\" = ?").bind(boost::lexical_cast<string>(alertID))
                .where("\"ALE_DELETE\" IS NULL")
                .limit(1);

        if (alertPtr)
        {
            idaId = alertPtr->alertValue->informationData.id();
            infId = alertPtr->alertValue->informationData->information.id();
            filId = alertPtr->alertValue->informationData->filter.id();
            astId = alertPtr->alertValue->informationData->asset.id();
            iutId = alertPtr->alertValue->informationData->informationUnit->unitType.id();
            posKeyValue = alertPtr->alertValue->informationData->filter->posKeyValue;
//            fieldFilterIndex = alertPtr->alertValue->informationData->filterFieldIndex;

            if (posKeyValue > 0)
            {
                //looking for the ida about the key
                keyValue = alertPtr->alertValue->keyValue.get().toUTF8();
                idakeyPtr = sessionThread
                        .find<Echoes::Dbo::InformationData>()
                        .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP TRIGRAM_FILTER SEP TRIGRAM_FILTER ID) " = ?")
                        .bind(filId)
                        .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP TRIGRAM_ASSET SEP TRIGRAM_ASSET ID) " = ?")
                        .bind(astId)
                        .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP TRIGRAM_INFORMATION SEP TRIGRAM_INFORMATION ID) " = ?")
                        .bind(infId)
                        .where(QUOTE(TRIGRAM_INFORMATION_DATA "FILTER_FIELD_INDEX = ?"))
                        .bind(posKeyValue)
                        .limit(1);
                
                if (idakeyPtr)
                {
                    logger.entry("debug") << "ptr found, ok";
                }
                else
                {
                    logger.entry("warning") << "[Alert Processor] no Ida in database for this poskey";
                    transaction.commit();
                    return;
                }
                
            }
        }
        else
        {
            logger.entry("warning") << "[Alert Processor] " << alertID << ": no alert in database for this ID";
            transaction.commit();
            return;
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[Alert Processor] " << e.what();
        return;
    }

    // Arbitrary definition
    const unsigned period = 60;

    Wt::WDateTime searchDateTime = Wt::WDateTime::currentDateTime().addSecs(-period);

    long long ivaID = 0, ivaKeyID = 0;
    string ivaValue = "";

    // first case, we have a pos key value and we need to get the lotNumber and the lineNumber
    if (posKeyValue > 0)
    {
        int lotNumber = 0, lineNumber = 0;
        while (ivaKeyID < 1 && _alertsMap[alertID].secPID > 0)
        {
            logger.entry("debug") << "[Alert Processor] Retrieve IVA Key after: " << searchDateTime.toString("yyyy-MM-dd hh:mm:ss");
            try
            {
                Wt::Dbo::Transaction transaction(sessionThread);

                Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaKeyPtr = sessionThread.find<Echoes::Dbo::InformationValue>()
                        .where("\"IVA_IDA_IDA_ID\" = ?").bind(idakeyPtr.id())
                        .where("\"IVA_STATE\" = ?").bind(0)
                        .where("\"IVA_VALUE\" = ?").bind(keyValue)
                        .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString("yyyy-MM-dd hh:mm:ss").toUTF8())
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
                logger.entry("error") << "[Alert Processor] " << e.what();
            }
            if (ivaKeyID < 1)
            {
                searchDateTime = searchDateTime.addSecs(period);
                informationValueSleep(period, searchDateTime);
            }
        }

        if (_alertsMap[alertID].secPID > 0)
        {
            logger.entry("debug") << "[Alert Processor] Retrieve IVA after: " << searchDateTime.toString("yyyy-MM-dd hh:mm:ss");
            try
            {
                Wt::Dbo::Transaction transaction(sessionThread);
                Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr = sessionThread.find<Echoes::Dbo::InformationValue>()
                        .where("\"IVA_IDA_IDA_ID\" = ?").bind(idaId)
                        .where("\"IVA_STATE\" = ?").bind(0)
                        .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString("yyyy-MM-dd hh:mm:ss").toUTF8())
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
                logger.entry("error") << "[Alert Processor] " << e.what();
            }
        }
        else
        {
            return;
        }

    }
    // second case, simple information without poskey
    else
    {
        while (ivaID < 1 && _alertsMap[alertID].secPID > 0)
        {
            logger.entry("debug") << "[Alert Processor] Retrieve IVA after: " << searchDateTime.toString("yyyy-MM-dd hh:mm:ss");
            try
            {
                Wt::Dbo::Transaction transaction(sessionThread);

                Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr = sessionThread.find<Echoes::Dbo::InformationValue>()
                        .where("\"IVA_IDA_IDA_ID\" = ?").bind(idaId)
                         .where("\"IVA_STATE\" = ?").bind(0)
                        .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString("yyyy-MM-dd hh:mm:ss").toUTF8())
                        .orderBy("\"IVA_ID\" DESC")
                        .limit(1);
                ivaID = ivaPtr.id();
                if (ivaPtr)
                    ivaValue = ivaPtr->value.toUTF8();

                transaction.commit();
            }
            catch (Wt::Dbo::Exception e)
            {
                logger.entry("error") << "[Alert Processor] " << e.what();
            }
            if (ivaID < 1)
            {
                searchDateTime = searchDateTime.addSecs(period);
                informationValueSleep(period, searchDateTime);
            }
        }
    }

    while (_alertsMap[alertID].secPID > 0)
    {
        // creating the input for SEC
        if (ivaID > 0)
        {
            string inputSEC = boost::lexical_cast<string>(ivaID);

            switch (iutId)
            {
            case Echoes::Dbo::EInformationUnitType::NUMBER:
                inputSEC += ":" + ivaValue;
                break;
            default:
                inputSEC += ":" + Wt::Utils::base64Encode(ivaValue);
                break;
            }
            inputSEC += "\n";

            logger.entry("debug") << "[Alert Processor] Send IVA to SEC";
            write(_alertsMap[alertID].secInFP, inputSEC.c_str(), inputSEC.size());
        }

        searchDateTime = searchDateTime.addSecs(period);
        informationValueSleep(period, searchDateTime);

        try
        {
            Wt::Dbo::Transaction transaction(sessionThread);

            Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr;
            if (posKeyValue > 0)
            {
                logger.entry("debug") << "[Alert Processor] Retrieve IVA Key";
                
                Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaKeyPtr = sessionThread.find<Echoes::Dbo::InformationValue>()
                        .where("\"IVA_ID\" > ?").bind(ivaKeyID)
                        .where("\"IVA_IDA_IDA_ID\" = ?").bind(idakeyPtr.id())
                        .where("\"IVA_STATE\" = ?").bind(0)
                        .where("\"IVA_VALUE\" = ?").bind(keyValue)
                        .orderBy("\"IVA_ID\" DESC")
                        .limit(1);

                ivaKeyID = ivaKeyPtr.id();
                if (ivaKeyPtr)
                {
                    logger.entry("debug") << "[Alert Processor] Retrieve IVA";
                    Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr = sessionThread.find<Echoes::Dbo::InformationValue>()
                        .where("\"IVA_IDA_IDA_ID\" = ?").bind(idaId)
                        .where("\"IVA_STATE\" = ?").bind(0)
                        .where("\"IVA_LOT_NUM\" = ?").bind(ivaKeyPtr->lotNumber)
                        .where("\"IVA_LINE_NUM\" = ?").bind(ivaKeyPtr->lineNumber)
                        .orderBy("\"IVA_ID\" DESC")
                        .limit(1);
                 }
            }
            else
            {
                logger.entry("debug") << "[Alert Processor] Retrieve IVA";
                ivaPtr = sessionThread.find<Echoes::Dbo::InformationValue>()
                        .where("\"IVA_ID\" > ?").bind(ivaID)
                        .where("\"IVA_IDA_IDA_ID\" = ?").bind(idaId)
                         .where("\"IVA_STATE\" = ?").bind(0)
                        .orderBy("\"IVA_ID\" DESC")
                        .limit(1);
            }

            ivaID = ivaPtr.id();
            if (ivaPtr)
                ivaValue = ivaPtr->value.toUTF8();

            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[Alert Processor] " << e.what();
        }
    }

    return;
}

void AlertProcessor::informationValueSleep(const unsigned period, Wt::WDateTime &previousDateTime)
{
    boost::this_thread::sleep(boost::posix_time::seconds(period - previousDateTime.secsTo(Wt::WDateTime::currentDateTime())));
    return;
}

void AlertProcessor::secLogLoop(const int fd, const string &logLevel)
{
    string line = "";

    __gnu_cxx::stdio_filebuf<char> fileBuf(fd, std::ios::in);
    istream is(&fileBuf);

    while (getline(is, line))
        logger.entry(logLevel) << "[Alert Processor] SEC: " << line;

    return;
}

