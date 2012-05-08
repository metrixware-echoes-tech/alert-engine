/** 
 * A syslog object is composed by the header informations of the received log 
 * and the properties included in the first structured datas of the log.
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-05-08
 */

#ifndef SYSLOG_H
#define	SYSLOG_H

#include <string>

class Syslog {
public:
    /**
     * class' builder
     */
    Syslog();
    /**
     * class' builder
     */
    Syslog(std::string mReceptionDate,
           std::string mSentDate,
           std::string mHostname,
           std::string mAppName,
           std::string mProcId,
           std::string mMsgId
          );
         
    virtual ~Syslog();
    
    /**
     * getters and setters of the class
     */
    unsigned int getVersion();
    void setVersion(unsigned int ver);
    
    unsigned int getPrbId();
    void setPrbId(unsigned int id);
    
private:

    /**
    * part of the log parsed here :
    * 2003-10-11T22:14:15Z mymachine.example.com echoes-alert-probe 3216 ID47 
    * [prop@5875 ver=1 probe=12]
    */   
    //TODO: add the address of the object "itself"
    std::string receptionDate; //at the reception
    std::string sentDate; //2012-05-08 10:17:01
    std::string hostname; //mymachine.example.com
    std::string appName; //echoes-alert-probe
    std::string procId; //3216
    std::string msgId; //ID47 
    unsigned int version; //1
    unsigned int prbId; //12 
};

#endif	/* SYSLOG_H */

