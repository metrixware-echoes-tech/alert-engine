/**
 * @file Logger.cpp
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

#include "Logger.h"

using namespace std;

Logger logger;

Logger::Logger() : Wt::WLogger()
{
    addField("datetime", false);
    addField("type", false);
    addField("message", false);
}

Logger::~Logger()
{
}

Wt::WLogEntry Logger::entry(const string& type)
{
    m_mutex.lock();
    Wt::WLogEntry log = Wt::WLogger::entry(type) << timestamp << sep << type << sep;
    m_mutex.unlock();

    return log;
}

void Logger::setType(unsigned short type)
{
    switch (type)
    {
        case DEBUG:
            logger.configure("*");
            break;
        case INFO:
            logger.configure("* -debug");
                break;
        case WARNING:
            logger.configure("* -debug -info");
            break;
        case SECURE:
            logger.configure("* -debug -info -warning");
            break;
        case ERROR:
            logger.configure("* -debug -info -warning -secure");
            break;
        case FATAL:
            logger.configure("* -debug -info -warning -secure -error");
            break;
        default:
            logger.configure("* -debug");
            break;            
    }

    log("debug") << "[Logger] log criticity = " << type;

    return;
}

void Logger::setFile(const string& path)
{
    Wt::WLogger::setFile(path);
    m_path = path;
    return;
}

std::string Logger::getPath() const
{
    return m_path;
}
