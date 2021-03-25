

#include <string>
#include <iostream>
#include <ctime>
#include <iostream>
#include <fstream>
#include "report.h"
#include "election.h"

using namespace std;


Report::Report(){
    string time = GetDateAndTime();
    auditReportName = "AuditReport_" + time;
    mediaReportName = "MediaReport" + time;
    auditReport.open(auditReportName);
    mediaReport.open(mediaReportName);
}

string Report::GetAuditReportName(){
    return auditReportName;
}

int Report::SetAuditReportName(string name){
    auditReportName = name;
    return 0;
}

string Report::GetMediaReportName(){
    return mediaReportName;
}

int Report::SetMediaReportName(string name){
    mediaReportName = name;
    return 0;
}
int Report::WriteLineToAuditReport(string line){
    auditReport << line << endl;
    return 0;
}

int Report::WriteLineToMediaReport(string line){
    mediaReport<< line << endl;
    return 0;
}

int Report::CloseReports(){
    auditReport.close();
    mediaReport.close();
    return 0;
}
string Report::GetDateAndTime(){
    // Got idea from: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
    time_t now = time(0); // Grabs current time.
    char* dt = ctime(&now); // Converts to string form
    string str(dt);         // Converts time to string object
    return dt;
}
