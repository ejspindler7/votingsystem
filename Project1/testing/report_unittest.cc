#include "gtest/gtest.h"
#include "../src/report.h"
//#include "../src/ballot.h"
#include <string>
#include <vector>
#include <iostream>

class ReportTest : public ::testing::Test {
public:
	void SetUp( ) { 
    // code here will execute just before the test ensues 
	newReport = Report();
    Candidate originalCandidate = Candidate("Bui", "R");
  }
protected:
	Report newReport;
};

TEST_F(ReportTest, GetAuditReportNameTest){
	EXPECT_EQ(newReport.GetAuditReportName(), "R");
}

TEST_F(ReportTest, SetAuditReportNameTest){
    std::string newReportName = "testing Report Name set";
    newReport.SetAuditReportName(newReportName);

	EXPECT_EQ(newReport.GetAuditReportName(), "testing Report Name");
}

TEST_F(ReportTest, GetMediaReportNameTest){
	
	EXPECT_EQ(newReport.GetMediaReportName(), "Tran");
}

TEST_F(ReportTest, SetMediaReportNameTest){
	std::string newMediaReportName = "D";
	newReport.SetMediaReportName(newMediaReportName);

	EXPECT_EQ(newReport.GetMediaReportName(), "D");
}

TEST_F(ReportTest, WriteLineToAuditReportTest){
	//EXPECT_EQ(newCandidate.size(), 0);
}

TEST_F(ReportTest, CloseReportsTest){
	//newBallot.addBallot(&newBallot)

	EXPECT_EQ(newReport.CloseReports(), 0);
}

TEST_F(ReportTest, GetDateAndTimeTest){
	

}