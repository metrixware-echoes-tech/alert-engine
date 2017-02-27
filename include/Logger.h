/**
 * @file Logger.h
 * @author Thomas Saquet, Florent Poinsaut
 * @date 
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Alert - Engine is a part of the Alert software
 * Copyright (C) 2013-2017
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 * 
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>

#include <Wt/WLogger>

#ifdef NDEBUG
    #define log(x) logger.entry(x)
#else
    #define log(x) logger.entry(x) << Wt::WLogger::sep \
                       << (unsigned int)pthread_self() << Wt::WLogger::sep \
                       << "[" << __FILE__ << ":" << __LINE__ << "]" << Wt::WLogger::sep
#endif

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
