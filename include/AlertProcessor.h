/** 
 * 
 * This class process the different received value with the existing alerts and start the workflow when the 
 * threshold occurs
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-08-07
 */

#ifndef ALERTPROCESSOR_H
#define	ALERTPROCESSOR_H

#include <tools/Session.h>
#include <string>
#include <queue>
#include <iostream>
#include <Wt/Dbo/Dbo>
#include <Wt/WDateTime>
#include "ToolsEngine.h"
#include <information/InformationValue.h>
#include <information/Information.h>
#include <alert/Alert.h>
#include <alert/AlertValue.h>
#include <alert/AlertType.h>
#include <alert/AlertCriteria.h>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <tools/Session.h>
#include <boost/lexical_cast.hpp>
#include "AlertSender.h"


class AlertProcessor {
public:
    /**
     * class' builder
     */
    AlertProcessor();
    virtual ~AlertProcessor();
    
   /**
    * method that create a thread for each alert resgistered in the database
    * @return error or success
    */
    int VerifyAlerts();  
    
    
   /**
    * method to evaluate the InformationValue table with one alert
    * @param the pointer of the alert
    * @return code for the parent thread
    */ 
    void InformationValueLoop(Wt::Dbo::ptr<Alert> alertPtr);
    

    
private:
    boost::mutex mutex;
    
    enum criteria{lt = 1,le = 2,eq = 3,ne = 4,ge = 5,gt = 6};
    
    enum informationUnitType{number = 1,text = 2};
       
};

#endif	/* ALERTPROCESSOR_H */

