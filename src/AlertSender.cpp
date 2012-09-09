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

int AlertSender::sendSMS(Wt::Dbo::ptr<InformationValue> InformationValuePtr, Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr)
{
    Wt::WString phoneNumber = alertTrackingPtr.get()->mediaValue.get()->value;
    Wt::WString assetConcerned = InformationValuePtr.get()->asset.get()->name;
    Wt::WString alertName = alertPtr.get()->name;
    Wt::WString informationReceived = InformationValuePtr.get()->value;
    Wt::WString unit = alertPtr.get()->alertValue.get()->information.get()->unit.get()->name;
    Wt::WString alertValue = alertPtr.get()->alertValue.get()->value;
    Wt::WString date = alertTrackingPtr.get()->sendDate.toString();
    Wt::WDateTime now = Wt::WDateTime::currentDateTime(); //for setting the send date of the alert
    Wt::WString key;
    Wt::WString sms;
    
    //we check if there is a key and get it if it's the case to put in the sms
    if (!alertPtr.get()->alertValue.get()->keyValue.empty())
    {
        key = alertPtr.get()->alertValue.get()->keyValue;
        
        ToolsEngine::log("info") << " [Class:AlertSender] " << "New SMS pour "<< phoneNumber << " : "
                                 << "Nouvelle alerte sur :" <<  assetConcerned
                                 << " concernant : " << alertName
                                 << "clef :" << key
                                 << " relevé : " << informationReceived << " " << unit
                                 << " prévu : " << alertValue << " " << unit
                                 << " à : " << date
                                 << " tracking id : " << alertTrackingPtr.id();
        sms =  "Nouvelle alerte sur :" +  assetConcerned
                    + " concernant : " + alertName
                    + " clef : " + key
                    + " relevé : " + informationReceived + " " + unit
                    + " prévu : " + alertValue + " " + unit
                    + " à : " + date;
    }
    else //there is no key in the value
    {
        ToolsEngine::log("info") << " [Class:AlertSender] " << "New SMS pour "<< phoneNumber << " : "
                                 << "Nouvelle alerte sur :" <<  assetConcerned
                                 << " concernant : " << alertName
                                 << " relevé : " << informationReceived << " " << unit
                                 << " prévu : " << alertValue << " " << unit
                                 << " à : " << date
                                 << " tracking id : " << alertTrackingPtr.id();                
        sms =  "Nouvelle alerte sur :" +  assetConcerned
                    + " concernant : " + alertName
                    + " relevé : " + informationReceived + " " + unit
                    + " prévu : " + alertValue + " " + unit
                    + " à : " + date;
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
    Session *session = static_cast<Session*>(InformationValuePtr.session());
    
      //  Wt::Dbo::Transaction transaction(*session);
        
    Wt::Dbo::ptr<Alert> alertP = session->find<Alert>().where("\"ALE_ID\" = ?").bind(alertPtr.id());

    ToolsEngine::log("info") << " [Class:AlertSender] " << "insert date of last send in db : " << now.toString();
    alertP.modify()->lastSend = now;
    
}

int AlertSender::send(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<InformationValue> InformationValuePtr )
{
    Session *session = static_cast<Session*>(InformationValuePtr.session());
    
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


        
        if (!alertPtr.get()->lastSend.isValid())//it is the first time we send the alert there is no last send date filled
        {
            ToolsEngine::log("info") << " [Class:AlertSender] " << "It's the first time we send this alert";
            ToolsEngine::log("info") << " [Class:AlertSender] " << "snooze = " << j->get()->snoozeDuration;
            switch (j->get()->media.id())
            {
                case sms:
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value SMS choosed for the alert : " << alertPtr.get()->name;
                    AlertSender::sendSMS(InformationValuePtr,alertPtr, alertTrackingPtr); 
                    break;
                case mail:
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value MAIL not yet implemented.";              
                    break;
                default:
                    break;        
            }
        }
        //we do : date.now() - last_send = nb_secs then, if nb_secs >= snooze of the media, we send the alert
        else if (alertPtr.get()->lastSend.secsTo(now) >= j->get()->snoozeDuration)
        {
            ToolsEngine::log("info") << " [Class:AlertSender] " << " last send - now = " << alertPtr.get()->lastSend.secsTo(now);
            ToolsEngine::log("info") << " [Class:AlertSender] " << "snooze = " << j->get()->snoozeDuration;
            ToolsEngine::log("info") << " [Class:AlertSender] " 
                                     << "Last time we send the alert : " << alertPtr.get()->name 
                                     << "was : " << alertPtr.get()->lastSend.toString()
                                     << "the snooze for the media " << j->get()->media.get()->name 
                                     << " is : " << j->get()->snoozeDuration << "secs so now it's time to send a new time";      
            switch (j->get()->media.id())
            {
                case sms:
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value SMS choosed for an alert.";
                    AlertSender::sendSMS(InformationValuePtr,alertPtr, alertTrackingPtr); 
                    break;
                case mail:
                    ToolsEngine::log("info") << " [Class:AlertSender] " << "Media value MAIL not yet implemented.";              
                    break;
                default:
                    break;        
            }            
        }
        else{
            ToolsEngine::log("info") << " [Class:AlertSender] " 
                                     << "Last time we send the alert : " << alertPtr.get()->name 
                                     << "was : " << alertPtr.get()->lastSend.toString()
                                     << "the snooze for the media " << j->get()->media.get()->name 
                                     << " is : " << j->get()->snoozeDuration << "secs,  it's not the time to send the alert";  
 
        }
    }
}