/** 
 * La classe Message expose le format des messages recus par les sondes
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
#include "Value.h"

class Message {
public:
    /**
     * classe builder's
     * @param the substring [ids="1-2-1-2-4-2" value="lkihazaz"]
     * @return the Value object
     */
    Value unserializeValue(std::string& strValue);
    

};

#endif	/* MESSAGE_H */

