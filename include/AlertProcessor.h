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
#include <vector>
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
#include <tools/SessionPool.h>
#include <boost/lexical_cast.hpp>
#include "AlertSender.h"

typedef Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > tbInformationValue;

typedef std::map<long long, bool*> alertBooleansMap;
typedef std::map<long long, alertBooleansMap*> ivaAlertsMap;

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
    int verifyAlerts();  
    
    
    void launchUpdateDataThread();
    void launchIvaThread();
    void launchAlertThread();
    void launchCleanThread();
    
    //update data thread
    bool updateData();
    bool setAlerts();
    bool setInfos();
    bool setAlertsByInfo();
    
    //collect iva thread
    void collectIva();
    
    //alert preparation thread
    void prepareAlertComputing();
    void prepareAlertComputingFromId(long long alertId);
    
    // alert computing
    void computeAlerts();
    void computeAlertFromId(long long alertId);

    //clean thread
    void cleanMaps();
    
    bool createIvaMaps();
    bool launchCalculationThreadForEachGroup();
    bool sendAlerts();
    
    
   /**
    * method to evaluate the InformationValue table with one alert
    * @param the id of the alert
    * @return code for the parent thread
    */ 
    void InformationValueLoop(long long idAlert);
    
    /**
    * Method to get the pos key from an information pk.
    * @param pluginId
    * @param sourceId
    * @param searchId
    * @param valueNum
    * @param unitId
    * @param list of assets
    * @return pos key value ; -1 if error
    */
    int getPosKey(int pluginId,int sourceId,int searchId,double valueNum, int unitId, std::string assetList);
    
    /**
    * Method to get an asset list to put it in a "in" sql request
    * @param assets
    * @return asset list
    */
    std::string getAssetListSqlPrepared(Wt::Dbo::collection<Wt::Dbo::ptr<Asset> > assets);
    std::string getInformationValueListSqlPrepared(Wt::Dbo::collection<Wt::Dbo::ptr<InformationValue> > informationValues, int state);
    
    /**
    * method compare a numerical value with an alert value and a mathematics operator
    * @param the table of informationvalue received and ready to be checked
    * @param the operator method
    * @param the value to compare with (set in the alert value)
    * @param the ptr of the current alert
    * @param optionnal, the line number if we have a value linked to a key transmitted
    * @return void
    */ 
    int compareNumberValue(Session * sessionCompare, std::string valuesToCheck,bool (*mathOperator)(double,double), double valueSetInDb, long long idAlert, int lineNumber=0);

private:
    boost::mutex mutex;
    
    boost::thread_group threadsVerifyAlerts;
    boost::thread_group threadsPrepareAlertComputing;
    boost::thread_group threadsComputeAlerts;
    
    std::map<long long, Wt::Dbo::ptr<Alert>*> mapAlerts;
    // key = infid ; value = vector containing id alerts for each info
    std::map<InformationId, std::vector<long long>*> mapInfsAlertId;
    
    // key = alert id ; value = vector containing InfId for each alert
    std::map<long long, std::vector<InformationId>*> mapAlertIdInfs;
    
    // key = alert id ; value = vector containing IvaId to check for each alert
    std::map<long long, std::vector<long long>*> mapAlertIvasToCheck;
    
    // to be deported in memcache later
    // key = asset id ; value = map with
    // key = inf id ; value = map with
    // key = iva id ; value = map with
    // key = ale id ; value = boolean (already treated or not)
    std::map<long long, std::map<InformationId,std::map<long long, std::map<long long, bool*>*>*>*> mapIvasSortedByAssetsByInfos;
    
    
    std::vector<Wt::Dbo::ptr<Information2>> vInfos;
    std::vector<std::vector<Wt::Dbo::ptr<Alert>>> vAlertGroups;
    
    void addInformationToMapInfos(InformationId infId);
    void removeInformationToMapInfos(InformationId infId);
    
    enum criteria{lt = 1,le = 2,eq = 3,ne = 4,ge = 5,gt = 6};
    
    enum informationUnitType{number = 2,text = 1};
    
    std::map<long long, Wt::Dbo::ptr<Alert>*> getMapAlerts();
    
    //define the pointer of the operators functions
    bool (*ltPtr)(double, double);
    bool (*lePtr) (double, double);
    bool (*eqPtr)(double, double);
    bool (*nePtr) (double, double);
    bool (*gePtr)(double, double);
    bool (*gtPtr)(double, double);
     
};

#endif	/* ALERTPROCESSOR_H */

