/* 
 * File:   PoolIvaPools.cpp
 * Author: tsa
 * 
 * Created on 10 janvier 2013, 18:57
 */

#include "PoolIvaPools.h"

PoolIvaPools::PoolIvaPools() {
}

PoolIvaPools::~PoolIvaPools() {
}

PoolIvaPools* PoolIvaPools::getInstance()
{
    mutex.lock();
    if (instance == 0)
    {
        instance = new PoolIvaPools();
    }
    mutex.unlock();
    return instance;
    
}

InformationValuePool* PoolIvaPools::getIvaPool(InformationId)
{
    mutex.lock();
    if (ivaPools.empty())
    {
        mutex.unlock();
        InformationValuePool *ivaPool = new InformationValuePool(InformationId);
        return ivaPool;
    }
    else
    {
        //TODO J'EN SUIS LA
        InformationValuePool* ivaPool;
//        InformationValuePool* ivaPool = ivaPools.;
//        sessions.pop_front();
        mutex.unlock();
        return ivaPool;
    }
}