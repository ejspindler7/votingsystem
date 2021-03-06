#include "gtest/gtest.h"
#include "../src/ballot.h"
#include <string>
#include <vector>
#include <iostream>


class BallotTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
	newBallot = Ballot(1);
  }
protected:
	Ballot newBallot;
};

TEST_F(BallotTest, GetCurrDisTest){
    EXPECT_EQ(newBallot.GetCurrDis(), 0) << "Expecting 0"; 
 
}


TEST_F(BallotTest, SetCurrDisTest){
	newBallot.SetCurrDis(1); 
    EXPECT_EQ(newBallot.GetCurrDis(), 1) << "Expecting 1"; 
 
}

TEST_F(BallotTest, GetIdTest){
	EXPECT_EQ(newBallot.GetId(), 1);
}

TEST_F(BallotTest, SetIdTest){
	newBallot.SetId(99);

	EXPECT_EQ(newBallot.GetId(), 99);
}

TEST_F(BallotTest, AddCandidateTest){
	std::string expectedCandidate = "Trump";
	newBallot.AddCandidate(expectedCandidate);

	testing::internal::CaptureStdout();
	newBallot.Print();
	std::string actualCandidate = testing::internal::GetCapturedStdout();

	EXPECT_EQ(actualCandidate, expectedCandidate);

}

TEST_F(BallotTest, PrintOrderTest){
	std::string expectedCandidate1 = "Trump";
	std::string expectedCandidate2 = "Biden";
	std::string expectedCandidate3 = "Harris";

	newBallot.AddCandidate(expectedCandidate1);
	newBallot.AddCandidate(expectedCandidate2);
	newBallot.AddCandidate(expectedCandidate3);

	testing::internal::CaptureStdout();
	newBallot.Print();
	std::string actualPrintedCandidates = testing::internal::GetCapturedStdout();

	EXPECT_EQ(actualPrintedCandidates, expectedCandidate1 + "\n" + expectedCandidate2 + "\n" + expectedCandidate3)


}










