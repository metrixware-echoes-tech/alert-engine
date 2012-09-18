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
#include <media/MediaValue.h>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <tools/Session.h>
#include <boost/lexical_cast.hpp>
#include "AlertSender.h"

typedef Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > tbInformationValue;

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
    * @param the id of the alert
    * @return code for the parent thread
    */ 
    void InformationValueLoop(long long idAlert);
    
    /**
    * method compare a numerical value with an alert value and a mathematics operator
    * @param the table of informationvalue received and ready to be checked
    * @param the operator method
    * @param the value to compare with (set in the alert value)
    * @param the ptr of the current alert
    * @param optionnal, the line number if we have a value linked to a key transmitted
    * @return void
    */ 
    int comparingNumberValue(tbInformationValue valuesToCheck,bool (*mathOperator)(double,double), double valueSetInDb, Wt::Dbo::ptr<Alert> alertPtr, int lineNumber=0);

    /**
    * method to compute the value of the alerts, implentation of the mathematics operators
    * @param first number to compare
    * @param second number to compare
    * @return true or false
    */ 
 //   bool ltMethod(double a, double b);
    bool leMethod(double a, double b);
    bool eqMethod(double a, double b);
    bool neMethod(double a, double b);
 //   bool geMethod(double a, double b);
    bool gtMethod(double a, double b);

    
private:
    boost::mutex mutex;
    
    enum criteria{lt = 1,le = 2,eq = 3,ne = 4,ge = 5,gt = 6};
    
    enum informationUnitType{number = 2,text = 1};
       
};

#endif	/* ALERTPROCESSOR_H */

