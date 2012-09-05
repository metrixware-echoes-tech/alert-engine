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
//        alertPtr.modify()->name = "prout"; //vérification taille mémoire
        alertTrackingPtr.flush();
        std::cout << "ptr id : " << alertTrackingPtr.id() << "\n";
        
    }
    catch (Wt::Dbo::Exception e)
    {
        ToolsEngine::log("error") << " [Class:AlertSender] " << e.what() ;
    }
    return alertTrackingPtr;
}

int AlertSender::sendSMS(Wt::Dbo::ptr<InformationValue> InformationValuePtr, Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr)
{
    std::cout << "ptr id : " << alertTrackingPtr.id() << "\n";
    Wt::WString phoneNumber = alertTrackingPtr.get()->mediaValue.get()->value;
    Wt::WString assetConcerned = InformationValuePtr.get()->asset.get()->name;
    Wt::WString alertName = alertPtr.get()->name;
    Wt::WString informationReceived = InformationValuePtr.get()->value;
    Wt::WString unit = alertPtr.get()->alertValue.get()->information.get()->unit.get()->name;
    Wt::WString alertValue = alertPtr.get()->alertValue.get()->value;
    Wt::WString date = alertTrackingPtr.get()->sendDate.toString();
    
    ToolsEngine::log("info") << " [Class:AlertSender] " << "New SMS pour "<< phoneNumber << " : "
            << "Nouvelle alerte sur :" <<  assetConcerned
            << " concernant : " << alertName
            << " relevé : " << informationReceived << " " << unit
            << " prévu : " << alertValue << " " << unit
            << " à : " << date;
    Wt::WString sms =  "Nouvelle alerte sur :" +  assetConcerned
                    + " concernant : " + alertName
                    + " relevé : " + informationReceived + " " + unit
                    + " prévu : " + alertValue + " " + unit
                    + " à : " + date;

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
   // client->post(apiAddress, message); 
//    exit(0);
}

int AlertSender::send(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<InformationValue> InformationValuePtr )
{
    Session *session = static_cast<Session*>(InformationValuePtr.session());
    //we get the list of media linked to this alert
    MediaValueList mediaList = AlertSender::checkMediaToSendAlert(alertPtr);
    for (MediaValueList::const_iterator j = mediaList.begin(); j != mediaList.end(); ++j) 
    {
        Wt::Dbo::ptr<AlertTracking> alertTrackingPtr = AlertSender::createAlertTrackingNumber(alertPtr,*j, session);
        std::cout << "ptr id : " << alertTrackingPtr.id() << "\n";
        //for each media value for this alert we send the corresponding alert over the air
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
}