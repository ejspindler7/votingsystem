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
	Driver irDriver= Driver("ir.csv");
	Driver oplDriver= Driver("opl.csv");
};

TEST_F(DriverTests, GetFileNameTest){
	EXPECT_TRUE("ballots" == newDriver.GetFileName());
	
}

TEST_F(DriverTests, SetFileNameTest){
	newDriver.SetFileName("votes");
	EXPECT_TRUE("votes" == newDriver.GetFileName());
}

//Tests for when the input for the driver is bad
TEST_F(DriverTests, InvalidInputsTest){
	Driver badDriver= Driver("Invalid");
	std::string expectedOutput ="File Handle is not open for Election Type.\nDid not recognize election type: NONE\nFIle not open.\n";
	testing::internal::CaptureStdout();
	badDriver.ReadInElectionType();
	badDriver.ReadInCandidates();
	badDriver.ReadInBallots();
	std::string actualOutput = testing::internal::GetCapturedStdout();

	EXPECT_EQ(expectedOutput, actualOutput);
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
	newDriver1.ReadInCandidates();

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

TEST_F(DriverTests, ProcessCSVTest){
	//Processes CSV file for an IR election
	std::string expectedOutput1 = "Compute IR election.\nNumber of candidates: 4\nNumber of ballots: 9\n";
	testing::internal::CaptureStdout();
	irDriver.ProcessCSV();
	std::string actualOutput1 = testing::internal::GetCapturedStdout();

	EXPECT_EQ(expectedOutput1, actualOutput1);

	//Processes CSCV file for an OPL election
	std::string expectedOutput2 = "Compute OPL election.\nNumber of candidates: 6\nNumber of seats: 3\nNumber of ballots: 9\n";
	testing::internal::CaptureStdout();
	oplDriver.ProcessCSV();
	std::string actualOutput2 = testing::internal::GetCapturedStdout();

	EXPECT_EQ(expectedOutput2, actualOutput2);

	//Processes invalid input
	std::string expectedOutput3 = "File Handle is not open for Election Type.\nDid not recognize election type: NONE\nElection type not recognized.\nFIle not open.\n";
	testing::internal::CaptureStdout();
	newDriver.ProcessCSV();
	std::string actualOutput3 = testing::internal::GetCapturedStdout();

	EXPECT_EQ(expectedOutput3, actualOutput3);
}

TEST_F(DriverTests, ParseLineTest){
	std::string line = "one, two, three, four";
	vector<std::string> words;
	newDriver.ParseLine(line, words, ',');

	EXPECT_EQ(words.at(0), "one");
	EXPECT_EQ(words.at(1), "two");
	EXPECT_EQ(words.at(2), "three");
	EXPECT_EQ(words.at(3), "four");
}

TEST_F(DriverTests, ParseLine2Test){
	std::string line = "four, three, two, one";
	vector<std::string> words;
	newDriver.ParseLine2(line, words, ',');

	EXPECT_EQ(words.at(0), "four");
	EXPECT_EQ(words.at(1), "three");
	EXPECT_EQ(words.at(2), "two");
	EXPECT_EQ(words.at(3), "one");
}

TEST_F(DriverTests, GetOPLVoteTest){
	EXPECT_EQ(newDriver.GetOPLVote(",,1"), 2);
	EXPECT_EQ(newDriver.GetOPLVote(""), -1);
}