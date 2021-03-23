#include "gtest/gtest.h"
#include "../src/candidate.h"
#include "../src/ballot.h"
#include <string>
#include <vector>
#include <iostream>

class CandidateTest : public ::testing::Test {
protected:
    // code here will execute just before the test ensues 
	Candidate newCandidate = Candidate("Bui", "R");
	Ballot* newBallot = new Ballot(1);
	Ballot* nullBallot = NULL;
  
};

TEST_F(CandidateTest, GetNameTest){
	EXPECT_EQ(newCandidate.GetName(), "Bui");
}

TEST_F(CandidateTest, GetPartyTest){
	EXPECT_EQ(newCandidate.GetParty(), "R");
}

TEST_F(CandidateTest, SetNameTest){
	std::string newName = "Tran";
	newCandidate.SetName(newName);

	EXPECT_EQ(newCandidate.GetName(), "Tran");
}

TEST_F(CandidateTest, SetPartyTest){
	std::string newParty = "D";
	newCandidate.SetParty(newParty);

	EXPECT_EQ(newCandidate.GetParty(), "D");
}

TEST_F(CandidateTest, GetBallotListSizeTest){
	EXPECT_EQ(newCandidate.GetBallotListSize(), 0);
}

TEST_F(CandidateTest, AddBallotTest){
	newCandidate.AddBallot(newBallot);

	EXPECT_EQ(newCandidate.GetBallotListSize(), 1);
}

TEST_F(CandidateTest, RemoveBallotTest){
	EXPECT_EQ(newCandidate.GetBallotListSize(), 0);

	//tests case if theres no ballots to remove
	EXPECT_EQ(newCandidate.RemoveBallot(),nullBallot);
	
	newCandidate.AddBallot(newBallot);
	EXPECT_EQ(newCandidate.GetBallotListSize(), 1);
	
	//tests if the ballot removec is returns and if the number of ballots decreased
	EXPECT_EQ(newCandidate.RemoveBallot(), newBallot);
	EXPECT_EQ(newCandidate.GetBallotListSize(), 0);
}

