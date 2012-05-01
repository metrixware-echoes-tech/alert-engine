#include "Value.h"

//builders of the class
Value::Value(int mOffset, 
             unsigned int mIdPlugin, 
             unsigned int mIdAsset, 
             unsigned int mIdSource, 
             unsigned int mIdSearch, 
             std::string mValue
            ): offset(mOffset), 
               idPlugin(mIdPlugin), 
               idAsset(mIdAsset), 
               idSource(mIdSource),
               idSearch(mIdSearch),
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

