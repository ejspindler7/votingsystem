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
	Candidate newCandidate2 = Candidate("Nguyen", "D");
	Ballot* newBallot = new Ballot(1);
	Ballot* nullBallot = NULL;
  
};

TEST_F(CandidateTest, GetNameTest){
	EXPECT_EQ(newCandidate.GetName(), "Bui");
	EXPECT_EQ(newCandidate2.GetName(), "Nguyen");
}

TEST_F(CandidateTest, GetPartyTest){
	EXPECT_EQ(newCandidate.GetParty(), "R");
	EXPECT_EQ(newCandidate2.GetParty(), "D");
}

TEST_F(CandidateTest, SetNameTest){
	EXPECT_EQ(newCandidate.GetName(), "Bui");

	std::string newName = "Tran";
	newCandidate.SetName(newName);

	EXPECT_EQ(newCandidate.GetName(), newName);
}

TEST_F(CandidateTest, SetPartyTest){
	EXPECT_EQ(newCandidate.GetParty(), "R");

	std::string newParty = "D";
	newCandidate.SetParty(newParty);

	EXPECT_EQ(newCandidate.GetParty(), "D");
}

TEST_F(CandidateTest, GetBallotListSizeTest){
	EXPECT_EQ(newCandidate.GetBallotListSize(), 0);
}

TEST_F(CandidateTest, AddBallotTest){
	EXPECT_EQ(newCandidate.GetBallotListSize(), 0);
	
	newCandidate.AddBallot(newBallot);

	EXPECT_EQ(newCandidate.GetBallotListSize(), 1);
}

TEST_F(CandidateTest, RemoveBallotTest){
	EXPECT_EQ(newCandidate.GetBallotListSize(), 0);
	EXPECT_EQ(newCandidate.RemoveBallot(),nullBallot);

	newCandidate.AddBallot(newBallot);
	EXPECT_EQ(newCandidate.GetBallotListSize(), 1);

	EXPECT_EQ(newCandidate.RemoveBallot(), newBallot);
	EXPECT_EQ(newCandidate.GetBallotListSize(), 0);
}

