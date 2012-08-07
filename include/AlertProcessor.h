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
#include <pthread.h>
#include <vector>



class AlertProcessor {
public:
    /**
     * class' builder
     */
    AlertProcessor();
    virtual ~AlertProcessor();
    
   /**
    * method to 
    * @return error or success
    */
    int VerifyAlerts();
    
    
   /**
    * method to evaluate the InformationValue table with one alert
    * @param the pointer of the alert
    * @return code for the parent thread
    */ 
    void* InformationValueLoop(void* arg);
    
private:
       
};

#endif	/* ALERTPROCESSOR_H */

