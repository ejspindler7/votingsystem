#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "election.h"
#include <vector>
#include <fstream>
#include "report.h"

class Driver{
    public:
        Driver(std::string fileName = "NONE");
        int ReadInElectionType(void);
        int ReadInNumCandidates(void);
        int ReadInCandidates(void);
        int ReadInBallots(void);
        int ReadInNumberOfBallots(void);
        int ReadInNumberOfSeats(void);
        int ProcessCSV(void);
        int SetFileName(std::string string);
        std::string GetFileName(void);
        //std::vector<std::string> ParseLine(std::string line, std::vector<std::string> words);
        void ParseLine(std::string line, std::vector<std::string> &words, char delim);
        void ParseLine2(std::string line, std::vector<std::string> &words, char delim);
        int GetOPLVote(std::string line);
        int ComputeElection();

    private:
        std::string fileName;
        std::ifstream fileHandle;
        Election election;
};



#endif
