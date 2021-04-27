#include "gtest/gtest.h"
#include "../src/driver.h"
#include "../src/candidate.h"
#include "../src/ballot.h"
#include "../src/election.h"
#include <string>
#include <vector>
#include <iostream>

class DriverTests : public ::testing::Test {
protected:
  virtual void SetUp(){
  }
};

/*TEST_F(DriverTests, ConstructorTest){
	std::vector<std::string> fakeFiles;
	fakeFiles.push_back("ballot1");
	fakeFiles.push_back("ballot2");
	fakeFiles.push_back("ballot3");

	std::vector<std::string> realFiles;
	realFiles.push_back("ir.csv");
	testing::internal::CaptureStdout();
	Driver fakeFilesDriver(fakeFiles);
	std::string outPut = testing::internal::GetCapturedStdout();
	EXPECT_EQ(fakeFilesDriver.GetNumInputFiles(), 3); //Testing first for-loop in the Driver constructor
	EXPECT_EQ("File not valid. \n", outPut);  	//Testing second for-loop when if-condition is met
	testing::internal::CaptureStdout();
	Driver realFilesDriver(realFiles);
	std::string outPut2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ("", outPut2); 					//Testing second for-loop when if-condition isn't met

}*/

TEST_F(DriverTests, ReadInElectionTypeTest){
	std::vector<std::string> files;
	files.push_back("ir.csv");
	Driver newDriver(files);

	std::ifstream *nullPtr = NULL;
	testing::internal::CaptureStdout();
	newDriver.ReadInElectionType(nullPtr, 1);
	std::string outPut = testing::internal::GetCapturedStdout();

	EXPECT_EQ(outPut, "File Handle is not open for Election Type.\n");
        std::ifstream *filePtr = new std::ifstream;
	filePtr->open(files.at(0));
        newDriver.ReadInElectionType(filePtr, 1);
        Election& election = const_cast <Election&>(newDriver.GetElection());
	EXPECT_EQ(election.GetElectionType(), "NONE");
        std::ifstream *filePtr2 = new std::ifstream;
        filePtr2->open(files.at(0));
        newDriver.ReadInElectionType(filePtr2, 0);
        Election& election2 = const_cast <Election&>(newDriver.GetElection());
        EXPECT_EQ(election2.GetElectionType(), "IR");
}

TEST_F(DriverTests, ReadInNumCandidatesTest){
        std::vector<std::string> files;
        files.push_back("ir.csv");
        Driver newDriver(files);

        std::ifstream *nullPtr = NULL;
        EXPECT_EQ(newDriver.ReadInNumCandidates(nullPtr, 1), 0);
        std::ifstream *filePtr = new std::ifstream;
        filePtr->open(files.at(0));
        newDriver.ReadInNumCandidates(filePtr, 1);
        Election& election = const_cast <Election&>(newDriver.GetElection());
        EXPECT_EQ(election.GetNumberOfCandidates(), -1);
        std::ifstream *filePtr2 = new std::ifstream;
        filePtr2->open(files.at(0));
        newDriver.ReadInElectionType(filePtr2, 0);
        newDriver.ReadInNumCandidates(filePtr2, 0);
        Election& election2 = const_cast <Election&>(newDriver.GetElection());
        EXPECT_EQ(election2.GetNumberOfCandidates(), 4);
}

TEST_F(DriverTests, ReadInNumberOfBallots){
        std::vector<std::string> files;
        files.push_back("ir.csv");
        Driver newDriver(files);

        std::ifstream *nullPtr = NULL;
        EXPECT_EQ(newDriver.ReadInNumCandidates(nullPtr, 1), 0);
        std::ifstream *filePtr = new std::ifstream;
        filePtr->open(files.at(0));
        newDriver.ReadInNumCandidates(filePtr, 1);
        Election& election = const_cast <Election&>(newDriver.GetElection());
        EXPECT_EQ(election.GetNumberOfCandidates(), -1);
        std::ifstream *filePtr2 = new std::ifstream;
        filePtr2->open(files.at(0));
        newDriver.ReadInElectionType(filePtr2, 0);
        newDriver.ReadInNumCandidates(filePtr2, 0);
        Election& election2 = const_cast <Election&>(newDriver.GetElection());
        EXPECT_EQ(election2.GetNumberOfCandidates(), 4);
}


TEST_F(DriverTests, ParseLineTest){
	std::vector<std::string> files;
	files.push_back("ir.csv");
	Driver newDriver = Driver(files);
	
	std::string line = "one, two, three, four";
	vector<std::string> words;
	newDriver.ParseLine(line, words, ',');

	EXPECT_EQ(words.at(0), "one");
	EXPECT_EQ(words.at(1), "two");
	EXPECT_EQ(words.at(2), "three");
	EXPECT_EQ(words.at(3), "four");
}

TEST_F(DriverTests, ParseLine2Test){
	std::vector<std::string> files;
	files.push_back("ir.csv");
	Driver newDriver = Driver(files);

	std::string line = "four, three, two, one";
	vector<std::string> words;
	newDriver.ParseLine2(line, words, ',');

	EXPECT_EQ(words.at(0), "four");
	EXPECT_EQ(words.at(1), "three");
	EXPECT_EQ(words.at(2), "two");
	EXPECT_EQ(words.at(3), "one");
}

TEST_F(DriverTests, GetOPLVoteTest){
	std::vector<std::string> files;
	files.push_back("ir.csv");
	Driver newDriver = Driver(files);
	EXPECT_EQ(newDriver.GetOPLVote(",,1"), 2);
}



