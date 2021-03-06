#include "gtest/gtest.h"
#include "../src/candidate.h"
#include "../src/ballot.h"
#include <string>
#include <vector>
#include <iostream>

class CandidateTest : public ::testing::Test {
public:
	void SetUp( ) { 
    // code here will execute just before the test ensues 
	newCandidate = Candidate("Bui", "R");
	Ballot* newBallot = Ballot(1)
  }
protected:
	Candidate newCandidate;
}

TEST_F(CandidateTest, GetNameTest){
	EXPECT_EQ(newCandidate.GetName(), "Bui");
}

TEST_F(CandidateTest, GetPartyTest){
	EXPECT_EQ(newCandiate.GetParty(), "R");
}

TEST_F(CandidateTest, SetNameTest){
	std::string newName = "Tran";
	newCandiate.setName(newName);

	EXPECT_EQ(newCandidate.GetName(), "Tran");
}

TEST_F(CandidateTest, SetPartyTest){
	std::string newParty = "D";
	newCandiate.setName(newName);

	EXPECT_EQ(newCandidate.GetParty(), "D");
}

TEST_F(CandidateTest, GetBallotListSizeTest{
	EXPECT_EQ(newCandidate.size(), 0);
}

TEST_F(CandidateTest, AddBallotTest){
	newBallot.addBallot(&newBallot)

	EXPECT_EQ(newCandidate.size(), 1);
}

TEST_F(CandidateTest, RemoveBallotTest){
	newCandidate.addBallot(&newBallot)

	EXPECT_EQ(newCandidate.size(), 1);
	EXPECT_EQ(newCandidate.RemoveBallot(), newBallot);
	EXPECT_EQ(newCandidate.size(), 0);

}