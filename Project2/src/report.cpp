

#include <string>
#include <iostream>
#include <ctime>
#include <iostream>
#include <fstream>
#include "report.h"
#include "election.h"

using namespace std;

// Creates a report
Report::Report(){
    string time = GetDateAndTime();
    auditReportName = "AuditReport_" + time;
    mediaReportName = "MediaReport" + time;
    auditReport.open(auditReportName);
    mediaReport.open(mediaReportName);
}

// Retrieves the audit report's name
string Report::GetAuditReportName(){
    return auditReportName;
}

// Updates the audit report's name with the provided name
int Report::SetAuditReportName(string name){
    auditReportName = name;
    return 0;
}

// Retrieves the media report's name
string Report::GetMediaReportName(){
    return mediaReportName;
}

// Updates the media report's name with the providd name
int Report::SetMediaReportName(string name){
    mediaReportName = name;
    return 0;
}

// Writes the provided line to the audit report
int Report::WriteLineToAuditReport(string line){
    auditReport << line << endl;      
    return 0;
}

// Writes the provided line to the media report
int Report::WriteLineToMediaReport(string line){
    mediaReport<< line << endl;      
    return 0;
}

/*
int Report::WriteOPLAuditReport(Election& election){
    return 0;
}
int Report::WriteOPLMediaReport(Election& election){
    return 0;
}
int Report::WriteOPLToScreen(Election& election){
    return 0;
}
int Report::WriteIRAuditReport(Election& election){
    return 0;
}
int Report::WriteIRMediaReport(Election& election){
    return 0;
}
int Report::WriteIRToScreen(Election& election){
    return 0;
}
*/

// Saves both media and audit reports
int Report::CloseReports(){
    auditReport.close();
    mediaReport.close();
    return 0;
}

// Gets the currnt date and time for naming the audit/media report
string Report::GetDateAndTime(){
    // Got idea from: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
    time_t now = time(0); // Grabs current time.
    char* dt = ctime(&now); // Converts to string form
    string str(dt);         // Converts time to string object
    return dt;
}

