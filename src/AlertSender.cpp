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

Wt::Dbo::ptr<AlertTracking> AlertSender::createAlertTrackingNumber(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<MediaValue> mediaValuePtr)
{
    //we get the session actually opened
    Session *session = static_cast<Session*>(alertPtr.session());
    AlertTracking *newAlertTracking = new AlertTracking();
    Wt::WDateTime *now = new Wt::WDateTime();
    
    newAlertTracking->alert = alertPtr;
    newAlertTracking->mediaValue = mediaValuePtr;
    now->currentDateTime();
    newAlertTracking->sendDate = *now;
    Wt::Dbo::ptr<AlertTracking> alertTrackingPtr;
    try
    {         
        alertTrackingPtr = session->add(newAlertTracking);
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
    
    ToolsEngine::log("info") << " [Class:AlertSender] " << "New SMS pour "<< phoneNumber << " : "
            << "Nouvelle alerte sur :" <<  assetConcerned
            << " concernant : " << alertName
            << " relevé : " << informationReceived << " " << unit
            << " prévu : " << alertValue << " " << unit
            << " à : " << date;     
}

int AlertSender::send(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<InformationValue> InformationValuePtr )
{
    
    //we get the list of media linked to this alert
    MediaValueList mediaList = AlertSender::checkMediaToSendAlert(alertPtr);
    for (MediaValueList::const_iterator j = mediaList.begin(); j != mediaList.end(); ++j) 
    {
        Wt::Dbo::ptr<AlertTracking> alertTrackingPtr = AlertSender::createAlertTrackingNumber(alertPtr,*j);
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