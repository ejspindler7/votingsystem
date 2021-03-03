#ifndef REPORT_H
#define REPORT_H


#include <string>
#include "election.h"
#include "candidate.h"

using namespace std;


class Report{
    public:
        Report();
        string GetAuditReportName();
        int SetAuditReportName(string name);
        string GetMediaReportName();
        int SetMediaReportName(string name);
        int WriteLineToAuditReport(string line);
        /*
        int WriteOPLAuditReport(Election& election);
        int WriteOPLMediaReport(Election& election);
        int WriteOPLToScreen(Election& election);
        int WriteIRAuditReport(Election& election);
        int WriteIRMediaReport(Election& election);
        int WriteIRToScreen(Election& election);
        */
        int CloseReports();
        string GetDateAndTime();

    private:
        string auditReportName;
        string mediaReportName;
        vector<Candidate> originalCandidates;
};



#endif
