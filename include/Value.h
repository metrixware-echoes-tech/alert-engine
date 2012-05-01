/** 
 * The value class represent the value format received in the message
 * 
 * @author ECHOES Technologies (RHI)
 * @date 2012-04-24
 */

/**
 * Exemple de valeur dans un message
 * [ids="1-2-1-2" value="lkihazaz"] signification de ids=idPlugin-idAsset-idSource-idSearch
 */

#ifndef VALUE_H
#define	VALUE_H


#include <string>

class Value {
public:
    /**
     * class' builder
     */
    Value(int mOffset, 
          unsigned int mIdPlugin, 
          unsigned int mIdAsset, 
          unsigned int mIdSource, 
          unsigned int mIdSearch, 
          std::string mValue
         );
         
    Value();
    
    /**
     * class' destructor
     */
    virtual ~Value();
    
private:
    
    // time offset linked with the date of the Message.
    int offset;
    
    //ids's string contains all the ids concerning the received value
    //std::string ids;
    //plugin's name identifier
    unsigned int idPlugin;
    //hostname's identifier
    unsigned int idAsset;
    //type of source identifier (file, socket, port)
    unsigned int idSource;
    //search identifier which is done by the selected source
    unsigned int idSearch;
    
    //Value sent by the sensor
    std::string value;
    
};

#endif	/* VALUE_H */

