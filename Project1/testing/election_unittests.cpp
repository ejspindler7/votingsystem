#include "gtest/gtest.h"
#include "../src/driver.h"
#include "../src/election.h"
#include <string>
#include <iostream>


class ElectionTests : public ::testing::Test {
public:
  void SetUp() { 
    // code here will execute just before the test ensues 
	  electionOPL = Election();
	  electionIR = Election();

  }
 protected:
  Election electionOPL; //opl.csv
  Election electionIR; //ir.csv

};

// GetElectionType
TEST_F(ElectionTests, GetElectionType){
	std::string expected_OPL = "OPL";
	std::string expected_IR= "IR";
  EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL"; 
  EXPECT_EQ(electionIR.GetElectionType(), expected_IR) << "Expecting IR"; 
}

//GetVotesForParty
TEST_F(ElectionTests, GetVotesForParty){
  EXPECT_EQ(electionOPL.GetVotesForParty(), 9) << "Expecting OPL: 9"; 
}

//SetVotesForParty
TEST_F(ElectionTests, SetVotesForParties){
  electionOPL.SetVotesForParties();
  EXPECT_EQ(electionOPL.GetVotesForParty(), 9) << "Expecting OPL: 9"; 
}

//SetElectionType
TEST_F(ElectionTests, SetElectionType){
  electionOPL.SetElectionType("OPL"); 
	electionIR.SetElectionType("IR");

	std::string expected_OPL = "OPL";
	std::string expected_IR= "IR";
    EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL"; 
    EXPECT_EQ(electionIR.GetElectionType(), expected_IR) << "Expecting IR"; 
}

//SetNumberOfCandidates
TEST_F(ElectionTests, SetNumberOfCandidates){
  electionOPL.SetNumberOfCandidates(6);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 6) << "Expecting OPL: 6"; 

}

//GetNumberOfSeats
TEST_F(ElectionTests, GetNumberOfSeats){
  EXPECT_EQ(electionOPL.GetNumberOfSeats(), 3) << "Expecting OPL: 3"; 
}

//SetNumberOfSeats
TEST_F(ElectionTests, SetNumberOfSeats){
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


//GetQuota
TEST_F(ElectionTests, GetQuota){
    EXPECT_EQ(electionOPL.GetQuota(), 3) << "Expecting OPL: 3"; 

}

//SetQuota
TEST_F(ElectionTests, SetQuota){
  electionOPL.SetQuota(3);
    EXPECT_EQ(electionOPL.GetQuota(), 3) << "Expecting OPL: 3"; 

}

//GetNumberOfCandidates
TEST_F(ElectionTests, GetNumberOfCandidates){
   electionOPL.SetNumberOfCandidates(6);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 6) << "Expecting OPL"; 

}

//IncreaseNumberOfCandidates
TEST_F(ElectionTests, IncreaseNumberOfCandidates){
  electionOPL.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 7) << "Expecting OPL"; 

}

//GetNumberOfBallots
TEST_F(ElectionTests, GetNumberOfBallots){
  EXPECT_EQ(electionOPL.GetNumberOfBallots(), 9) << "Expecting OPL"; 

}

//IncreaseNumberOfBallots
TEST_F(ElectionTests, IncreaseNumberOfBallots){
  electionOPL.IncreaseNumberOfBallots();
  EXPECT_EQ(electionOPL.GetNumberOfBallots(), 10) << "Expecting OPL"; 
}

//RunElection
TEST_F(ElectionTests, RunElection){
  electionOPL.RunElection();
}

//ComputeIRElection
TEST_F(ElectionTests, ComputeIRElection){
  electionIR.ComputeIRElection();
  //checkformajority.
  //writelinetoaudit/media?
  //findcandidatetoremove?
  //redistributeballots??
  //removecandidate
  //getparty

}

//ComputeOPLElection
TEST_F(ElectionTests, ComputeOPLElection){
  electionOPL.ComputeOPLElection();
}

//AddCandidate
TEST_F(ElectionTests, AddCandidate){
  Candidate newCandidate = Candidate("Emma", "D");
  electionOPL.AddCandidate(newCandidate);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 8) << "Expecting OPL"; 

}

//RemoveCandidate
TEST_F(ElectionTests, RemoveCandidate){
  electionOPL.RemoveCandidate("Emma");
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 7) << "Expecting OPL"; 

}

//FindCandidateToRemove ???????????/
TEST_F(ElectionTests, FindCandidateToRemove){//NOT SURE HOW TO TEST BC THE IR HAS ROSEN WIN FIRST ROUND I BELIEVE
  EXPECT_EQ(electionIR.FindCandidateToRemove(),);
}

//AddBallot
TEST_F(ElectionTests, AddBallot){
  
}

//AddParty ??????
TEST_F(ElectionTests, AddParty){
  electionOPL.AddParty("Test");

}

//CheckForMajority
TEST_F(ElectionTests, CheckForMajority){
  int index = 0;
  EXPECT_EQ(CheckForMajority(),index) << "Expecting IR: 0 index Rosen"; 

}

//writelinetoaudit????
TEST_F(ElectionTests, WriteLineToAudit){
  int index = 0;
  EXPECT_EQ(CheckForMajority(),index) << "Expecting IR: 0 index Rosen"; 

}
//writelinetomedia
TES_F(ElectionTests,WriteLineToMedia){

}

//UpdateBallotCurrDis
TEST_F(ElectionTests, UpdateBallotCurrDis){
  
}

//RedistributeBallots
TEST_F(ElectionTests, RedistributeBallots){
  
}

//SetCandidateRoundCountVotesElement
TEST_F(ElectionTests, SetCandidateRoundCountVotesElement){
  
}

//ResolveTie
TEST_F(ElectionTests, ResolveTie){
  
}

//&GetCandidate
TEST_F(ElectionTests, &GetCandidate){
  
}








