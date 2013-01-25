#include "AlertSender.h"

AlertSender::AlertSender() {
}

AlertSender::~AlertSender() {
}


Wt::Dbo::ptr<AlertTracking> AlertSender::createAlertTrackingNumber(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertMediaSpecialization> amsPtr)
{
    //we get the session actually opened
    AlertTracking *newAlertTracking = new AlertTracking();
    
    newAlertTracking->alert = alertPtr;
    newAlertTracking->mediaValue = amsPtr.get()->mediaValue;

    // WARNING : SendDate must be set by the API when the alert was sent, not before
    Wt::WDateTime *sendDate = new Wt::WDateTime();
    newAlertTracking->sendDate = *sendDate;
    Wt::Dbo::ptr<AlertTracking> alertTrackingPtr;

    Session * session = SessionPool::getInstance()->getSession();
    try
    {
        Transaction transaction(*session);        
        alertTrackingPtr = session->add<AlertTracking>(newAlertTracking);
        alertTrackingPtr.flush();
        transaction.commit();
        
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertSender] " << e.what() ;
    }
    delete sendDate;
    delete newAlertTracking;
    SessionPool::getInstance()->returnSession(session);
    return alertTrackingPtr;
}

int AlertSender::sendSMS(Session * session, Wt::Dbo::ptr<InformationValue> informationValuePtr, Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr, Wt::Dbo::ptr<AlertMediaSpecialization> amsPtr)
{

    Wt::WString phoneNumber = amsPtr.get()->mediaValue.get()->value;
    Wt::WString assetConcerned = informationValuePtr.get()->asset.get()->name;
    Wt::WString alertName = alertPtr.get()->name;
    Wt::WString informationReceived = informationValuePtr.get()->value;
    Wt::WString unit = alertPtr.get()->alertValue.get()->information.get()->pk.unit.get()->name;
    Wt::WString alertValue = alertPtr.get()->alertValue.get()->value;
    Wt::WString date = informationValuePtr.get()->creationDate.toString();
    Wt::WDateTime now = Wt::WDateTime::currentDateTime(); //for setting the send date of the alert
    Wt::WString key;
    Wt::WString sms;

    
    //we check if there is a key and get it if it's the case to put in the sms
//    if (!boost::lexical_cast<Wt::WString,boost::optional<Wt::WString> >(alertPtr.get()->alertValue.get()->keyValue).empty())
    if (alertPtr.get()->alertValue.get()->keyValue)
    {
        key = alertPtr.get()->alertValue.get()->keyValue.get();
        ToolsEngine::log("info") << " [Class:AlertSender] " << "New SMS for "<< phoneNumber << " : "
                                 << "New alert on " <<  assetConcerned
                                 << " about : " << alertName
                                 << "for : " << key
                                 << " Received information : " << informationReceived << " " << unit
                                 << " expected : " << alertValue << " " << unit
                                 << " at : " << date
                                 << " tracking id : " << alertTrackingPtr.id();
        sms =  "New alert on " +  assetConcerned
                    + " about : " + alertName
                    + " for : " + key
                    + " Received information : " + informationReceived + " " + unit
                    + " expected : " + alertValue + " " + unit
                    + " at : " + date;
    }
    else //there is no key in the value
    {
        ToolsEngine::log("info") << " [Class:AlertSender] " << "New SMS for "<< phoneNumber << " : "
                                 << "New alert on " <<  assetConcerned
                                 << " about : " << alertName
                                 << " Received information : " << informationReceived << " " << unit
                                 << " expected : " << alertValue << " " << unit
                                 << " at : " << date
                                 << " tracking id : " << alertTrackingPtr.id();
        sms =  "New alert on " +  assetConcerned
                    + " about : " + alertName
                    + " Received information : " + informationReceived + " " + unit
                    + " expected : " + alertValue + " " + unit
                    + " at : " + date;
    }
    
    
//    Session * session = SessionPool::getInstance()->getSession();
    try
    {
//        Transaction transaction(*session);
        // HTTP Client init
        Wt::Http::Client *client = new Wt::Http::Client(*te->ioService);       


        std::string bodyText = "alertid=" + boost::lexical_cast<std::string>(alertPtr.id()) + "&alerttrackingid=" + boost::lexical_cast<std::string>(alertTrackingPtr.id()) + "&messageText=" + sms.toUTF8() + "&number=" + phoneNumber.toUTF8() + "&login=contact@echoes-tech.com&password=147258369aA";


        ToolsEngine::log("info") << " [Class:AlertSender] " << bodyText;

        /** Message containing the http parameters and the body of the post request */
        Wt::Http::Message message;
        message.addBodyText(bodyText);
        message.setHeader("Content-Type", "application/x-www-form-urlencoded");

        std::string apiAddress = te->apiUrl;
        ToolsEngine::log("info") << " [Class:AlertSender] " << "[SMS] Trying to send request to API. Address : " << apiAddress;
        client->post(apiAddress, message);


        //SQL transaction to commit the date

//        Wt::Dbo::ptr<AlertMediaSpecialization> amsP = session->find<AlertMediaSpecialization>().where("\"AMS_ID\" = ? FOR UPDATE").bind(amsPtr.id()).limit(1);
        std::string qryString = "SELECT ams FROM \"T_ALERT_MEDIA_SPECIALIZATION_AMS\" ams WHERE \"AMS_ID\" = ? FOR UPDATE";
        Wt::Dbo::ptr<AlertMediaSpecialization> amsP = session->query<Wt::Dbo::ptr<AlertMediaSpecialization> >(qryString).bind(amsPtr.id());
//        Wt::Dbo::ptr<AlertMediaSpecialization> amsP = session->find<AlertMediaSpecialization>().where("\"AMS_ID\" = ?").bind(amsPtr.id()).limit(1);

        ToolsEngine::log("info") << " [Class:AlertSender] " << "insert date of last send in db : " << now.toString();
        amsP.modify()->lastSend = now;
//        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertSender] " << e.what(); 
    }
//    SessionPool::getInstance()->returnSession(session);
    
}

int AlertSender::sendMAIL(Session * session, Wt::Dbo::ptr<InformationValue> informationValuePtr, Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr, Wt::Dbo::ptr<AlertMediaSpecialization> amsPtr, int overSMSQuota)
{
    Wt::WString mailRecipient; 
    const Wt::WString mailRecipientName = amsPtr.get()->mediaValue.get()->user.get()->firstName + " " + amsPtr.get()->mediaValue.get()->user.get()->lastName ;
    const Wt::WString mailSender = "alert@echoes-tech.com";
    Wt::WString mailSenderName = "ECHOES Alert";
    Wt::WString assetConcerned = informationValuePtr.get()->asset.get()->name;
    Wt::WString alertName = alertPtr.get()->name;
    Wt::WString informationReceived = informationValuePtr.get()->value;
    Wt::WString unit = alertPtr.get()->alertValue.get()->information.get()->pk.unit.get()->name;
    Wt::WString criteria = alertPtr->alertValue->alertCriteria->name;
    Wt::WString alertValue = alertPtr.get()->alertValue.get()->value;
    Wt::WString date = informationValuePtr.get()->creationDate.toString();
    Wt::WDateTime now = Wt::WDateTime::currentDateTime(); //for setting the send date of the alert
    Wt::WString key = alertPtr->alertValue->keyValue.get();
    Wt::WString mail;
    Wt::Mail::Message mailMessage;
    Wt::Mail::Client mailClient;
    
    

    //normal case
    if (overSMSQuota == 0)
    {
        mailRecipient = amsPtr.get()->mediaValue.get()->value;
        //we check if there is a key and get it if it's the case to put in the sms
        if (alertPtr.get()->alertValue.get()->keyValue)
        {
            key = alertPtr.get()->alertValue.get()->keyValue.get();
        }
        else //there is no key in the value
        {
            key = Wt::WString::Empty;
        }
        Wt::WString mailBody = mailFormater(assetConcerned, alertName, key, informationReceived, unit, alertValue, criteria, date, false);
        ToolsEngine::log("info") << " [Class:AlertSender] " << mailBody;
        mail = mailBody;
    }
    else if (overSMSQuota == 1)
    {
        mailRecipient = amsPtr.get()->mediaValue.get()->user.get()->eMail;
        //we check if there is a key and get it if it's the case to put in the sms
        if (alertPtr.get()->alertValue.get()->keyValue)
        {
            key = alertPtr.get()->alertValue.get()->keyValue.get();
        }
        else //there is no key in the value
        {
            key = Wt::WString::Empty;
        }
        Wt::WString mailBody = mailFormater(assetConcerned, alertName, key, informationReceived, unit, alertValue, criteria, date, true);
        ToolsEngine::log("info") << " [Class:AlertSender] " << mailBody;
        mail = mailBody;
    }
    const Wt::WString constMailRecipient = mailRecipient;
    mailMessage.setFrom(Wt::Mail::Mailbox(mailSender.toUTF8(), mailSenderName));
    mailMessage.addRecipient(Wt::Mail::To, Wt::Mail::Mailbox(constMailRecipient.toUTF8(), mailRecipientName));
    mailMessage.setSubject("[ECHOES Alert] " + alertName);
    mailMessage.addHtmlBody(mail);
    mailClient.connect("hermes.gayuxweb.fr");
    mailClient.send(mailMessage);

//    Session * session = SessionPool::getInstance()->getSession();
//    try
//    {
//        Wt::Dbo::ptr<AlertMediaSpecialization> amsP = session->find<AlertMediaSpecialization>().where("\"AMS_ID\" = ? FOR UPDATE").bind(amsPtr.id()).limit(1);
        Wt::Dbo::ptr<AlertMediaSpecialization> amsP = session->find<AlertMediaSpecialization>().where("\"AMS_ID\" = ?").bind(amsPtr.id()).limit(1);
        ToolsEngine::log("info") << " [Class:AlertSender] " << "insert date of last send in db : " << now.toString();
        amsP.modify()->lastSend = now;
        
        alertTrackingPtr.modify()->sendDate = now;
//    }
//    catch (Wt::Dbo::Exception e)
//    {
//        ToolsEngine::log("error") << " [Class:AlertSender] " << e.what();
//    }
//    SessionPool::getInstance()->returnSession(session);
}
 

int AlertSender::send(Session * session, long long idAlert, Wt::Dbo::ptr<InformationValue> InformationValuePtr )
{
    ToolsEngine::log("debug") << " [Class:AlertSender] " << "Entering send";
    int smsQuota;
    long long idOrg;
    
   
//    try
//    {

        //dates used for the snooze
        Wt::WDateTime now = Wt::WDateTime::currentDateTime();
        ToolsEngine::log("debug") << " [Class:AlertSender] " << "now : " << now.toString();

        //because we have to re read the alert last send date that was just modified, if not we will read the first one commited at the first time alert send.
        // TODO : check wether an alert is selected (avoid null pointer)
        Wt::Dbo::ptr<Alert> alertPtr = session->find<Alert>().where("\"ALE_ID\" = ?").bind(idAlert);

        Wt::Dbo::ptr<AlertTracking> alertTrackingPtr;

        //we get the list of media linked to this alert
        Wt::Dbo::collection<Wt::Dbo::ptr<AlertMediaSpecialization> >  amsList = alertPtr.get()->alertMediaSpecializations;
        for (Wt::Dbo::collection<Wt::Dbo::ptr<AlertMediaSpecialization> >::const_iterator j = amsList.begin(); j != amsList.end(); ++j) 
        {


            if (!(*j).get()->lastSend.isValid())//it is the first time we send the alert there is no last send date filled
            {   
                alertTrackingPtr = createAlertTrackingNumber(alertPtr,*j);
                //for each media value for this alert we send the corresponding alert over the air
                ToolsEngine::log("info") << " [Class:AlertSender] " << "Alert tracking number creation : " << alertTrackingPtr.id();
                //TODO : add the feature to modify the media on the alert tracking tuple when the sms quota is 0 ( think to send the mail instead of sms to the appropriate guy instead of the referent user)


                ToolsEngine::log("info") << " [Class:AlertSender] " << "It's the first time we send this alert";
                ToolsEngine::log("debug") << " [Class:AlertSender] " << "snooze = " << j->get()->snoozeDuration;
                switch (j->get()->mediaValue.get()->media.id())
                {
                    case sms:
                    {
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value SMS choosed for the alert : " << alertPtr.get()->name;

                        //we verify the quota of sms
                        idOrg = j->get()->mediaValue.get()->user.get()->currentOrganization.id();

                        try
                        {
    //                        optionValue = session->find<OptionValue>().where("\"OPT_ID_OPT_ID\" = ?").bind(quotasms).where("\"ORG_ID_ORG_ID\" = ? FOR UPDATE").bind(idOrg).limit(1);
                            Wt::Dbo::ptr<OptionValue> optionValue = session->find<OptionValue>().where("\"OPT_ID_OPT_ID\" = ?").bind(quotasms).where("\"ORG_ID_ORG_ID\" = ?").bind(idOrg).limit(1);

                            smsQuota = boost::lexical_cast<int>(optionValue.get()->value); 
                            if ( smsQuota == 0 )   
                            {

                                ToolsEngine::log("info") << " [Class:AlertSender] " << "SMS quota 0 for alert : " <<  alertPtr.get()->name;
                                ToolsEngine::log("info") << " [Class:AlertSender] " << "Sending e-mail instead." ;

                                sendMAIL(session,InformationValuePtr,alertPtr, alertTrackingPtr,(*j),1);
                            }
                            else
                            {
                                ToolsEngine::log("debug") << " [Class:AlertSender] " << "We send a SMS, quota : "<< smsQuota;
                                optionValue.modify()->value = boost::lexical_cast<std::string>((smsQuota - 1));
                                optionValue.flush();                        
                                sendSMS(session,InformationValuePtr,alertPtr, alertTrackingPtr, (*j)); 
                            }
                        }
                        catch (Wt::Dbo::Exception e)
                        {
                            ToolsEngine::log("error") << " [Class:AlertSender] " << e.what();
                        }
                        break;
                    }
                    case mail:
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value MAIL choosed for the alert : " << alertPtr.get()->name;              
                        sendMAIL(session,InformationValuePtr,alertPtr, alertTrackingPtr, (*j));
                        break;
                    default:
                        break;        
                }
            }
            //we do : date.now() - last_send = nb_secs then, if nb_secs >= snooze of the media, we send the alert
            else if ((*j).get()->lastSend.secsTo(now) >= j->get()->snoozeDuration)
            {
                alertTrackingPtr = AlertSender::createAlertTrackingNumber(alertPtr,*j);
                //for each media value for this alert we send the corresponding alert over the air
                ToolsEngine::log("info") << " [Class:AlertSender] " << "Alert tracking number creation : " << alertTrackingPtr.id();

                ToolsEngine::log("debug") << " [Class:AlertSender] " << " last send : " << (*j).get()->lastSend.toString();
                ToolsEngine::log("debug") << " [Class:AlertSender] " << " now : " << now.toString();            
                ToolsEngine::log("debug") << " [Class:AlertSender] " << " last send to now in secs = " << (*j).get()->lastSend.secsTo(now);

                ToolsEngine::log("debug") << " [Class:AlertSender] " << "snooze = " << j->get()->snoozeDuration;
                ToolsEngine::log("debug") << " [Class:AlertSender] " 
                                         << "Last time we send the alert : " << alertPtr.get()->name 
                                         << "was : " << (*j).get()->lastSend.toString()
                                         << "the snooze for the media " << j->get()->mediaValue.get()->media.get()->name 
                                         << " is : " << j->get()->snoozeDuration << "secs so now it's time to send a new time";      
                switch (j->get()->mediaValue.get()->media.id())
                {
                    case sms:
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value SMS choosed for an alert.";

                        //we verify the quota of sms
                        idOrg = j->get()->mediaValue.get()->user.get()->currentOrganization.id();

                        try
                        {
                            Wt::Dbo::ptr<OptionValue> optionValue = session->find<OptionValue>().where("\"OPT_ID_OPT_ID\" = ?").bind(quotasms).where("\"ORG_ID_ORG_ID\" = ?").bind(idOrg).limit(1);

                            smsQuota = boost::lexical_cast<int>(optionValue.get()->value); 
                            if ( smsQuota == 0 )   
                            {
                                ToolsEngine::log("info") << " [Class:AlertSender] " << "SMS quota 0 for alert : " <<  alertPtr.get()->name;
                                ToolsEngine::log("info") << " [Class:AlertSender] " << "Sending e-mail instead." ;
                                sendMAIL(session,InformationValuePtr,alertPtr, alertTrackingPtr, (*j),1);
                            }
                            else
                            {
                                ToolsEngine::log("debug") << " [Class:AlertSender] " << "We send a SMS, quota : "<< smsQuota;
                                optionValue.modify()->value = boost::lexical_cast<std::string>((smsQuota - 1));
                                optionValue.flush();
                                sendSMS(session,InformationValuePtr,alertPtr, alertTrackingPtr, (*j)); 
                            }
                        }
                        catch (Wt::Dbo::Exception e)
                        {
                            ToolsEngine::log("error") << " [Class:AlertSender] " << e.what();
                        }
                        break;
                    case mail:
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value MAIL choosed for the alert : " << alertPtr.get()->name;              
                        sendMAIL(session,InformationValuePtr,alertPtr, alertTrackingPtr, (*j));            
                        break;
                    default:
                        break;        
                }            
            }
            else
            {
                ToolsEngine::log("debug") << " [Class:AlertSender] " 
                                         << "Last time we send the alert : " << alertPtr.get()->name 
                                         << "was : " << (*j).get()->lastSend.toString()
                                         << "the snooze for the media " << j->get()->mediaValue.get()->media.get()->name 
                                         << " is : " << j->get()->snoozeDuration << "secs,  it's not the time to send the alert";  

            }
        }
        amsList.~collection();
        return 0;
//    }
//    catch (Wt::Dbo::Exception e)
//    {
//        ToolsEngine::log("error") << " [Class:AlertSender] " << " - " << "send : " << e.what();;
//    }
}

Wt::WString AlertSender::mailFormater(Wt::WString assetName,Wt::WString alertName,Wt::WString key, Wt::WString informationReceived,Wt::WString unit,Wt::WString alertValue,Wt::WString criteria, Wt::WString date, bool noMoreSMS)
{
    Wt::WString res = "";
    if (noMoreSMS)
    {
        res += "MAIL sent instead of SMS (quota = 0) <br />";
    }
    res += 
        + "Asset name : " +  assetName + "<br />"
        + "Alert name : " + alertName + "<br />";
    
        if (!key.empty())
        {
           res += "Key : " + key + "<br />";
        }
        res += "Received value : " + informationReceived + " " + unit + "<br />"
        + "Criteria : " + criteria + "<br />"
        + "Expected value : " + alertValue + " " + unit + "<br />"
        + "Time : " + date + "<br />"
        + "Check it on https://alert.echoes-tech.com";
    
    return res;
}