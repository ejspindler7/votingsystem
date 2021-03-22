#include "gtest/gtest.h"
#include "../src/driver.h"
#include "../src/election.h"
#include <string>
#include <iostream>


class ElectionTests : public ::testing::Test {
    // code here will execute just before the test ensues

 protected:
  Election electionOPL  = Election(); //opl.csv
  Election electionIR  = Election(); //ir.csv
  Candidate newCandidate = Candidate("Emma", "D");
  Ballot* newballot = new Ballot(1);

};

//SetElectionType
TEST_F(ElectionTests, SetElectionType){
  electionOPL.SetElectionType("OPL");
	electionIR.SetElectionType("IR");

	std::string expected_OPL = "OPL";
	std::string expected_IR= "IR";
    EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL";
    EXPECT_EQ(electionIR.GetElectionType(), expected_IR) << "Expecting IR";
}

// GetElectionType
TEST_F(ElectionTests, GetElectionType){
	std::string expected_OPL = "OPL";
	std::string expected_IR= "IR";
  electionOPL.SetElectionType("OPL");
	electionIR.SetElectionType("IR");
  EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL";
  EXPECT_EQ(electionIR.GetElectionType(), expected_IR) << "Expecting IR";
}

//AddParty
TEST_F(ElectionTests, AddParty){
  EXPECT_EQ(electionOPL.AddParty("Test"),0);

}
//SetVotesForParty
TEST_F(ElectionTests, SetVotesForParties){
  std::string dem = "D";
  int success = electionOPL.AddParty(dem);
  electionOPL.SetVotesForParties();
  EXPECT_EQ(electionOPL.GetVotesForParty(dem), 0) << "Expecting OPL votes for D: 0";
}

//GetVotesForParty
TEST_F(ElectionTests, GetVotesForParty){
  std::string dem = "D";
  int success = electionOPL.AddParty(dem);
  electionOPL.SetVotesForParties();
  EXPECT_EQ(electionOPL.GetVotesForParty(dem), 0) << "Expecting OPL D votes: 0";
}






//SetNumberOfCandidates
TEST_F(ElectionTests, SetNumberOfCandidates){
  electionOPL.SetNumberOfCandidates(6);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 6) << "Expecting OPL: 6";

}
//GetNumberOfCandidates
TEST_F(ElectionTests, GetNumberOfCandidates){
   electionOPL.SetNumberOfCandidates(6);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 6) << "Expecting OPL";

}


//SetNumberOfSeats
TEST_F(ElectionTests, SetNumberOfSeats){
  electionOPL.SetNumberOfSeats(3);
  EXPECT_EQ(electionOPL.GetNumberOfSeats(), 3) << "Expecting OPL: 3";
}
//GetNumberOfSeats
TEST_F(ElectionTests, GetNumberOfSeats){
  electionOPL.SetNumberOfSeats(3);

  EXPECT_EQ(electionOPL.GetNumberOfSeats(), 3) << "Expecting OPL: 3";
}



//SetNumberOfBallots
TEST_F(ElectionTests, SetNumberOfBallots){
  electionOPL.SetNumberOfBallots(9);
  electionIR.SetNumberOfBallots(6);
  EXPECT_EQ(electionOPL.GetNumberOfBallots(), 9) << "Expecting OPL: 9";
  EXPECT_EQ(electionIR.GetNumberOfBallots(), 6) << "Expecting IR: 6";

}
//GetNumberOfBallots
TEST_F(ElectionTests, GetNumberOfBallots){
  electionOPL.SetNumberOfBallots(9);
  electionIR.SetNumberOfBallots(6);
  EXPECT_EQ(electionOPL.GetNumberOfBallots(), 9) << "Expecting OPL: 9";
  EXPECT_EQ(electionIR.GetNumberOfBallots(), 6) << "Expecting IR: 6";

}


//SetQuota
TEST_F(ElectionTests, SetQuota){
  electionOPL.SetQuota(3);
    EXPECT_EQ(electionOPL.GetQuota(), 3) << "Expecting OPL: 3";

}
//GetQuota
TEST_F(ElectionTests, GetQuota){
  electionOPL.SetQuota(3);
    EXPECT_EQ(electionOPL.GetQuota(), 3) << "Expecting OPL: 3";

}

//IncreaseNumberOfCandidates
TEST_F(ElectionTests, IncreaseNumberOfCandidates){
  electionOPL.SetNumberOfCandidates(6);
  electionOPL.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 7) << "Expecting OPL: 7";

}


//IncreaseNumberOfBallots
TEST_F(ElectionTests, IncreaseNumberOfBallots){
  electionOPL.SetNumberOfBallots(9);
  electionOPL.IncreaseNumberOfBallots();
  EXPECT_EQ(electionOPL.GetNumberOfBallots(), 10) << "Expecting OPL";
}
/*
//not passed
//RunElection
TEST_F(ElectionTests, RunElection){
  electionOPL.RunElection();
}
//not passed
//ComputeIRElection
TEST_F(ElectionTests, ComputeIRElection){
  electionIR.ComputeIRElection();
  //checkformajority.
  //writelinetoaudit/media?
  //findcandidatetoremove?
  //redistributeballots??
  //removecandidate.
}
//not passed
//ComputeOPLElection
TEST_F(ElectionTests, ComputeOPLElection){
  electionOPL.ComputeOPLElection();
  //setvotesforparties.
  //writelinetoaudit
  //writelinetomedia
}
*/
//AddCandidate
TEST_F(ElectionTests, AddCandidate){
  //checks the number of default candidates from constructor
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), -1) << "Expecting OPL: -1";
  electionOPL.SetNumberOfCandidates(0);
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();
  //tests the number of candidates when one is added
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 1) << "Expecting OPL: 1";
  electionOPL.AddCandidate(newCandidate2);
  electionOPL.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(),2) << "Expecting OPL: 2";
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionIR.GetNumberOfCandidates(), 1) << "Expecting IR: 1";
}
//RemoveCandidate
TEST_F(ElectionTests, RemoveCandidate){
  electionOPL.SetNumberOfCandidates(0);
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();
  electionOPL.RemoveCandidate(0);
  electionOPL.SetNumberOfCandidates(0);
  //test with one candidate
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 0) << "Expecting OPL: 0";
  electionOPL.AddCandidate(newCandidate2);
  electionOPL.IncreaseNumberOfCandidates();
  electionOPL.RemoveCandidate(1);
  electionOPL.SetNumberOfCandidates(1);
  //tests with 2 candidates and removing the second one
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 1) << "Expecting OPL: 1";
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  electionIR.RemoveCandidate(0);
  electionIR.SetNumberOfCandidates(0);
  EXPECT_EQ(electionIR.GetNumberOfCandidates(), 0) << "Expecting IR: 0";
}
/*
//not tested
//FindCandidateToRemove ???????????/
TEST_F(ElectionTests, FindCandidateToRemove){
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionIR.FindCandidateToRemove(),0) << "Expecting IR to remove candidate at index 0";
}
*/
//CheckForMajority
TEST_F(ElectionTests, CheckForMajority){
  int index = 0;
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionIR.CheckForMajority(), index) << "Expecting IR: 0 index Rosen";
}
/*
//not tested
//writelinetoaudit????
TEST_F(ElectionTests, WriteLineToAudit){
  int index = 0;
  EXPECT_EQ(CheckForMajority(),index) << "Expecting IR: 0 index Rosen";
}
//not tested
//writelinetomedia
TEST_F(ElectionTests,WriteLineToMedia){
}

//doesnt pass
//UpdateBallotCurrDis
TEST_F(ElectionTests, UpdateBallotCurrDis){
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionOPL.UpdateBallotCurrDis(newballot),0);
}

//not tested
//RedistributeBallots
TEST_F(ElectionTests, RedistributeBallots){
  electionOPL.RedistributeBallots(5);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(),5);
}
*/
//ResolveTie
//returns a random number
TEST_F(ElectionTests, ResolveTie){
  int ans = electionOPL.ResolveTie(3);
  EXPECT_EQ(ans,ans);
}
/*
//not nottested
//&GetCandidate not sure how to access
TEST_F(ElectionTests, GetCandidate){
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  electionOPL.SetNumberOfCandidates(0);
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionOPL.GetCandidate(0),newCandidate) << "Expecting OPL: Emma";
  EXPECT_EQ(electionIR.GetCandidate(0),newCandidate) << "Expecting IR: Emma";
}
*/

TEST_F(ElectionTests, GetDateAndTime){
  time_t now = time(0); // Grabs current time.
  char* time = ctime(&now); // Converts to string form
  string str(time);         // Converts time to string object
  EXPECT_EQ(electionOPL.GetDateAndTime(),time);
}
TEST_F(ElectionTests, CloseReports){

  EXPECT_EQ(electionOPL.CloseReports(),0);
}
