#include "gtest/gtest.h"
#include "../src/driver.h"
#include "../src/candidate.h"
#include "../src/ballot.h"
#include <string>
#include <vector>
#include <iostream>

class DriverTests : public ::testing::Test {
protected:
	Driver newDriver= Driver("ballots");
};

TEST_F(DriverTests, GetFileNameTest){
	EXPECT_TRUE("ballots" == newDriver.GetFileName());
	
}

TEST_F(DriverTests, ReadIRArgumentsTest){
	Driver newDriver1= Driver("ir.csv");
	//Reading in election type
	testing::internal::CaptureStdout();
	newDriver1.ReadInElectionType();
	std::string actualElection = testing::internal::GetCapturedStdout();

	EXPECT_EQ("Compute IR election.\n", actualElection);

	//Reading in number of candidates
	testing::internal::CaptureStdout();
	newDriver1.ReadInNumCandidates();
	std::string actualNumOfCandidates = testing::internal::GetCapturedStdout();

	EXPECT_EQ("Number of candidates: 4\n", actualNumOfCandidates);

	//Reading in candidates
	EXPECT_EQ(newDriver1.ReadInCandidates(),0);

	//Reading in number of ballots
	testing::internal::CaptureStdout();
	newDriver1.ReadInNumberOfBallots();
	std::string actualNumOfBallots = testing::internal::GetCapturedStdout();

	EXPECT_EQ("Number of ballots: 9\n", actualNumOfBallots);

	//Reading in ballots
	EXPECT_EQ(newDriver1.ReadInBallots(), 0);

}

TEST_F(DriverTests, ReadOPLArgumentsTest){
	Driver newDriver2= Driver("opl.csv");
	//Reading in election type
	testing::internal::CaptureStdout();
	newDriver2.ReadInElectionType();
	std::string actualElection = testing::internal::GetCapturedStdout();

	EXPECT_EQ("Compute OPL election.\n", actualElection);

	//Reading in number of candidates
	testing::internal::CaptureStdout();
	newDriver2.ReadInNumCandidates();
	std::string actualNumOfCandidates = testing::internal::GetCapturedStdout();

	EXPECT_EQ("Number of candidates: 6\n", actualNumOfCandidates);

	//Reading in candidates
	EXPECT_EQ(newDriver2.ReadInCandidates(),0);

	//Reading in number of seats
	testing::internal::CaptureStdout();
	newDriver2.ReadInNumberOfSeats();
	std::string actualNumOfSeats = testing::internal::GetCapturedStdout();

	EXPECT_EQ("Number of seats: 3\n", actualNumOfSeats);

	//Reading in number of ballots
	testing::internal::CaptureStdout();
	newDriver2.ReadInNumberOfBallots();
	std::string actualNumOfBallots = testing::internal::GetCapturedStdout();

	EXPECT_EQ("Number of ballots: 9\n", actualNumOfBallots);

	//Reading in ballots
	EXPECT_EQ(newDriver2.ReadInBallots(), 0);
	
}

TEST_F(DriverTests, GetOPLVoteTest){
	EXPECT_EQ(newDriver.GetOPLVote(",,1"), 2);
}