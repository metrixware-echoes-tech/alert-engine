#include "AlertSender.h"

AlertSender::AlertSender() {
}

AlertSender::~AlertSender() {
}

MediaValueList AlertSender::checkMediaToSendAlert(Wt::Dbo::ptr<Alert> alertPtr)
{
    MediaValueList mvList = alertPtr.get()->mediaValues;
    
    return mvList;
}

Wt::Dbo::ptr<AlertTracking> AlertSender::createAlertTrackingNumber(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<MediaValue> mediaValuePtr, Session *session)
{
    //we get the session actually opened
    AlertTracking *newAlertTracking = new AlertTracking();
    Wt::WDateTime *now = new Wt::WDateTime();
    
    newAlertTracking->alert = alertPtr;
    newAlertTracking->mediaValue = mediaValuePtr;
    now->currentDateTime();
    newAlertTracking->sendDate = *now;
    Wt::Dbo::ptr<AlertTracking> alertTrackingPtr;
    
    try
    {         
        alertTrackingPtr = session->add<AlertTracking>(newAlertTracking);
        alertTrackingPtr.flush();
        
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertSender] " << e.what() ;
    }
    return alertTrackingPtr;
}

int AlertSender::sendSMS(Wt::Dbo::ptr<InformationValue> informationValuePtr, Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr, Wt::Dbo::ptr<MediaValue> mediaValuePtr)
{
    Wt::WString phoneNumber = mediaValuePtr.get()->value;
    Wt::WString assetConcerned = informationValuePtr.get()->asset.get()->name;
    Wt::WString alertName = alertPtr.get()->name;
    Wt::WString informationReceived = informationValuePtr.get()->value;
    Wt::WString unit = alertPtr.get()->alertValue.get()->information.get()->unit.get()->name;
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
    
    

    // HTTP Client init
    Wt::Http::Client *client = new Wt::Http::Client(*te->ioService);       


    std::string bodyText = "alertid=" + boost::lexical_cast<std::string>(alertPtr.id()) + "&alerttrackingid=" + boost::lexical_cast<std::string>(alertTrackingPtr.id()) + "&messageText=" + sms.toUTF8() + "&number=" + phoneNumber.toUTF8() + "&login=contact@echoes-tech.com&password=147258369aA";


    ToolsEngine::log("info") << " [Class:AlertSender] " << bodyText;

    /** Message containing the http parameters and the body of the post request */
    Wt::Http::Message message;
    message.addBodyText(bodyText);
    message.setHeader("Content-Type", "application/x-www-form-urlencoded");

    std::string apiAddress = "https://sms/netsize/send";
    ToolsEngine::log("info") << " [Class:AlertSender] " << "[SMS] Trying to send request to API. Address : " << apiAddress;
    //client->post(apiAddress, message);
    
    
    //SQL transaction to commit the date
    Session *session = static_cast<Session*>(informationValuePtr.session());
        
    Wt::Dbo::ptr<MediaValue> mediaValueP = session->find<MediaValue>().where("\"MEV_ID\" = ?").bind(mediaValuePtr.id());

    ToolsEngine::log("info") << " [Class:AlertSender] " << "insert date of last send in db : " << now.toString();
    mediaValueP.modify()->lastSend = now;
    
}

int AlertSender::sendMAIL(Wt::Dbo::ptr<InformationValue> informationValuePtr, Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr, Wt::Dbo::ptr<MediaValue> mediaValuePtr, int overSMSQuota)
{
    Wt::WString mailRecipient; 
    const Wt::WString mailRecipientName = mediaValuePtr.get()->user.get()->firstName + " " + mediaValuePtr.get()->user.get()->lastName ;
    const Wt::WString mailSender = "alert@echoes-tech.com";
    Wt::WString mailSenderName = "ECHOES Alert";
    Wt::WString assetConcerned = informationValuePtr.get()->asset.get()->name;
    Wt::WString alertName = alertPtr.get()->name;
    Wt::WString informationReceived = informationValuePtr.get()->value;
    Wt::WString unit = alertPtr.get()->alertValue.get()->information.get()->unit.get()->name;
    Wt::WString alertValue = alertPtr.get()->alertValue.get()->value;
    Wt::WString date = informationValuePtr.get()->creationDate.toString();
    Wt::WDateTime now = Wt::WDateTime::currentDateTime(); //for setting the send date of the alert
    Wt::WString key;
    Wt::WString mail;
    Wt::Mail::Message mailMessage;
    Wt::Mail::Client mailClient;
    
    //SQL transaction
    Session *session = static_cast<Session*>(informationValuePtr.session());
 

    //normal case
    if (overSMSQuota == 0)
    {
        mailRecipient = mediaValuePtr.get()->value;

        //we check if there is a key and get it if it's the case to put in the sms
        if (alertPtr.get()->alertValue.get()->keyValue)
        {
            key = alertPtr.get()->alertValue.get()->keyValue.get();
            ToolsEngine::log("info") << " [Class:AlertSender] " << "New MAIL for "<< mailRecipient << " : "
                                    << "New alert on " <<  assetConcerned
                                    << " about : " << alertName
                                    << "for : " << key
                                    << " Received information : " << informationReceived << " " << unit
                                    << " expected : " << alertValue << " " << unit
                                    << " at : " << date
                                    << " tracking id : " << alertTrackingPtr.id();
            mail =  "New alert on " +  assetConcerned
                        + " about : " + alertName
                        + " for : " + key
                        + " Received information : " + informationReceived + " " + unit
                        + " expected : " + alertValue + " " + unit
                        + " at : " + date
                        + " check it on https://alert.echoes-tech.com";
        }
        else //there is no key in the value
        {
            ToolsEngine::log("info") << " [Class:AlertSender] " << "New MAIL for "<< mailRecipient << " : "
                                    << "New alert on " <<  assetConcerned
                                    << " about : " << alertName
                                    << " Received information : " << informationReceived << " " << unit
                                    << " expected : " << alertValue << " " << unit
                                    << " at : " << date
                                    << " tracking id : " << alertTrackingPtr.id();
            mail =  "New alert on " +  assetConcerned
                        + " about : " + alertName
                        + " Received information : " + informationReceived + " " + unit
                        + " expected : " + alertValue + " " + unit
                        + " at : " + date
                        + " check it on https://alert.echoes-tech.com";
        }
    }
    else if (overSMSQuota == 1)
    {
        mailRecipient = mediaValuePtr.get()->user.get()->eMail;
        //we check if there is a key and get it if it's the case to put in the sms
        if (alertPtr.get()->alertValue.get()->keyValue)
        {
            key = alertPtr.get()->alertValue.get()->keyValue.get();
            ToolsEngine::log("info") << " [Class:AlertSender] " << "New MAIL instead of SMS (quota reached) for "<< mailRecipient << " : "
                                    << "New alert on " <<  assetConcerned
                                    << " about : " << alertName
                                    << "for : " << key
                                    << " Received information : " << informationReceived << " " << unit
                                    << " expected : " << alertValue << " " << unit
                                    << " at : " << date
                                    << " tracking id : " << alertTrackingPtr.id();
            mail =  "New Alert instead of SMS (quota reached) for " +  assetConcerned
                        + " about : " + alertName
                        + " for : " + key
                        + " Received information : " + informationReceived + " " + unit
                        + " expected : " + alertValue + " " + unit
                        + " at : " + date;
        }
        else //there is no key in the value
        {
            ToolsEngine::log("info") << " [Class:AlertSender] " << "New MAIL instead of SMS (quota reached) for "<< mailRecipient << " : "
                                    << "New alert on " <<  assetConcerned
                                    << " about : " << alertName
                                    << " Received information : " << informationReceived << " " << unit
                                    << " expected : " << alertValue << " " << unit
                                    << " at : " << date
                                    << " tracking id : " << alertTrackingPtr.id();
            mail =  "New Alert instead of SMS (quota reached) for " +  assetConcerned
                        + " about : " + alertName
                        + " Received information : " + informationReceived + " " + unit
                        + " expected : " + alertValue + " " + unit
                        + " at : " + date
                        + " check it on https://alert.echoes-tech.com";
        }
    }
    const Wt::WString constMailRecipient = mailRecipient;
    mailMessage.setFrom(Wt::Mail::Mailbox(mailSender.toUTF8(), mailSenderName));
    mailMessage.addRecipient(Wt::Mail::To, Wt::Mail::Mailbox(constMailRecipient.toUTF8(), mailRecipientName));
    mailMessage.setSubject("You have a new alert");
    mailMessage.addHtmlBody(mail);
    mailClient.connect("hermes.gayuxweb.fr");
    mailClient.send(mailMessage);
    
    
    Wt::Dbo::ptr<MediaValue> mediaValueP = session->find<MediaValue>().where("\"MEV_ID\" = ?").bind(mediaValuePtr.id());

    ToolsEngine::log("info") << " [Class:AlertSender] " << "insert date of last send in db : " << now.toString();
    mediaValueP.modify()->lastSend = now;
}
 

int AlertSender::send(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<InformationValue> InformationValuePtr )
{
    Session *session = static_cast<Session*>(InformationValuePtr.session());
    int smsQuota;
    long long idOrg;
    Wt::Dbo::ptr<OptionValue> optionValue;
    
    //dates used for the snooze
    Wt::WDateTime now = Wt::WDateTime::currentDateTime();
    ToolsEngine::log("info") << " [Class:AlertSender] " << "now : " << now.toString();
    
    //because we have to re read the alert last send date that was just modified, if not we will read the first one commited at the first time alert send.
    alertPtr.reread();
    

    
    //we get the list of media linked to this alert
    MediaValueList mediaList = AlertSender::checkMediaToSendAlert(alertPtr);
    for (MediaValueList::const_iterator j = mediaList.begin(); j != mediaList.end(); ++j) 
    {
        Wt::Dbo::ptr<AlertTracking> alertTrackingPtr = AlertSender::createAlertTrackingNumber(alertPtr,*j, session);
        //for each media value for this alert we send the corresponding alert over the air


        
        if (!(*j).get()->lastSend.isValid())//it is the first time we send the alert there is no last send date filled
        {
            ToolsEngine::log("info") << " [Class:AlertSender] " << "It's the first time we send this alert";
            ToolsEngine::log("info") << " [Class:AlertSender] " << "snooze = " << j->get()->snoozeDuration;
            switch (j->get()->media.id())
            {
                case sms:
                {
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value SMS choosed for the alert : " << alertPtr.get()->name;
                    
                    //we verify the quota of sms
                    idOrg = j->get()->user.get()->currentOrganization.id();
                    
                    optionValue = session->find<OptionValue>().where("\"OPT_ID_OPT_ID\" = ?").bind(quotasms).where("\"ORG_ID_ORG_ID\" = ?").bind(idOrg);
                    
                    smsQuota = boost::lexical_cast<int>(optionValue.get()->value); 
                    if ( smsQuota == 0 )   
                    {
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "SMS quota 0 for alert : " <<  alertPtr.get()->name;
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "Sending e-mail instead." ;
                        
                        AlertSender::sendMAIL(InformationValuePtr,alertPtr, alertTrackingPtr,(*j),1);
                    }
                    else
                    {
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "We send a SMS, quota : "<< smsQuota;
                        optionValue.modify()->value = boost::lexical_cast<std::string>((smsQuota - 1));
                        optionValue.flush();                        
                        AlertSender::sendSMS(InformationValuePtr,alertPtr, alertTrackingPtr, (*j)); 
                    }
                    break;
                }
                case mail:
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value MAIL choosed for the alert : " << alertPtr.get()->name;              
                    AlertSender::sendMAIL(InformationValuePtr,alertPtr, alertTrackingPtr, (*j));
                    break;
                default:
                    break;        
            }
        }
        //we do : date.now() - last_send = nb_secs then, if nb_secs >= snooze of the media, we send the alert
        else if ((*j).get()->lastSend.secsTo(now) >= j->get()->snoozeDuration)
        {
            ToolsEngine::log("info") << " [Class:AlertSender] " << " last send : " << (*j).get()->lastSend.toString();
            ToolsEngine::log("info") << " [Class:AlertSender] " << " now : " << now.toString();            
            ToolsEngine::log("info") << " [Class:AlertSender] " << " last send to now in secs = " << (*j).get()->lastSend.secsTo(now);
            
            ToolsEngine::log("info") << " [Class:AlertSender] " << "snooze = " << j->get()->snoozeDuration;
            ToolsEngine::log("info") << " [Class:AlertSender] " 
                                     << "Last time we send the alert : " << alertPtr.get()->name 
                                     << "was : " << (*j).get()->lastSend.toString()
                                     << "the snooze for the media " << j->get()->media.get()->name 
                                     << " is : " << j->get()->snoozeDuration << "secs so now it's time to send a new time";      
            switch (j->get()->media.id())
            {
                case sms:
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value SMS choosed for an alert.";
                    
                    //we verify the quota of sms
                    idOrg = j->get()->user.get()->currentOrganization.id();
                    
                    optionValue = session->find<OptionValue>().where("\"OPT_ID_OPT_ID\" = ?").bind(quotasms).where("\"ORG_ID_ORG_ID\" = ?").bind(idOrg);
                    
                    smsQuota = boost::lexical_cast<int>(optionValue.get()->value); 
                    if ( smsQuota == 0 )   
                    {
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "SMS quota 0 for alert : " <<  alertPtr.get()->name;
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "Sending e-mail instead." ;
                        AlertSender::sendMAIL(InformationValuePtr,alertPtr, alertTrackingPtr, (*j),1);
                    }
                    else
                    {
                        ToolsEngine::log("info") << " [Class:AlertSender] " << "We send a SMS, quota : "<< smsQuota;
                        optionValue.modify()->value = boost::lexical_cast<std::string>((smsQuota - 1));
                        optionValue.flush();
                        AlertSender::sendSMS(InformationValuePtr,alertPtr, alertTrackingPtr, (*j)); 
                    }
                    break;
                case mail:
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value MAIL choosed for the alert : " << alertPtr.get()->name;              
                    AlertSender::sendMAIL(InformationValuePtr,alertPtr, alertTrackingPtr, (*j));            
                    break;
                default:
                    break;        
            }            
        }
        else{
            ToolsEngine::log("info") << " [Class:AlertSender] " 
                                     << "Last time we send the alert : " << alertPtr.get()->name 
                                     << "was : " << (*j).get()->lastSend.toString()
                                     << "the snooze for the media " << j->get()->media.get()->name 
                                     << " is : " << j->get()->snoozeDuration << "secs,  it's not the time to send the alert";  
 
        }
    }
}