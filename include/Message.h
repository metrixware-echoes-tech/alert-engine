/** 
 * The message class represent the message format received by the probes
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-04-22
 */

/**
 * Exemple de message :
 * <165>1 2003-10-11T22:14:15Z mymachine.example.com echoes-alert-probe - 3216 - ID47 
 * [offset="-1256"]
 * [ids="1-2-1-2-4-2" value="lkihazaz"][ids="1-2-1-2-4-3" value="lkihazaefzzefz"]
 * [offset="-1256"]
 * [ids="1-2-1-2-4-2" value="lkihazaz"]
 * [ids="1-2-1-2-4-3" value="lkihazaefzzefz"]
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include <string>
#include <Wt/WDateTime>

class Message {
public:
    /**
     * class' builder
     */
    Message();
    
    /**
     * class' destructor
     */
    virtual ~Message();

    /**
     * method the unserialize a value included in a message
     * @param strValue the string that contains the informations
     * @return error or success
     */
    int unserializeValue(std::string& strValue);
    
  
private:    
    //Message's Identifier
    unsigned int idMessage;
    //Probe's identifer
    unsigned int idProbe;
    //PID of the process
    unsigned int pid;  
    //name of the process
    std::string processName;
    //FQDN of the probe
    std::string FQDN;
    //Sent date of the message on the probe
    Wt::WDateTime SentDate;
    
};

#endif	/* MESSAGE_H */

