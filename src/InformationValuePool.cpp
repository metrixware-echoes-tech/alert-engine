/* 
 * File:   InformationPool.cpp
 * Author: tsa
 * 
 * Created on 10 janvier 2013, 17:56
 */

#include "InformationValuePool.h"

InformationValuePool::InformationValuePool(InformationId infId) {
}

InformationValuePool::~InformationValuePool() {
}

InformationValuePool* InformationValuePool::getInstance(InformationId infId)
{
    mutex.lock();
    if (instance == 0)
    {
        instance = new InformationValuePool(infId);
    }
    mutex.unlock();
    return instance;
}

Session* InformationValuePool::getInformationValue(long long ivaId)
{
//    mutex.lock();
//    if (sessions.empty())
//    {
//        mutex.unlock();
        return new Session(credentials);
//    }
//    else
//    {
//        Session* session = sessions.front();
//        sessions.pop_front();
//        mutex.unlock();
//        return session;
//    }
}

void SessionPool::returnSession(Session* session)
{
    mutex.lock();
    sessions.push_back(session);
    mutex.unlock();
}