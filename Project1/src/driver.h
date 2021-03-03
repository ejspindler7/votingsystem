#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "election.h"
#include <vector>
#include <fstream>

class Driver{
    public:
        Driver(std::string fileName = "NONE");
        int ReadInElectionType(void);
        int ReadInNumCandidates(void);
        int ReadInCandidates(void);
        int ReadInBallots(void);
        int ReadInNumberOfBallots(void);
        int ReadNumberOfSeats(void);
        int ProcessCSV(void);
        int SetFileName(std::string string);
        std::string GetFileName(void);
        std::vector<std::string> ParseLine(std::string line);

    private:
        std::string fileName;
        std::ifstream fileHandle;
        Election election;
};



#endif
