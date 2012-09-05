#include "Value.h"

//builders of the class
Value::Value(unsigned int mIdPlugin, 
             unsigned int mIdSource, 
             unsigned int mIdSearch,
             unsigned int mNumSubSearch, //number of the value in the sub search (match with nb value in search)  
             unsigned int mIdAsset, 
             std::string mValueCreatedDate,
             std::string mValue
            ): idPlugin(mIdPlugin), 
               idSource(mIdSource),
               idSearch(mIdSearch),
               numSubSearch(mNumSubSearch),
               idAsset(mIdAsset), 
               valueCreatedDate(mValueCreatedDate),
               value(mValue)
{
}

Value::Value()
{
}

//destructor of the class
Value::~Value()
{
}

//getter and setter of the class:
unsigned int Value::getIdPlugin()
{
    return idPlugin;
}

void Value::setIdPlugin(unsigned int id)
{
    idPlugin = id;
}

unsigned int Value::getIdSource()
{
    return idSource;
}

void Value::setIdSource(unsigned int id)
{
    idSource = id;
}

unsigned int Value::getIdSearch()
{
    return idSearch;
}

void Value::setIdSearch(unsigned int id)
{
    idSearch = id;
}

unsigned int Value::getNumSubSearch()
{
    return numSubSearch;
}
void Value::setNumSubSearch(unsigned int num)
{
    numSubSearch = num;
}

unsigned int Value::getIdAsset()
{
    return idAsset;
}

void Value::setIdAsset(unsigned int id)
{
    idAsset = id;
}

std::string Value::getValueCreatedDate()
{
    return valueCreatedDate;
}

void Value::setValueCreatedDate(std::string date)
{
    valueCreatedDate = date;
}

std::string Value::getValue()
{
    return value;
}

void Value::setValue(std::string val)
{
    value = val;
}