#include "gtest/gtest.h"
#include "../src/driver.h"
//#include "../src/ballot.h"
#include <string>
#include <vector>
#include <iostream>

class DriverTests : public ::testing::Test {
public:
	void SetUp( ) { 
    // code here will execute just before the test ensues 
	newDriver = Driver("ballots");
  Election newElection = Election();
  }
protected:
	Driver newDriver;
};

TEST_F(DriverTests, ReadInElectionType){
	
}

TEST_F(DriverTests, ReadInNumCandidates){

}

TEST_F(DriverTests, ReadInCandidates){
	
}

TEST_F(DriverTests, ReadInBallots){

}

TEST_F(DriverTests, ReadInNumberOfBallots){

}

TEST_F(DriverTests, ReadInNumberOfSeats){
	
}

TEST_F(DriverTests, ProcessCSV){
	

}

TEST_F(DriverTests, SetFileName){
	

}
TEST_F(DriverTests, GetFileName){
	

}
TEST_F(DriverTests, ParseLine){
	

}
TEST_F(DriverTests, GetOPLVote){
	

}
TEST_F(DriverTests, ComputeElection){
	

}