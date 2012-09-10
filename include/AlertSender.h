/** 
 * 
 * This class send the alerts to the differents medias registered by the customer
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-08-29
 */

#ifndef ALERTSENDER_H
#define	ALERTSENDER_H

#include <tools/Session.h>
#include <string>
#include <Wt/Dbo/Dbo>
#include <Wt/WDateTime>
#include "ToolsEngine.h"
#include <alert/Alert.h>
#include <media/MediaValue.h>
#include <media/Media.h>
#include <alert/AlertTracking.h>
#include <pack/Option.h>
#include <Wt/Http/Client>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include <Wt/WObject>
#include <Wt/Mail/Client>
#include <Wt/Mail/Message>

typedef Wt::Dbo::collection< Wt::Dbo::ptr<MediaValue> > MediaValueList;

class AlertSender {
public:
    /**
     * class' builder
     */    
    AlertSender();
    virtual ~AlertSender();
    
   /**
    * method to get the media linked to an alert
    * @param the alert that we want to kow the media linked
    * @return the list of the medias 
    */ 
    MediaValueList checkMediaToSendAlert(Wt::Dbo::ptr<Alert> alertPtr);
    
   /**
    * method to create a new alert tracking number
    * @param the alert 
    * @param the media value used to create the alert tracking
    * @return the pointer on the created object
    */ 
    Wt::Dbo::ptr<AlertTracking> createAlertTrackingNumber(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<MediaValue> mediaValuePtr, Session *session);

   /**
    * method to send an SMS with the call of the API
    * @param the information value that matches the alert
    * @param the alert
    * @param the alert tracking required and concerned by the sms
    * @param the media value concern by the alert
    * @return error -1 or sucess 0
    */     
    int sendSMS(Wt::Dbo::ptr<InformationValue> InformationValuePtr,Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr, Wt::Dbo::ptr<MediaValue> mediaValuePtr);

   /**
    * method to send a MAIL 
    * @param the information value that matches the alert
    * @param the alert
    * @param the alert tracking required and concerned by the sms
    * @param the media value concern by the alert
    * @param if the user as use all his sms, the value here is 1 if not it's 0
    * @return error -1 or sucess 0
    */    
    int sendMAIL(Wt::Dbo::ptr<InformationValue> InformationValuePtr, Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<AlertTracking> alertTrackingPtr, Wt::Dbo::ptr<MediaValue> mediaValuePtr, int overSMSQuota = 0);
   /**
    * method to send the differents alerts over the air (mail, sms....) linked to an alert
    * @param the alert
    * @param the information value that matches the alert
    * @return error -1 or sucess 0
    */ 
    int send(Wt::Dbo::ptr<Alert> alertPtr, Wt::Dbo::ptr<InformationValue> InformationValuePtr );

private:
    enum mediaTypes{sms = 0,mail = 1};

};

#endif	/* ALERTSENDER_H */

