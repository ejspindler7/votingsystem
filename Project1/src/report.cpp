

#include <string>
#include "election.h"
#include "candidate.h"

using namespace std;


Report::Report(){
    auditReportName = "NONE";
    mediaReportName = "NONE";
}

string Report::GetAuditReportName(){
    return "ASDF";
}

int Report::SetAuditReportName(string name){
    return 0;
}

string Report::GetMediaReportName(){
    return "asdf";
}

int Report::SetMediaReportName(string name){
    return 0;
}
int Report::WriteLineToAuditReport(string line){
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
 
int Report::CloseReports(){
    return 0;
}
string Report::GetDateAndTime(){
    return "asdf";
}





