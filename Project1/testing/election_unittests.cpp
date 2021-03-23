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
  Election election  = Election(); 

  Candidate newCandidate = Candidate("Emma", "D");
  Candidate newCandidate2 = Candidate("Eric", "R");
  Candidate newCandidate3 = Candidate("Ryan", "I");
  Candidate newCandidate4 = Candidate("Hoai", "D");

  Ballot* newballot = new Ballot(1);
  Ballot* newballot2 = new Ballot(2);
  Ballot* newballot3 = new Ballot(3);
  Ballot* newballot4 = new Ballot(4);
  Ballot* newballot5 = new Ballot(5);
  Ballot* newballot6 = new Ballot(6);

};

//SetElectionType
TEST_F(ElectionTests, SetElectionType){
  electionOPL.SetElectionType("OPL");
	std::string expected_OPL = "OPL";
  EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL";
}

// GetElectionType
TEST_F(ElectionTests, GetElectionType){
  //constructor test
  EXPECT_EQ(electionOPL.GetElectionType(), "NONE") << "Expecting NONE";

	std::string expected_OPL = "OPL";
  electionOPL.SetElectionType("OPL");
  EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL";
}

TEST_F(ElectionTests, GetNumberParties){
  std::string independent = "I";
  electionOPL.AddParty(independent);
  EXPECT_EQ(electionOPL.GetNumberParties(),1);
}

//AddParty
TEST_F(ElectionTests, AddParty){
  //party adds 
  std::string independent = "I";
  electionOPL.AddParty(independent);
  EXPECT_EQ(electionOPL.GetNumberParties(), 1);
  
  //try to add the same party
  electionOPL.AddParty(independent);
  EXPECT_EQ(electionOPL.GetNumberParties(), 1);

}
//SetVotesForParty !
TEST_F(ElectionTests, SetVotesForParties){
  newballot->AddCandidate(newCandidate.GetName());
  newCandidate.AddBallot(newballot);
  electionOPL.SetNumberOfCandidates(0);
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();  
  std::string dem = "D";
  int success = electionOPL.AddParty(dem);
  electionOPL.SetVotesForParties();
  EXPECT_EQ(electionOPL.GetVotesForParty(dem), 1) << "Expecting OPL votes for D: 1";
}

//GetVotesForParty !
TEST_F(ElectionTests, GetVotesForParty){
  newballot->AddCandidate(newCandidate.GetName());
  newCandidate.AddBallot(newballot);
  electionOPL.SetNumberOfCandidates(0);
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();  
  std::string dem = "D";
  int success = electionOPL.AddParty(dem);
  electionOPL.SetVotesForParties();
  EXPECT_EQ(electionOPL.GetVotesForParty(dem), 1) << "Expecting OPL D votes: 1";
}


//SetNumberOfCandidates
TEST_F(ElectionTests, SetNumberOfCandidates){
  electionOPL.SetNumberOfCandidates(6);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 6) << "Expecting OPL: 6";

}
//GetNumberOfCandidates
TEST_F(ElectionTests, GetNumberOfCandidates){
  //testing constructor
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), -1) << "Expecting -1";

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
//testing constructor
  EXPECT_EQ(electionOPL.GetNumberOfSeats(), -1) << "Expecting -1";

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
  //testing constructor
  EXPECT_EQ(electionOPL.GetNumberOfBallots(), -1) << "Expecting -1";

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
  //testing constructor
  EXPECT_EQ(electionOPL.GetQuota(), -1) << "Expecting -1";

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
  //tests with more than one added
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(),2) << "Expecting OPL: 2";
}
//RemoveCandidate
TEST_F(ElectionTests, RemoveCandidate){
  //test with one candidate that gets removed
  electionOPL.SetNumberOfCandidates(0);
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();
  electionOPL.RemoveCandidate(0);
  electionOPL.SetNumberOfCandidates(0);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 0) << "Expecting OPL: 0";

  //tests with 2 candidates and removing the second one
  electionOPL.AddCandidate(newCandidate2);
  electionOPL.IncreaseNumberOfCandidates();
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();
  electionOPL.RemoveCandidate(1);
  electionOPL.SetNumberOfCandidates(1);
  EXPECT_EQ(electionOPL.GetNumberOfCandidates(), 1) << "Expecting OPL: 1";
  
}

TEST_F(ElectionTests, FindCandidateToRemove){
//one candidate no ballot
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionIR.FindCandidateToRemove(),0) << "Expecting IR to remove candidate at index 0";

//two ballots two candidates
  newballot->AddCandidate(newCandidate.GetName());
  newCandidate.AddBallot(newballot);
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();

  newballot2->AddCandidate(newCandidate2.GetName());
  newCandidate2.AddBallot(newballot);
  electionIR.SetNumberOfCandidates(1);
  electionIR.AddCandidate(newCandidate2);
  electionIR.IncreaseNumberOfCandidates();    
  std::string dem = "D";
  std::string rep = "R";
  int success = electionIR.AddParty(dem);
  int success2 = electionIR.AddParty(rep);
  electionIR.SetVotesForParties();

  //check for tie
  EXPECT_EQ(electionIR.FindCandidateToRemove(),0) << "Expecting IR to resolve tie";

  //3 ballots two candidates
  newballot3->AddCandidate(newCandidate2.GetName());
  newCandidate2.AddBallot(newballot3);
  electionIR.SetVotesForParties();
  EXPECT_EQ(electionIR.FindCandidateToRemove(),0) << "Expecting IR to remove First Candidate";
}


//CheckForMajority
TEST_F(ElectionTests, CheckForMajority){
  //tests to see if last candidate
  electionOPL.SetNumberOfCandidates(0);
  electionOPL.AddCandidate(newCandidate);
  electionOPL.IncreaseNumberOfCandidates();
  EXPECT_EQ(electionOPL.CheckForMajority(), 0) << "Expecting IR: 0 index Rosen";

  //have a tie for majority will return -1
  newballot->AddCandidate(newCandidate.GetName());
  newballot2->AddCandidate(newCandidate2.GetName());

  newCandidate.AddBallot(newballot);
  newCandidate2.AddBallot(newballot2);

  electionIR.SetNumberOfCandidates(0);

  electionIR.AddCandidate(newCandidate);
  electionIR.AddCandidate(newCandidate2);

  electionIR.IncreaseNumberOfCandidates();
  electionIR.IncreaseNumberOfCandidates(); 

  std::string dem = "D";
  std::string rep = "R";
  int success = electionIR.AddParty(dem);
  int success2 = electionIR.AddParty(rep);
  electionIR.SetVotesForParties();

  electionIR.SetNumberOfBallots(2);

  EXPECT_EQ(electionIR.CheckForMajority(),-1) << "Expecting IR to have winning index of -1";
  
  //one candidate has a majority 
  newballot3->AddCandidate(newCandidate2.GetName());
  newballot->AddCandidate(newCandidate.GetName());
  newballot2->AddCandidate(newCandidate2.GetName());

  newCandidate.AddBallot(newballot);
  newCandidate2.AddBallot(newballot2);
  newCandidate2.AddBallot(newballot3);

  electionOPL.SetNumberOfCandidates(0);

  electionOPL.AddCandidate(newCandidate);
  electionOPL.AddCandidate(newCandidate2);

  electionOPL.IncreaseNumberOfCandidates();
  electionOPL.IncreaseNumberOfCandidates(); 

  election.SetNumberOfBallots(5);

  std::string dem3 = "D";
  std::string rep3 = "R";
  int success3 = electionOPL.AddParty(dem3);
  int success4 = electionOPL.AddParty(rep3);
  electionIR.SetVotesForParties();
  EXPECT_EQ(electionOPL.CheckForMajority(),2) << "Expecting IR to have winning index of 2";

  //candidate has more votes than other candidates but not the majority
  newballot6->AddCandidate(newCandidate3.GetName());
  newballot4->AddCandidate(newCandidate4.GetName());
  newballot5->AddCandidate(newCandidate4.GetName());

  newCandidate3.AddBallot(newballot6);
  newCandidate4.AddBallot(newballot4);
  newCandidate4.AddBallot(newballot5);

  election.SetNumberOfBallots(6);
  election.SetNumberOfCandidates(0);
  election.AddCandidate(newCandidate);
  election.AddCandidate(newCandidate2);
  election.AddCandidate(newCandidate3);
  election.AddCandidate(newCandidate4);

  election.IncreaseNumberOfCandidates();
  election.IncreaseNumberOfCandidates(); 
  election.IncreaseNumberOfCandidates();
  election.IncreaseNumberOfCandidates(); 

  std::string dem4 = "D";
  std::string rep4 = "R";
  std::string ind = "I";

  int success5 = election.AddParty(dem4);
  int success6 = election.AddParty(rep4);
  int success7 = election.AddParty(ind);

  election.SetVotesForParties();

  EXPECT_EQ(election.CheckForMajority(),-1) << "Expecting IR to have winning index of -1";
}


//UpdateBallotCurrDis
TEST_F(ElectionTests, UpdateBallotCurrDis){
  //did not find new candidiate
  EXPECT_EQ(electionOPL.UpdateBallotCurrDis(newballot),-1);

  //ran out of candidates
  newballot->AddCandidate(newCandidate.GetName());
  newballot->SetCurrDis(3);
  EXPECT_EQ(electionIR.UpdateBallotCurrDis(newballot),-1);

  //updates ballots
  newballot2->AddCandidate(newCandidate2.GetName());
  newballot2->AddCandidate(newCandidate3.GetName());
  newballot2->AddCandidate(newCandidate.GetName());
  newballot2->AddCandidate(newCandidate4.GetName());

  newballot3->AddCandidate(newCandidate3.GetName());

  newballot2->SetCurrDis(0);
  newCandidate.AddBallot(newballot2);
  newCandidate2.AddBallot(newballot3);

  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.AddCandidate(newCandidate2);

  electionIR.IncreaseNumberOfCandidates();
  electionIR.IncreaseNumberOfCandidates();

  EXPECT_EQ(electionIR.UpdateBallotCurrDis(newballot2),0);
}

//RedistributeBallots
TEST_F(ElectionTests, RedistributeBallots){
  newballot2->AddCandidate(newCandidate2.GetName());
  newballot2->AddCandidate(newCandidate3.GetName());

  newballot3->AddCandidate(newCandidate3.GetName());
  newballot3->AddCandidate(newCandidate2.GetName());

  newballot2->SetCurrDis(0);
  //newCandidate.AddBallot(newballot2);
  newCandidate2.AddBallot(newballot2);
  newCandidate3.AddBallot(newballot3);

  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate2);
  electionIR.AddCandidate(newCandidate3);

  electionIR.IncreaseNumberOfCandidates();
  electionIR.IncreaseNumberOfCandidates();

  electionIR.RedistributeBallots(1);
  EXPECT_EQ(newCandidate2.GetBallotListSize(),1);
  EXPECT_EQ(newCandidate3.GetBallotListSize(),1);

}

//ResolveTie
//returns a random number
TEST_F(ElectionTests, ResolveTie){
  int ans = electionOPL.ResolveTie(3);
  EXPECT_EQ(ans,ans);
}


//&GetCandidate not sure how to access
TEST_F(ElectionTests, GetCandidate){
  electionIR.SetNumberOfCandidates(0);
  electionIR.AddCandidate(newCandidate);
  electionIR.IncreaseNumberOfCandidates();
  
  EXPECT_TRUE(electionIR.GetCandidate(0).GetName() == "Emma");
 
}


TEST_F(ElectionTests, GetDateAndTime){
  time_t now = time(0); // Grabs current time.
  char* time = ctime(&now); // Converts to string form
  string str(time);         // Converts time to string object
  EXPECT_EQ(electionOPL.GetDateAndTime(),time);
}

TEST_F(ElectionTests, CloseReports){
  EXPECT_EQ(electionOPL.CloseReports(),0);
}
