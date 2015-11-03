/* 
 * Header of Engine Alert Processor
 * @author ECHOES Technologies (RHI, FPO)
 * @date 07/08/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef ALERTPROCESSOR_H
#define	ALERTPROCESSOR_H

#include <wait.h>

#include <csignal>
#include <ext/stdio_filebuf.h>
#include <fstream>
#include <iostream>

#include <boost/thread/thread.hpp>

#include <Wt/Utils>
#include <Wt/WDateTime>

#include <tools/Enums.h>

#include "Conf.h"

class AlertProcessor {
    public:
        AlertProcessor(Echoes::Dbo::Session &session);
        virtual ~AlertProcessor();

        /**
         * Launch a SEC instance and create a thread to retrieve Information Value for each alert resgistered in the database
         * @param sig Pointer of Signal number
         * @return error or success
         */
        int verifyAlerts(int *signum);

        /**
         * Stop All Alerts
         */
        void stopAllAlerts();

    private:
        struct AlertSpecs
        {
            bool check;
            bool start;
            std::string secConfFilename;
            pid_t secPID;
            int secInFP, secOutFP, secErrFP;
            boost::thread *ivaThread;
        };
        
        /* < alert id - < mediaSpec id - struct AlertSpecs >> */
        std::map<long long, std::map<long long, struct AlertSpecs>> m_alertsMap;

        Echoes::Dbo::Session& m_session;
        Wt::Dbo::ptr<Echoes::Dbo::Engine> m_enginePtr;

#define READ 0
#define WRITE 1
        /**
         * Stop SEC and remove its config file
         * @param IDentifier of the alert
         * @param IDentifier of the media specialization
         */
        pid_t popen_sec(const long long alertID, const long long mediaSpecID, int *infp, int *outfp, int *errfp);
        
        /**
         * Write SEC config file and launch it
         */
        void startAlert(Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr, Wt::Dbo::ptr<Echoes::Dbo::EngGrp> enoPtr);
        /**
         * Stop SEC and remove its config file
         * @param IDentifier of the alert
         * @param IDentifier of the media specialization
         */
        void stopAlert(const long long alertID, const long long mediaSpecID);

        /**
         * Retrieve InformationValue from table for one alert
         * @param IDentifier of the alert
         * @param IDentifier of the media specialization
         */
        void informationValueLoop(const long long alertID, const long long mediaSpecID);

        /**
         * Method to know when continue the collect
         * @param Period
         * @param Previous Date Time
         */
        void informationValueSleep(const unsigned period, Wt::WDateTime &previousDateTime);

        /**
         * Write SEC log to file log
         * @param fd File Descriptor
         * @param logLevel Log Level
         */
        void secLogLoop(const int fd, const std::string &logLevel);

        /**
         * if needed set time slot context
         * @param number of timeslot
         * @param start of timeslot
         * @param duration of timeslot
         * @param days of timeslot
         * @param months of timeslot
         */
        std::string setTimeSlotContext(int numTimeSlot, int start, int duration, std::vector<std::string> days, std::vector<std::string> months);

};

#endif	/* ALERTPROCESSOR_H */

