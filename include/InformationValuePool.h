/* 
 * File:   InformationPool.h
 * Author: tsa
 *
 * Created on 10 janvier 2013, 17:56
 */

#ifndef INFORMATIONPOOL_H
#define	INFORMATIONPOOL_H

#include <tools/MainIncludeFile.h>
#include <tools/Session.h>
#include <boost/thread/thread.hpp>

class InformationValuePool {
public:
    virtual ~InformationValuePool();
    static InformationValuePool* getInstance(InformationId infId);
    InformationId infoKey;
    Session* getInformationValue(long long ivaId);
    void returnInformation(Information2* information);
    std::vector<int> alertIds;
private:
    InformationValuePool(InformationId);
    static InformationValuePool* instance;
    static boost::mutex mutex;

};

#endif	/* INFORMATIONPOOL_H */

