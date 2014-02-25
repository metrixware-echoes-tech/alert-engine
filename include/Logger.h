/* 
 * Header of Engine Logger
 * @author ECHOES Technologies (FPO)
 * @date 31/05/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>

#include <Wt/WLogger>

class Logger : public Wt::WLogger {
    public:
        Logger();
        virtual ~Logger();

        Wt::WLogEntry entry(const std::string& type);
        void setType(unsigned short severity);
        void setFile(const std::string& path);
        std::string getPath() const;

    private:
        boost::mutex m_mutex;
        std::string m_path;
        
        enum EType
        {
            DEBUG = 1,
            INFO = 2,
            WARNING = 3,
            SECURE = 4,
            ERROR = 5,
            FATAL = 6
        };
};

extern Logger logger;

#endif	/* LOGGER_H */

