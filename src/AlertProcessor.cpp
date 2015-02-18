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

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

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
                                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> >::const_iterator itMS = it->get()->alertMediaSpecializations.begin(); itMS != it->get()->alertMediaSpecializations.end(); ++itMS)
                                {
                                    std::string newConfName;
                                    #ifdef NDEBUG
                                    newConfName += "/opt/echoes-alert/engine/etc/sec-alert";
                                    #else
                                    newConfName += "conf/sec-alert";
                                    #endif

                                    newConfName += boost::lexical_cast<string>(it->id());
                                    newConfName += "-media";
                                    newConfName += boost::lexical_cast<string>(itMS->id());
                                    newConfName += ".conf";

                                    m_alertsMap[it->id()][itMS->id()] = {
                                            true,
                                            false,
                                            newConfName,
                                            -1,
                                            0,
                                            0,
                                            0,
                                            new boost::thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id(), itMS->id()))
                                    };
                                }
                                                               
                                startAlert(*it, engOrgPtr);
                            }
                            else
                            {
                                log("debug") << "No Token for Alert: " << it->id();
                            }
                        }
                        else
                        {
                            for (std::map<long long, struct AlertSpecs>::const_iterator itMS = m_alertsMap[it->id()].begin() ; itMS != m_alertsMap[it->id()].end() ; ++itMS)
                            {
                                m_alertsMap[it->id()][itMS->first].check = true;
                            }
                        }
                    }
                    else
                    {
                        log("debug") << "Id <= 0: " << it->id();
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
                                
                                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> >::const_iterator itMS = it->get()->alertMediaSpecializations.begin(); itMS != it->get()->alertMediaSpecializations.end(); ++itMS)
                                {
                                    std::string newConfName;
                                    #ifdef NDEBUG
                                    newConfName += "/opt/echoes-alert/engine/etc/sec-alert";
                                    #else
                                    newConfName += "conf/sec-alert";
                                    #endif

                                    newConfName += boost::lexical_cast<string>(it->id());
                                    newConfName += "-media";
                                    newConfName += boost::lexical_cast<string>(itMS->id());
                                    newConfName += ".conf";

                                    
                                    m_alertsMap[it->id()][itMS->id()] = {
                                            true,
                                            false,
                                            newConfName,
                                            -1,
                                            0,
                                            0,
                                            0,
                                            new boost::thread(boost::bind(&AlertProcessor::informationValueLoop, this, it->id(), itMS->id()))
                                    };
                                }
                                
                                
                                it->modify()->engine = m_enginePtr;
                                it->flush();

                                
                                startAlert(*it, enoPtr);
                            }
                            else
                            {
                                log("debug") << "No Token for Alert: " << it->id();
                            }
                        }
                    }
                }
                else
                {
                    log("debug") << "Max nb thread reached.";
                }

                transaction.commit();
            }
            catch (Wt::Dbo::Exception const& e)
            {
                log("error") << "Wt::Dbo: " << e.what();
            }

            vector<std::pair<long long, long long>> alertToErase;
            for (map<long long, std::map<long long, struct AlertSpecs>>::const_iterator itA = m_alertsMap.begin(); itA != m_alertsMap.end(); ++itA)
            {
                for (std::map<long long, struct AlertSpecs>::const_iterator itMS = m_alertsMap[itA->first].begin() ; itMS != m_alertsMap[itA->first].end() ; ++itMS)
                {
                    if (itMS->second.check)
                    {
                        m_alertsMap[itA->first][itMS->first].check = false;
                    }
                    else
                    {
                        stopAlert(itA->first, itMS->first);
                        itMS->second.ivaThread->interrupt();
                        delete itMS->second.ivaThread;
                        alertToErase.push_back(std::make_pair(itA->first, itMS->first));
                        
                    }
                }
            }

            for (vector<std::pair<long long, long long>>::iterator itER = alertToErase.begin() ; itER != alertToErase.end() ; ++itER)
            {
                m_alertsMap[itER->first].erase(itER->second);
            }

            boost::this_thread::sleep(boost::posix_time::seconds(conf.sleepThreadCheckAlert));
        }
    }

    return res;
}

pid_t AlertProcessor::popen_sec(const long long alertID, const long long mediaSpecID, int *infp, int *outfp, int *errfp)
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
              (m_alertsMap[alertID][mediaSpecID].start ? "--intevents" : ""),
              ("-conf=" + m_alertsMap[alertID][mediaSpecID].secConfFilename).c_str(),
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

std::string AlertProcessor::setTimeSlotContext(int numTimeSlot, int start, int duration, std::vector<std::string> days, std::vector<std::string> months)
{
    std::string output("");
    
    bool isDay = false;
    bool isMonth = false;

    Wt::WTime currentTime = Wt::WTime::currentServerTime();
    Wt::WDate currentDate = Wt::WDate::currentDate();

    int currentDay = -2;
    int finish = start + duration;
    int maxHour = (finish > 24 ? 24 : finish);
    
    if (start <= currentTime.hour())
    {
        if (currentTime.hour() < maxHour)
        {
            currentDay = currentDate.day() % 7;
        }
    }
    else if (0 <= currentTime.hour() && finish > 24)
    {
        if (currentTime.hour() < finish)
        {
            finish = finish % 24;
            currentDay = (currentDate.day() % 7) - 1;
            if (currentDay == -1)
            {
                currentDay = 6;
            }
        }
    }
    
    for (auto itD = days.begin() ; itD != days.end() ; ++itD)
    {
        if (!itD->compare(boost::lexical_cast<string> (currentDay)))
        {
            isDay = true;
        }
    }

    for (auto itM = months.begin() ; itM != months.end() ; ++itM)
    {
        if (!itM->compare(boost::lexical_cast<string> (currentDate.month())))
        {
            isMonth = true;
        }
    }
    
    if (isDay && isMonth)
    {
        output += "type=Single";
        output += "\nptype=RegExp";
        output += "\npattern=^(?:SEC_STARTUP|SEC_RESTART)$";
        output += "\ndesc=TIMESLOT" + boost::lexical_cast<string> (numTimeSlot);
        output += "\naction=create %s " + boost::lexical_cast<string> ((finish - currentTime.hour()) * 3600 - currentTime.minute() * 60);
        output += "\n\n";
    }
    
    return (output);
}

void AlertProcessor::startAlert(Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr, Wt::Dbo::ptr<Echoes::Dbo::EngOrg> enoPtr)
{
    for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> >::const_iterator itMS = alePtr->alertMediaSpecializations.begin(); itMS != alePtr->alertMediaSpecializations.end(); ++itMS)
    {
        std::string currentFile = m_alertsMap[alePtr.id()][itMS->id()].secConfFilename;
        ofstream secConfFile(m_alertsMap[alePtr.id()][itMS->id()].secConfFilename.c_str());

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
                Wt::WString inputRule;
                Wt::WString inputAction("");

                std::vector<Wt::WString> createContexts;
                std::vector<Wt::WString> deleteContexts;
                Wt::WString masterRule;

                inputRule = "type=Single\n"
                        "ptype=PerlFunc\n"
                        "pattern= \\\n"
                        "sub { \\\n"
                        "   use strict; \\\n"
                        "   if ($_[0] cmp '') \\\n"
                        "   { \\\n"
                        "       my @inputs = split(';', $_[0]); \\\n"
                        "       my @ids; \\\n"
                        "       my @values; \\\n"
                        "       my @listRes; \\\n"
                        "       foreach my $i (0 .. $#inputs) \\\n"
                        "       { \\\n"
                        "           ($ids[$i], $values[$i]) = split(':', $inputs[$i]); \\\n"
                        "       } \\\n"
                        "       if ($ids[0] =~ /^[0-9]+$/) \\\n"
                        "       {\\\n";

                inputAction += "action=";

                masterRule = "type=Single\n"
                        "ptype=RegExp\n"
                        "pattern=^MASTER RULE:([^-]*)-(.*)$\n"
                        "context=(";


                int i = 0;
                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::AlertTimeSlot> >::const_iterator itTS = itMS->get()->timeSlots.begin(); itTS != itMS->get()->timeSlots.end(); ++itTS)
                {
                    std::vector<std::string> months;
                    std::vector<std::string> days;
                    std::string s_months(itTS->get()->months.toUTF8());
                    std::string s_days(itTS->get()->days.toUTF8());
                    boost::split(months, s_months, boost::is_any_of(","), boost::token_compress_on);
                    boost::split(days, s_days, boost::is_any_of(","), boost::token_compress_on);

                    std::string timeSlotContext("");
                    timeSlotContext = setTimeSlotContext(i, itTS->get()->start, itTS->get()->duration, days, months);
                    if (!timeSlotContext.empty())
                    {
                        m_alertsMap[alePtr.id()][itMS->id()].start = true;
                    }

                    secConfFile << timeSlotContext;

                    secConfFile << "type=Calendar";
                    secConfFile << "\ntime=* "
                            + boost::lexical_cast<string>(itTS->get()->start)
                            + std::string(" * ")
                            + itTS->get()->months
                            + " "
                            + itTS->get()->days;
                    secConfFile << "\ndesc=TIMESLOT" + boost::lexical_cast<string> (i);
                    secConfFile << "\naction=create %s " + boost::lexical_cast<string> (itTS->get()->duration * 3600);

                    secConfFile << "\n\n";
                    ++i;
                }

                std::string contexts = "(";
                for (unsigned int count = 0; count < itMS->get()->timeSlots.size(); ++count)
                {
                    if (count != 0)
                    {
                        contexts += " || ";
                    }
                    contexts += "TIMESLOT" + boost::lexical_cast<string> (count);
                }
                contexts += ") && (";

                if (itMS->get()->timeSlots.size())
                {
                    masterRule += contexts;
                }

                int cpt = 0;
                bool firstAse = true;
                bool firstBase64 = true;
                while (asePtr)
                {
                    Wt::WString test;
                    Wt::WString flapping;
                    flapping = (asePtr->alertValue->flapping == 0 ? "; " : boost::lexical_cast<string>(asePtr->alertValue->flapping * 60) + " (");
                    Wt::WString createContext("type=Single\n"
                                              "ptype=RegExp\n"
                                              "pattern=^RULE"
                                              + boost::lexical_cast<string>(cpt)
                                              + ":true$\n"
                                              "context=!RULE"
                                              + boost::lexical_cast<string>(cpt)
                                              + "\ndesc=RULE"
                                              + boost::lexical_cast<string>(cpt)
                                              + "\naction=create %s "
                                              + flapping +
                                              +"create END"
                                              + boost::lexical_cast<string>(cpt)
                                              + (asePtr->alertValue->flapping == 0 ? "" : ";)")
                                              + "\n");
                    createContexts.push_back(createContext);

                    Wt::WString deleteContext("type=Single\n"
                                              "ptype=RegExp\n"
                                              "pattern=^RULE"
                                              + boost::lexical_cast<string>(cpt)
                                              + ":false$\n"
                                              "desc=RULE"
                                              + boost::lexical_cast<string>(cpt)
                                              + "\naction=delete %s ; delete END"
                                              + boost::lexical_cast<string>(cpt)
                                              + "\n");
                    deleteContexts.push_back(deleteContext);

                    iutId = asePtr->alertValue->informationData->informationUnit->unitType.id();
                    if (iutId != Echoes::Dbo::EInformationUnitType::NUMBER)
                    {
                        if (firstBase64)
                        {
                            inputRule += "        use MIME::Base64; \\\n";
                        }
                        inputRule += "        $values["
                                + boost::lexical_cast<string>(cpt)
                                + "] = decode_base64($values["
                                + boost::lexical_cast<string>(cpt)
                                + "]); \\\n";
                        firstBase64 = false;
                    }
                    else
                    {
                        inputRule += "          if ($values["
                                + boost::lexical_cast<string>(cpt)
                                + "] !~ /^([+-]?)(?=\\d|\\.\\d)\\d*(\\.\\d*)?([Ee]([+-]?\\d+))?$/) \\\n"
                                "      { \\\n"
                                "          exit; \\\n"
                                "      } \\\n";
                    }

                    if (!firstAse)
                    {
                        switch (*asePtr.get()->boolOperator)
                        {
                        case Echoes::Dbo::EBooleanOperator::AND:
                            masterRule += " && ";
                            break;
                        case Echoes::Dbo::EBooleanOperator::OR:
                            masterRule += " || ";
                            break;
                        }
                    }
                    masterRule += "END" + boost::lexical_cast<string>(cpt);

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
                    inputRule += "        $listRes[" + boost::lexical_cast<string>(cpt) + "] = 'RULE" + boost::lexical_cast<string>(cpt) + ":';\\\n";
                    inputRule += "        if (" + test + ") \\\n"
                            "        { \\\n"
                            "           $listRes[" + boost::lexical_cast<string>(cpt) + "] .= 'true'; \\\n"
                            "        } \\\n"
                            "        else \\\n"
                            "        { \\\n"
                            "            $listRes[" + boost::lexical_cast<string>(cpt) + "] .= 'false'; \\\n"
                            "        } \\\n";

                    inputAction += "event $" + boost::lexical_cast<string>(cpt + 1) + " ; ";

                    firstAse = false;
                    asePtr = asePtr.get()->alertSequence;
                    cpt++;
                }

                inputAction += "event 1 $" + boost::lexical_cast<string>(cpt + 1) + " ;";
                inputRule += "          my $listIDs;  \\\n"
                        "           foreach my $i (0 .. $#ids) \\\n"
                        "           { \\\n"
                        "               $listIDs .= $ids[$i]; \\\n"
                        "               if($i != $#ids) \\\n"
                        "               { \\\n"
                        "                   $listIDs .= ','; \\\n"
                        "               } \\\n"
                        "           } \\\n"
                        "           my $res = '{\\\\\\\\\\\\\"information_value_ids\\\\\\\\\\\\\": ['.$listIDs.'],\\\\\\\\\\\\\"alert_id\\\\\\\\\\\\\": " + boost::lexical_cast<string>(alePtr.id()) + "}'; \\\n"
                        "           $listRes[" + boost::lexical_cast<string>(cpt) + "] = 'MASTER RULE:'.$listIDs.'-'.(length($res) - 12); \\\n"
                        "           return (@listRes) \\\n"
                        "       }; \\\n"
                        "   };\\\n"
                        "}\n";

                if (itMS->get()->timeSlots.size())
                {
                    masterRule += ")";
                }
                
                masterRule += ")\ndesc=POST /messages?eno_token=" + enoPtr->token + "&alert_media_specialization_id=" + boost::lexical_cast<string>(itMS->id()) + " HTTP/1.1\\n"
                        "Host: " + conf.getAPIHost() + "\\n"
                        "Content-Type: application/json; charset=utf-8\\n"
                        "Content-length: $2\\n"
                        "Connection: close\\n\\n"
                        "{\\\\\\\"information_value_ids\\\\\\\": [$1],\\\\\\\"alert_id\\\\\\\":" + boost::lexical_cast<string>(alePtr.id()) + "}\\n\\n\n"
                        "action=shellcmd (/usr/bin/perl -e \"alarm(2); exec(\\\"/usr/bin/printf \\'%s\\' | /usr/bin/openssl s_client -quiet -crlf -connect " + conf.getAPIHost() + ":" + boost::lexical_cast<string>(conf.getAPIPort()) + "\\\")\")\n";


                secConfFile << inputRule;
                secConfFile << "desc=dsds\n";
                secConfFile << inputAction << "\n";
                for (unsigned int i = 0; i < createContexts.size(); ++i)
                {
                    secConfFile << "\n";
                    secConfFile << createContexts.at(i);
                    secConfFile << "\n";
                    secConfFile << deleteContexts.at(i);
                }

                secConfFile << "\n";
                secConfFile << masterRule;
            }
            secConfFile.close();
        }
        else
        {
            log("error") << "Unable to open/create file: " << currentFile;
        }
        
        m_alertsMap[alePtr.id()][itMS->id()].secPID = popen_sec(alePtr.id(), itMS->id(), &m_alertsMap[alePtr.id()][itMS->id()].secInFP, &m_alertsMap[alePtr.id()][itMS->id()].secOutFP, &m_alertsMap[alePtr.id()][itMS->id()].secErrFP);
        if (m_alertsMap[alePtr.id()][itMS->id()].secPID <= 0)
        {
            log("error") << "Unable to exec SEC: " << currentFile;
        }
    }
}

void AlertProcessor::stopAllAlerts()
{
    for (map<long long, std::map<long long, struct AlertSpecs>>::const_iterator itA = m_alertsMap.begin(); itA != m_alertsMap.end(); ++itA)
    {
        for (std::map<long long, struct AlertSpecs>::const_iterator itMS = itA->second.begin() ; itMS != itA->second.end() ; ++itMS)
        {
            stopAlert(itA->first, itMS->first);
            itMS->second.ivaThread->interrupt();
            delete itMS->second.ivaThread;
        }
    }
}   

void AlertProcessor::stopAlert(const long long alertID, const long long mediaSpecID)
{
    kill(m_alertsMap[alertID][mediaSpecID].secPID, SIGTERM);
    close(m_alertsMap[alertID][mediaSpecID].secInFP);
    close(m_alertsMap[alertID][mediaSpecID].secOutFP);
    close(m_alertsMap[alertID][mediaSpecID].secErrFP);
    waitpid(m_alertsMap[alertID][mediaSpecID].secPID, NULL, 0);
    m_alertsMap[alertID][mediaSpecID].secPID = -1;

    if (remove(m_alertsMap[alertID][mediaSpecID].secConfFilename.c_str()) < 0)
    {
        log("info") << m_alertsMap[alertID][mediaSpecID].secConfFilename << ": " << strerror(errno);
    }

    if (m_alertsMap[alertID].size() == 0)
    {
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
}

void AlertProcessor::informationValueLoop(const long long alertID, const long long mediaSpecID)
{
    if (alertID < 1)
    {
        log("error") << alertID << ": alert ID invalid";
        return;
    }

    unsigned idx = 0;
    // Waiting for SEC instance creation

    while (m_alertsMap[alertID][mediaSpecID].secPID <= 0)
    {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        idx++;
        if (idx % 10 == 0)
        {
            log("warning") << "No SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;
        }
        if (idx == 30)
        {
            log("error") << "Stop IVA Collect for alert ID: " << alertID;
            return;
        }
    }
    log("info") << "SEC instance after " << boost::lexical_cast<string>(idx) << "s for alert ID: " << alertID;

    boost::thread(boost::bind(&AlertProcessor::secLogLoop, this, m_alertsMap[alertID][mediaSpecID].secOutFP, "info"));
    boost::thread(boost::bind(&AlertProcessor::secLogLoop, this, m_alertsMap[alertID][mediaSpecID].secErrFP, "error"));
    boost::thread(boost::bind(&AlertProcessor::secLogLoop, this, 1, "info"));

    struct IvaStruct
    {
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
            while (asePtr)
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

    while (!areIVAsFound && m_alertsMap[alertID][mediaSpecID].secPID > 0)
    {
        areIVAsFound = true;
        for (vector<IvaStruct>::iterator it = ivaStructs.begin(); it < ivaStructs.end(); it++)
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

    while (m_alertsMap[alertID][mediaSpecID].secPID > 0)
    {
        // creating the input for SEC
        if (areIVAsFound)
        {
            string inputSEC;
            for (vector<IvaStruct>::iterator it = ivaStructs.begin(); it < ivaStructs.end(); it++)
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
                if (it < ivaStructs.end() - 1)
                {
                    inputSEC += ";";
                }
                it->isIVAFound = false;
            }

            inputSEC += "\n";
            log("debug") << "Send IVA to SEC";
            // input, content, content size
            write(m_alertsMap[alertID][mediaSpecID].secInFP, inputSEC.c_str(), inputSEC.size());
        }

        searchDateTime = searchDateTime.addSecs(period);
        informationValueSleep(period, searchDateTime);

        try
        {
            Wt::Dbo::Transaction transaction(m_session, true);

            areIVAsFound = true;

            Wt::Dbo::ptr<Echoes::Dbo::InformationValue> ivaPtr;
            for (vector<IvaStruct>::iterator it = ivaStructs.begin(); it < ivaStructs.end(); it++)
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

