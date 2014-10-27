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

AlertProcessor::AlertProcessor(Echoes::Dbo::Session &session) : m_session(session)
{
    try
    {
        Wt::Dbo::Transaction transaction(m_session, true);

        m_enginePtr = m_session.find<Echoes::Dbo::Engine>()
                .where(QUOTE(TRIGRAM_ENGINE ID)" = ?").bind(conf.getId())
                .limit(1);

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e)
    {
        log("error") << "Wt::Dbo: " << e.what();
    }
}

AlertProcessor::~AlertProcessor()
{
    stopAllAlerts();
}

int AlertProcessor::verifyAlerts(int *signum)
{
    int res = -1;

    if (m_enginePtr)
    {
        while (*signum == 0)
        {
            try
            {
                cout << "[ transaction about to begin ]" << endl;
                Wt::Dbo::Transaction transaction(m_session, true);

                Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Alert>> alePtrCol = m_session.find<Echoes::Dbo::Alert>()
                        .where(QUOTE(TRIGRAM_ALERT SEP TRIGRAM_ENGINE SEP TRIGRAM_ENGINE ID)" = ?").bind(m_enginePtr.id())
                        .where(QUOTE(TRIGRAM_ALERT SEP "DELETE") " IS NULL");

                log("debug") << "We have " << alePtrCol.size() << " Alert(s) for this Engine in the database";
                
                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Alert>>::const_iterator it = alePtrCol.begin(); it != alePtrCol.end(); ++it)
                {
                    if (it->get()->alertSequence.id() > 0)
                    {
                        if (m_alertsMap.find(it->id()) == m_alertsMap.end())
                        {
                            Wt::Dbo::ptr<Echoes::Dbo::EngOrg> engOrgPtr = m_session.find<Echoes::Dbo::EngOrg>()
                                    .where(QUOTE(TRIGRAM_ENGINE ID SEP TRIGRAM_ENGINE ID)" = ?").bind(m_enginePtr.id())
                                    .where(QUOTE(TRIGRAM_ORGANIZATION ID SEP TRIGRAM_ORGANIZATION ID)" = ?").bind(it->get()->alertSequence->alertValue->informationData->asset->organization.id())
                                    .where(QUOTE(TRIGRAM_ENG_ORG SEP "DELETE")" IS NULL")
                                    .limit(1);
                            log("info") << "Call responded";
                            if (engOrgPtr)
                            {

                                std::map<long long, std::string> confFileNames;
                                
                                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> >::const_iterator itMS = it->get()->alertMediaSpecializations.begin(); itMS != it->get()->alertMediaSpecializations.end(); ++itMS)
                                {
                                    cout << "media spec id: " << boost::lexical_cast<string>(itMS->id());
                                    std::string newConfName("/opt/echoes-alert/engine/conf/sec-alert" + boost::lexical_cast<string>(it->id()));
                                    newConfName += "-media";
                                    newConfName += boost::lexical_cast<string>(itMS->id());
                                    newConfName += ".conf";
                                    confFileNames.insert(std::make_pair(itMS->id(), newConfName));
                                    cout << "newConfName: " << newConfName << endl;
                                }

                                m_alertsMap[it->id()] = {
                                    true,
                                    confFileNames,
                                    -1,
                                    0,
                                    0,
                                    0,
                                    new boost::thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id()))
                                };
                                startAlert(*it, engOrgPtr);
                            }
                            else
                            {
                                log("debug") << "No Token for Alert: " << it->id();
                            }
                        }
                        else
                        {
                            m_alertsMap[it->id()].check = true;
                        }
                    }
                }

                if (alePtrCol.size() < (unsigned)m_enginePtr->nbThread)
                {
                    Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Alert>> newAlePtrCol = m_session.find<Echoes::Dbo::Alert>()
                            .where(QUOTE(TRIGRAM_ALERT SEP TRIGRAM_ENGINE SEP TRIGRAM_ENGINE ID)" IS NULL")
                            .where(QUOTE(TRIGRAM_ALERT SEP "DELETE")" IS NULL")
                            .limit(m_enginePtr->nbThread - alePtrCol.size());

                    log("debug") << "We have " << newAlePtrCol.size() << " more Alert(s) for this Engine in the database";

                    for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Alert>>::const_iterator it = newAlePtrCol.begin(); it != newAlePtrCol.end(); ++it)
                    {
                        if (it->get()->alertSequence.id() > 0)
                        {
                            Wt::Dbo::ptr<Echoes::Dbo::EngOrg> enoPtr = m_session.find<Echoes::Dbo::EngOrg>()
                                    .where(QUOTE(TRIGRAM_ENGINE ID SEP TRIGRAM_ENGINE ID)" = ?").bind(m_enginePtr.id())
                                    .where(QUOTE(TRIGRAM_ORGANIZATION ID SEP TRIGRAM_ORGANIZATION ID)" = ?").bind(it->get()->alertSequence->alertValue->informationData->asset->organization.id())
                                    .where(QUOTE(TRIGRAM_ENG_ORG SEP "DELETE")" IS NULL")
                                    .limit(1);

                            if (enoPtr)
                            {
                                it->modify()->engine = m_enginePtr;
                                it->flush();

                                std::map<long long, std::string> confFileNames;
                                
                                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> >::const_iterator itMS = it->get()->alertMediaSpecializations.begin(); itMS != it->get()->alertMediaSpecializations.end(); ++itMS)
                                {
                                    cout << "media spec id: " << boost::lexical_cast<string>(itMS->id());
                                    std::string newConfName("/opt/echoes-alert/engine/conf/sec-alert" + boost::lexical_cast<string>(it->id()));
                                    newConfName += "-media";
                                    newConfName += boost::lexical_cast<string>(itMS->id());
                                    newConfName += ".conf";
                                    confFileNames.insert(std::make_pair(itMS->id(), newConfName));
                                    cout << "newConfName: " << newConfName << endl;
                                }
                                
                                    it->modify()->engine = m_enginePtr;
                                    it->flush();

                                    m_alertsMap[it->id()] = {
                                        true,
                                        confFileNames,
                                        -1,
                                        0,
                                        0,
                                        0,
                                        new boost::thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id()))
                                    };
                                startAlert(*it, enoPtr);
                            }
                            else
                            {
                                log("debug") << "No Token for Alert: " << it->id();
                            }
                        }
                    }
                }

                transaction.commit();
            }
            catch (Wt::Dbo::Exception const& e)
            {
                log("error") << "Wt::Dbo: " << e.what();
            }

            vector<long long> alertToErase;
            for (map<long long, SecondStructure>::const_iterator it = m_alertsMap.begin(); it != m_alertsMap.end(); ++it)
            {
                if (it->second.check)
                {
                    m_alertsMap[it->first].check = false;
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
                m_alertsMap.erase(alertToErase[i]);
            }

            boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCheckAlert));
        }
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
        log("info") << "execl: " << strerror(errno);
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
        log("error") << "fork: " << strerror(errno);

    return pid;
}

void AlertProcessor::startAlert(Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr, Wt::Dbo::ptr<Echoes::Dbo::EngOrg> enoPtr)
{
    cout << "[ start Alert ]" << endl;
    for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> >::const_iterator itMS = alePtr->alertMediaSpecializations.begin(); itMS != alePtr->alertMediaSpecializations.end(); ++itMS)
    {
        cout << "mediaSpec id: " << itMS->id() << endl;
        cout << "media mail: " << itMS->get()->media->value << endl;
        std::string currentFile = m_alertsMap[alePtr.id()].secConfFilename.at(itMS->id());
        ofstream secConfFile(m_alertsMap[alePtr.id()].secConfFilename.at(itMS->id()).c_str());
        cout << "fileName: " << m_alertsMap[alePtr.id()].secConfFilename.at(itMS->id()).c_str() << endl;
        if (secConfFile)
        {
            Wt::Dbo::ptr<Echoes::Dbo::AlertSequence> asePtr = alePtr->alertSequence;
            long long iutId = asePtr->alertValue->informationData->informationUnit->unitType.id();
            if (iutId == Echoes::Dbo::EInformationUnitType::CUSTOM)
            {
                secConfFile << asePtr->alertValue->value;
            }
            else
            {
                secConfFile << "type=Single\n"
                        "ptype=PerlFunc\n"
                        "pattern= \\\n"
                        "sub { \\\n"
                        "  use strict; \\\n"
                        "  if ($_[0] cmp '') \\\n"
                        "  { \\\n"
                        "    my @inputs = split(';', $_[0]); \\\n"
                        "    my @ids; \\\n"
                        "    my @values; \\\n"
                        "    foreach my $i (0 .. $#inputs) \\\n"
                        "    { \\\n"
                        "      ($ids[$i], $values[$i]) = split(':', $inputs[$i]); \\\n"
                        "    } \\\n";

                bool firstAse = true;
                bool firstBase64 = true;
                string test;
                int cpt = 0;
                while (asePtr)
                {
                    iutId = asePtr->alertValue->informationData->informationUnit->unitType.id();

                    if (iutId != Echoes::Dbo::EInformationUnitType::NUMBER)
                    {
                        if (firstBase64)
                        {
                            secConfFile << "    use MIME::Base64; \\\n";
                        }
                        secConfFile << "    $values[" << cpt << "] = decode_base64($values[" << cpt << "]); \\\n";
                        firstBase64 = false;
                    }
                    else
                    {
                        secConfFile << "    if ($values[" << cpt << "] !~ /^([+-]?)(?=\\d|\\.\\d)\\d*(\\.\\d*)?([Ee]([+-]?\\d+))?$/) \\\n"
                                "    { \\\n"
                                "      exit; \\\n"
                                "    } \\\n";
                    }

                    if (!firstAse)
                    {
                        switch (*asePtr.get()->boolOperator)
                        {
                        case Echoes::Dbo::EBooleanOperator::AND:
                            test += " && ";
                            break;
                        case Echoes::Dbo::EBooleanOperator::OR:
                            test += " or ";
                            break;
                        }
                    }
                    switch (iutId)
                    {
                    case Echoes::Dbo::EInformationUnitType::NUMBER:
                        log("debug") << "We are entering in the switch of the case number";
                        test += "$values[" + boost::lexical_cast<string>(cpt) + "] ";
                        switch (asePtr->alertValue->alertCriteria.id())
                        {
                        case Echoes::Dbo::EAlertCriteria::LT:
                            log("debug") << "We are entering in the switch of the lt comparison";
                            test += "<";
                            break;
                        case Echoes::Dbo::EAlertCriteria::LE:
                            log("debug") << "We are entering in the switch of the le comparison";
                            test += "<=";
                            break;
                        case Echoes::Dbo::EAlertCriteria::EQ:
                            log("debug") << "We are entering in the switch of the eq comparison";
                            test += "==";
                            break;
                        case Echoes::Dbo::EAlertCriteria::NE:
                            log("debug") << "We are entering in the switch of the ne comparison";
                            test += "!=";
                            break;
                        case Echoes::Dbo::EAlertCriteria::GE:
                            log("debug") << "We are entering in the switch of the ge comparison";
                            test += ">=";
                            break;
                        case Echoes::Dbo::EAlertCriteria::GT:
                            log("debug") << "We are entering in the switch of the gt comparison";
                            test += ">";
                            break;
                        default:
                            log("error") << "Switch operator selection failed";
                            break;
                        }
                        test += " " + asePtr->alertValue->value.toUTF8();
                        break;
                    case Echoes::Dbo::EInformationUnitType::BOOL:
                    case Echoes::Dbo::EInformationUnitType::TEXT:
                        test += "$values[" + boost::lexical_cast<string>(cpt) + "] =~ /^" + asePtr->alertValue->value.toUTF8() + "$/";
                        break;
                    default:
                        log("error") << "Switch Information unit type check failed";
                        break;
                    }
                    firstAse = false;
                    asePtr = asePtr.get()->alertSequence;
                    cpt++;
                }

                secConfFile << "    if (" << test << ") \\\n"
                        "    { \\\n"
                        "      my $listIDs;  \\\n"
                        "      foreach my $id (@ids) { \\\n"
                        "        $listIDs .= $id; \\\n"
                        "        if($id != $ids[$#ids]) \\\n"
                        "        { \\\n"
                        "          $listIDs .= ','; \\\n"
                        "        } \\\n"
                        "      } \\\n"
                        "      my $res = '{\\\\\\\\\\\\\"information_value_ids\\\\\\\\\\\\\": ['.$listIDs.']}'; \\\n"
                        "      return ($res, (length($res) - 6)) \\\n"
                        "    }; \\\n"
                        "  }; \\\n"
                        "}\n";
            }

            std::string contexts = "";
            for (unsigned int i = 0; i < itMS->get()->timeSlots.size(); ++i)
            {
                if (i != 0)
                {
                    contexts += " || ";
                }
                contexts += "TIMESLOT" + boost::lexical_cast<string> (i);
            }
            secConfFile << "context=" + contexts + "\n";
            secConfFile << "desc=POST /alerts/" << alePtr.id() << "/trackings?eno_token=" << enoPtr->token << "&alert_media_specialization_id=" << boost::lexical_cast<string>(itMS->id()) << " HTTP/1.1\\n"
                    "Host: " << conf.getAPIHost() << "\\n"
                    "Content-Type: application/json; charset=utf-8\\n"
                    "Content-length: $3\\n"
                    "Connection: close\\n\\n"
                    "$1\\n\\n\n"
                    "action=shellcmd (/usr/bin/perl -e \"alarm(2); exec(\\\"/usr/bin/printf \\'%s\\' > /home/vpl/timeslot.tmp | /usr/bin/openssl s_client -quiet -crlf -connect " << conf.getAPIHost() << ":" << conf.getAPIPort() << "\\\")\")\n";
            
            int i = 0;
            for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertTimeSlot> >::const_iterator itTS = itMS->get()->timeSlots.begin(); itTS != itMS->get()->timeSlots.end(); ++itTS)
            {
                secConfFile << "\ntype=Calendar";
                secConfFile << "\ntime=* "
//                        + boost::lexical_cast<string>(itTS->get()->start)
                          + std::string("* * * *");
//                        + itTS->get()->months
//                        + " "
//                        + itTS->get()->days
                secConfFile << "\ndesc=TIMESLOT" + boost::lexical_cast<string> (i);
                secConfFile << "\naction=create %s " + boost::lexical_cast<string> (itTS->get()->duration * 3600);
                ++i;
            }
            
            secConfFile.close();
        }
        else
        {
            log("error") << "Unable to open/create file: " << currentFile;
        }

        m_alertsMap[alePtr.id()].secPID = popen_sec(currentFile, &m_alertsMap[alePtr.id()].secInFP, &m_alertsMap[alePtr.id()].secOutFP, &m_alertsMap[alePtr.id()].secErrFP);
        if (m_alertsMap[alePtr.id()].secPID <= 0)
        {
            log("error") << "Unable to exec SEC: " << currentFile;
        }
    }
}

void AlertProcessor::stopAllAlerts()
{
    for (map<long long, SecondStructure>::const_iterator it = m_alertsMap.begin(); it != m_alertsMap.end(); ++it)
    {
        stopAlert(it->first);
        it->second.ivaThread->interrupt();
        delete it->second.ivaThread;
    }
}   

void AlertProcessor::stopAlert(const long long alertID)
{
    kill(m_alertsMap[alertID].secPID, SIGTERM);
    close(m_alertsMap[alertID].secInFP);
    close(m_alertsMap[alertID].secOutFP);
    close(m_alertsMap[alertID].secErrFP);
    waitpid(m_alertsMap[alertID].secPID, NULL, 0);
    m_alertsMap[alertID].secPID = -1;

    for (std::map<long long, std::string>::const_iterator itFile = m_alertsMap[alertID].secConfFilename.begin() ; itFile != m_alertsMap[alertID].secConfFilename.end(); ++itFile)
    {
        if (remove(itFile->second.c_str()) < 0)
        {
            log("info") << itFile->second << ": " << strerror(errno);
        }
    }

    try
    {
        Wt::Dbo::Transaction transaction(m_session, true);

        Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr = m_session.find<Echoes::Dbo::Alert>()
                .where(QUOTE(TRIGRAM_ALERT ID)" = ?").bind(alertID)
                .where(QUOTE(TRIGRAM_ALERT SEP "DELETE")" IS NULL")
                .limit(1);

        alePtr.modify()->engine = Wt::Dbo::ptr<Echoes::Dbo::Engine>();
        alePtr.flush();

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e)
    {
        log("error") << "Wt::Dbo: " << e.what();
    }
}

void AlertProcessor::informationValueLoop(const long long alertID)
{
    if (alertID < 1)
    {
        log("error") << alertID << ": alert ID invalid";
        return;
    }

    unsigned idx = 0;
    // Waiting for SEC instance creation
    while (m_alertsMap[alertID].secPID <= 0)
    {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        idx++;
        if (idx % 10 == 0)
            log("warning") << "No SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;
        if (idx == 30)
        {
            log("error") << "Stop IVA Collect for alert ID: " << alertID;
            return;
        }
    }
    log("info") << "SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;

    boost::thread(boost::bind(&AlertProcessor::secLogLoop, this, m_alertsMap[alertID].secOutFP, "info"));
    boost::thread(boost::bind(&AlertProcessor::secLogLoop, this, m_alertsMap[alertID].secErrFP, "error"));    

    struct IvaStruct {
        long long idaId = 0;
        long long filId = 0;
        long long astId = 0;
        long long infId = 0;
        long long iutId = 0;
        int posKeyValue = 0;
        string keyValue = "";  
        Wt::Dbo::ptr<Echoes::Dbo::InformationData> idakeyPtr;  
        long long ivaId = 0;        
        bool isIVAFound = false;        
        long long ivaKeyId = 0;        
        string ivaValue = "";
    };
    vector<IvaStruct> ivaStructs;

    // We get the data to be able to find all the IVAs needed
    try
    {
        log("debug") << "Retrieve Alert in InformationValueLoop";
        Wt::Dbo::Transaction transaction(m_session, true);

        // Getting the dbo ptr on the alert currently processed
        Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr = m_session.find<Echoes::Dbo::Alert>()
                .where(QUOTE(TRIGRAM_ALERT ID)" = ?").bind(alertID)
                .where(QUOTE(TRIGRAM_ALERT SEP "DELETE")" IS NULL")
                .limit(1);

        if (alePtr)
        {            
            Wt::Dbo::ptr<Echoes::Dbo::AlertSequence> asePtr = alePtr->alertSequence;
            while(asePtr)
            {    
                IvaStruct ivaStruct;
                ivaStruct.idaId = asePtr->alertValue->informationData.id();
                ivaStruct.infId = asePtr->alertValue->informationData->information.id();
                ivaStruct.filId = asePtr->alertValue->informationData->filter.id();
                ivaStruct.astId = asePtr->alertValue->informationData->asset.id();
                ivaStruct.iutId = asePtr->alertValue->informationData->informationUnit->unitType.id();
                ivaStruct.posKeyValue = asePtr->alertValue->informationData->filter->posKeyValue;

                if (ivaStruct.posKeyValue > 0)
                {
                    //looking for the ida about the key
                    ivaStruct.keyValue = asePtr->alertValue->keyValue.get().toUTF8();
                    ivaStruct.idakeyPtr = m_session
                            .find<Echoes::Dbo::InformationData>()
                            .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP TRIGRAM_FILTER SEP TRIGRAM_FILTER ID) " = ?")
                            .bind(ivaStruct.filId)
                            .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP TRIGRAM_ASSET SEP TRIGRAM_ASSET ID) " = ?")
                            .bind(ivaStruct.astId)
                            .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP TRIGRAM_INFORMATION SEP TRIGRAM_INFORMATION ID) " = ?")
                            .bind(ivaStruct.infId)
                            .where(QUOTE(TRIGRAM_INFORMATION_DATA SEP "FILTER_FIELD_INDEX")" = ?")
                            .bind(ivaStruct.posKeyValue)
                            .limit(1);

                    if (ivaStruct.idakeyPtr)
                    {
                        log("debug") << "ptr found, ok";
                    }
                    else
                    {
                        log("warning") << "no Ida in database for this poskey";
                        transaction.commit();
                        return;
                    }
                }
                ivaStructs.push_back(ivaStruct);
                asePtr = asePtr->alertSequence;
            }
        }
        else
        {
            log("warning") << alertID << ": no alert in database for this ID";
            transaction.commit();
            return;
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e)
    {
        log("error") << "Wt::Dbo: " << e.what();
        return;
    }
    
    bool areIVAsFound = false;   
    
    // Arbitrary definition
    const unsigned period = 60;

    Wt::WDateTime searchDateTime = Wt::WDateTime::currentDateTime().addSecs(-period);
    
    while (!areIVAsFound && m_alertsMap[alertID].secPID > 0)
    {    
        areIVAsFound = true;
        for(vector<IvaStruct>::iterator it = ivaStructs.begin(); it < ivaStructs.end(); it++)
        {        
            // first case, we have a pos key value and we need to get the lotNumber and the lineNumber
            if (it->posKeyValue > 0)
            {
                bool isIVAKeyFound = false;
                int lotNumber = 0;
                int lineNumber = 0;
                
                log("debug") << "Retrieve IVA Key after: " << searchDateTime.toString("yyyy-MM-dd hh:mm:ss");
                try
                {
                    Wt::Dbo::Transaction transaction(m_session, true);

                    Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaKeyPtr = m_session.find<Echoes::Dbo::InformationValue>()
                            .where("\"IVA_IDA_IDA_ID\" = ?").bind(it->idakeyPtr.id())
                            .where("\"IVA_STATE\" = ?").bind(0)
                            .where("\"IVA_VALUE\" = ?").bind(it->keyValue)
                            .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString("yyyy-MM-dd hh:mm:ss").toUTF8())
                            .orderBy("\"IVA_ID\" DESC")
                            .limit(1);

                    if (ivaKeyPtr)
                    {
                        isIVAKeyFound = true;
                        it->ivaKeyId = ivaKeyPtr.id();
                        lotNumber = ivaKeyPtr->lotNumber;
                        lineNumber = ivaKeyPtr->lineNumber;
                    }

                    transaction.commit();
                }
                catch (Wt::Dbo::Exception const& e)
                {
                    log("error") << "Wt::Dbo: " << e.what();
                }
                if (isIVAKeyFound)
                {
                    log("debug") << "Retrieve IVA after: " << searchDateTime.toString("yyyy-MM-dd hh:mm:ss");
                    try
                    {
                        Wt::Dbo::Transaction transaction(m_session, true);
                        Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr = m_session.find<Echoes::Dbo::InformationValue>()
                                .where("\"IVA_IDA_IDA_ID\" = ?").bind(it->idaId)
                                .where("\"IVA_STATE\" = ?").bind(0)
                                .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString("yyyy-MM-dd hh:mm:ss").toUTF8())
                                .where("\"IVA_LOT_NUM\" = ?").bind(lotNumber)
                                .where("\"IVA_LINE_NUM\" = ?").bind(lineNumber)
                                .orderBy("\"IVA_ID\" DESC")
                                .limit(1);

                        if (ivaPtr)
                        {
                            it->isIVAFound = true;
                            it->ivaId = ivaPtr.id();
                            it->ivaValue = ivaPtr->value.toUTF8();
                        }
                        transaction.commit();
                    }
                    catch (Wt::Dbo::Exception const& e)
                    {
                        log("error") << "Wt::Dbo: " << e.what();
                    }
                }
            }
            // second case, simple information without poskey
            else
            {
                log("debug") << "Retrieve IVA after: " << searchDateTime.toString("yyyy-MM-dd hh:mm:ss");
                try
                {
                    Wt::Dbo::Transaction transaction(m_session, true);

                    Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr = m_session.find<Echoes::Dbo::InformationValue>()
                            .where("\"IVA_IDA_IDA_ID\" = ?").bind(it->idaId)
                             .where("\"IVA_STATE\" = ?").bind(0)
                            .where("\"IVA_CREA_DATE\" >= ?").bind(searchDateTime.toString("yyyy-MM-dd hh:mm:ss").toUTF8())
                            .orderBy("\"IVA_ID\" DESC")
                            .limit(1);
                    if (ivaPtr)
                    {
                        it->isIVAFound = true;
                        it->ivaId = ivaPtr.id();
                        it->ivaValue = ivaPtr->value.toUTF8();
                    }

                    transaction.commit();
                }
                catch (Wt::Dbo::Exception const& e)
                {
                    log("error") << "Wt::Dbo: " << e.what();
                }
            }
            areIVAsFound &= it->isIVAFound;
        }
        if (!areIVAsFound)
        {
            searchDateTime = searchDateTime.addSecs(period);
            informationValueSleep(period, searchDateTime);
        }
    }

    while (m_alertsMap[alertID].secPID > 0)
    {
        // creating the input for SEC
        if (areIVAsFound)
        {
            string inputSEC;
            for(vector<IvaStruct>::iterator it = ivaStructs.begin(); it < ivaStructs.end(); it++)
            { 
                inputSEC += boost::lexical_cast<string>(it->ivaId) + ":";
                switch (it->iutId)
                {
                case Echoes::Dbo::EInformationUnitType::NUMBER:
                    inputSEC += it->ivaValue;
                    break;
                default:
                    inputSEC += Wt::Utils::base64Encode(it->ivaValue);
                    break;
                }
                if(it < ivaStructs.end()-1)
                {
                    inputSEC += ";";
                }
                it->isIVAFound = false;
            }
            
            inputSEC += "\n";
            log("debug") << "Send IVA to SEC";
            write(m_alertsMap[alertID].secInFP, inputSEC.c_str(), inputSEC.size());
        }

        searchDateTime = searchDateTime.addSecs(period);
        informationValueSleep(period, searchDateTime);

        try
        {
            Wt::Dbo::Transaction transaction(m_session, true);

            areIVAsFound = true;

            Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr;            
            for(vector<IvaStruct>::iterator it = ivaStructs.begin(); it < ivaStructs.end(); it++)
            { 
                if (it->posKeyValue > 0)
                {
                    log("debug") << "Retrieve IVA Key";

                    Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaKeyPtr = m_session.find<Echoes::Dbo::InformationValue>()
                            .where("\"IVA_ID\" > ?").bind(it->ivaKeyId)
                            .where("\"IVA_IDA_IDA_ID\" = ?").bind(it->idakeyPtr.id())
                            .where("\"IVA_STATE\" = ?").bind(0)
                            .where("\"IVA_VALUE\" = ?").bind(it->keyValue)
                            .orderBy("\"IVA_ID\" DESC")
                            .limit(1);

                    it->ivaKeyId = ivaKeyPtr.id();
                    if (ivaKeyPtr)
                    {
                        log("debug") << "Retrieve IVA";
                        ivaPtr = m_session.find<Echoes::Dbo::InformationValue>()
                            .where("\"IVA_IDA_IDA_ID\" = ?").bind(it->idaId)
                            .where("\"IVA_STATE\" = ?").bind(0)
                            .where("\"IVA_LOT_NUM\" = ?").bind(ivaKeyPtr->lotNumber)
                            .where("\"IVA_LINE_NUM\" = ?").bind(ivaKeyPtr->lineNumber)
                            .orderBy("\"IVA_ID\" DESC")
                            .limit(1);
                     }
                }
                else
                {
                    log("debug") << "Retrieve IVA";
                    ivaPtr = m_session.find<Echoes::Dbo::InformationValue>()
                            .where("\"IVA_ID\" > ?").bind(it->ivaId)
                            .where("\"IVA_IDA_IDA_ID\" = ?").bind(it->idaId)
                             .where("\"IVA_STATE\" = ?").bind(0)
                            .orderBy("\"IVA_ID\" DESC")
                            .limit(1);
                }

                if (ivaPtr)
                {
                    it->isIVAFound = true;
                    it->ivaId = ivaPtr.id();
                    it->ivaValue = ivaPtr->value.toUTF8();
                }
                
                areIVAsFound &= it->isIVAFound;
            }

            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            log("error") << "Wt::Dbo: " << e.what();
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

    __gnu_cxx::stdio_filebuf<char> fileBuf(fd, ios::in);
    istream is(&fileBuf);

    while (getline(is, line))
    {
        log(logLevel) << "SEC: " << line;
    }

    return;
}

