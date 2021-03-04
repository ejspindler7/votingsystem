#include "gtest/gtest.h"
#include "../src/driver.h"
#include "../src/election.h"
#include <string>
#include <iostream>


class Election : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
	electionOPL = Election();
	electionIR= Election();

  }
 protected:
  Election election1;

};



// GetElectionType
TEST_F(ElectionTests, GetElectionType){
	electionOPL.SetElectionType("OPL"); 
	electionIR.SetElectionType("IR");

	std::string expected_OPL = "OPL";
	std::string expected_IR= "IR";
    EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL"; 
    EXPECT_EQ(electionIR.GetElectionType(), expected_IR) << "Expecting IR"; 
}




// SetElectionType 
TEST_F(ElectionTests, SetElectionType){
	electionOPL.SetElectionType("OPL"); 
	electionIR.SetElectionType("IR");

	std::string expected_OPL = "OPL";
	std::string expected_IR= "IR";
    EXPECT_EQ(electionOPL.GetElectionType(), expected_OPL) << "Expecting OPL"; 
    EXPECT_EQ(electionIR.GetElectionType(), expected_IR) << "Expecting IR"; 
}






