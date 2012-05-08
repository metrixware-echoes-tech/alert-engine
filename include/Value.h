/** 
 * The value class represent the value format received in the message
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-05-08
 */

/**
 * part of the log parsed here
 * idPlugin-idAsset-idSource-idSearch-idSubSearch="value"
 */

#ifndef VALUE_H
#define	VALUE_H

#include "Syslog.h"
#include <string>

class Value {
public:
    /**
     * class' builder
     */
    Value(unsigned int mIdPlugin, 
          unsigned int mIdSource, 
          unsigned int mIdSearch,
          unsigned int mNumSubSearch,  
          unsigned int mIdAsset, 
          std::string mValueCreatedDate,
          std::string mValue
         );
    /**
     * class' builder
     */         
    Value();
    
    /**
     * classgetters and setters
     */  
    unsigned int getSyslogPointer();
    void setSyslogPointer(Syslog *ptr);
    
    unsigned int getIdPlugin();
    void setIdPlugin(unsigned int id);
    
    unsigned int getIdSource();
    void setIdSource(unsigned int id);
    
    unsigned int getIdSearch();
    void setIdSearch(unsigned int id); 
    
    unsigned int getNumSubSearch();
    void setNumSubSearch(unsigned int num); 
    
    unsigned int getIdAsset();
    void setIdAsset(unsigned int id);
    
    std::string getValueCreatedDate();
    void setValueCreatedDate(std::string date);

    std::string getValue();
    void setValue(std::string val);
    
    /**
     * class' destructor
     */
    virtual ~Value();
    
 private:
    //plugin's name identifier
    unsigned int idPlugin;
    //type of source identifier (file, socket, port)
    unsigned int idSource;
    //search identifier which is done by the selected source
    unsigned int idSearch;
    //number of the regex field
    unsigned int numSubSearch;
    //hostname's identifier
    unsigned int idAsset;
    //this is the syslog sent date + offset
    std::string valueCreatedDate;  
    //Value sent by the sensor
    std::string value;

};

#endif	/* VALUE_H */

