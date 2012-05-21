/** 
 * A structured data represent a received log : a syslog object and 
 * multiples values.
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-05-08
 */

#ifndef STRUCTUREDDATA_H
#define	STRUCTUREDDATA_H

#include "Syslog.h"
#include "Value.h"
#include <string>
#include <queue>
#include <iostream>

class StructuredData {
public:
    /**
     * class' builder
     */
    StructuredData();
    virtual ~StructuredData();
    /**
     * example of a rawStructuredData : 
     * [res2@5875 offset=10 8-4-5-6-2="53" 8-4-5-6-1="987"]
     * [res1@5875 offset=15 8-4-5-6="543" 8-4-5-6="54546"]
     */
    
    /**
     * method to fill the value's queue with the initial rawStructuredData 
     * @param the rawStructuredData
     * @return error or success
     */
    int unserializeStructuredData(std::string& rawStructuredData);
    
    /**
     * method to unserialize the SD Elements included in a rawStructuredData
     * @param strSDElement the string that contains the informations
     * @return error or success
     */
    int unserializeSDElement(std::string& strSDElement);
    
    /**
     * method to unserialize a value included in a SDElement
     * @param strValue the string that contains the informations
     * @param offset the offet contained on the sd-element to calculate the date
     * @return error or success
     */
    int unserializeValue(std::string& strValue, int offset);
    
    /**
     * method to unserialize the sd-element concerning the properties
     * @param strProperties the sub string of rawStructuredData that contains the properties
     * @return error or success
     */
    int unserializeProperties(std::string& strProperties);
    
private:
    Syslog syslogHeader;
    Value tempValue;
    std::queue<Value> valuesFifo;
};

#endif	/* STRUCTUREDDATA_H */

