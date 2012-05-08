#include "Syslog.h"

Syslog::Syslog() 
{
}

Syslog::Syslog(std::string mReceptionDate,
               std::string mSentDate,
               std::string mHostname,
               std::string mAppName,
               std::string mProcId,
               std::string mMsgId
              ):receptionDate(mReceptionDate),
                sentDate(mSentDate),
                hostname(mHostname),
                appName(mAppName),
                procId(mProcId),
                msgId(mMsgId)
{
}

Syslog::~Syslog() {
}

unsigned int Syslog::getVersion()
{
    return version;
}

void Syslog::setVersion(unsigned int ver)
{
    version = ver;
}

unsigned int Syslog::getPrbId()
{
    return prbId;
}
void Syslog::setPrbId(unsigned int id)
{
    prbId = id;
}