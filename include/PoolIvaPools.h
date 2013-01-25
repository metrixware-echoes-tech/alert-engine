/* 
 * File:   PoolIvaPools.h
 * Author: tsa
 *
 * Created on 10 janvier 2013, 18:57
 */

#ifndef POOLIVAPOOLS_H
#define	POOLIVAPOOLS_H

#include "InformationValuePool.h"


class PoolIvaPools {
public:
    virtual ~PoolIvaPools();
    static PoolIvaPools* getInstance();
    InformationValuePool* getIvaPool(InformationId);
private:
    PoolIvaPools();
    std::list<InformationValuePool*> ivaPools;
    static PoolIvaPools* instance;
    static boost::mutex mutex;
};

#endif	/* POOLIVAPOOLS_H */

