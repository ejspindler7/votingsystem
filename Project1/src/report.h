/**
 * @file report.h
 */

#ifndef REPORT_H
#define REPORT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include "election.h"

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for producing election reports.
 *
 * Uses its various funcctions to update information in the report files and save them to the comptuer, as well as printing election result to the terminal
 */
class Report{
    public:
        /**
        * @brief The constructor for the Report class.
        *
        * This function will be used to create a new Report class which produces a media and audit report and writes results to the terminal
        *
        * @return Report object
        */
        Report();
        /**
        * @brief Returns the string indicating the name of the audit report file.
        *
        * @return string indicating the candidate's party name.
        */
        string GetAuditReportName();
        /**
        * @brief Sets the string indicating the name of the audit report file.
        *
        * @param[in] name The string indicating the new name of the audit report file.
        *
        * @return int 0 indicating success or 1 indicating failure.
        */
        int SetAuditReportName(string name);
        /**
        * @brief Returns the string indicating the name of the media report file.
        *
        * @return string indicating the candidate's party name.
        */
        string GetMediaReportName();
        /**
        * @brief Sets the string indicating the name of the media report file to the given name.
        *
        * @param[in] name The string indicating the new name of the media report file.
        *
        * @return int 0 indicating success or 1 indicating failure.
        */
        int SetMediaReportName(string name);
        /**
        * @brief Adds the given string to the end of the audit report file.
        *
        * @param[in] line The string to be appended to the audit file.
        *
        * @return int 0 indicating success or 1 indicating failure.
        */
        int WriteLineToAuditReport(string line);
        /**
        * @brief Adds the given string to the end of the media report file.
        *
        * @param[in] line The string to be appended to the media file.
        *
        * @return int 0 indicating success or 1 indicating failure.
        */
        int WriteLineToMediaReport(string line);
        /*
        int WriteOPLAuditReport(Election& election);
        int WriteOPLMediaReport(Election& election);
        int WriteOPLToScreen(Election& election);
        int WriteIRAuditReport(Election& election);
        int WriteIRMediaReport(Election& election);
        int WriteIRToScreen(Election& election);
        */
        /**
        * @brief Closes all of the report files.
        *
        * @return int 0 indicating success or 1 indicating failure.
        */
        int CloseReports();
        /**
        * @brief Gets the current date and time, then converts them into a string and returns it.
        *
        * @return string consisting of the current date and time.
        */
        string GetDateAndTime();

    private:
        string auditReportName;
        string mediaReportName;
        ofstream auditReport;
        ofstream mediaReport;
        vector<Candidate> originalCandidates;
};



#endif
