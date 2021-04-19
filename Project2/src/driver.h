/**
 * @file driver.h
 * @author Ryan Mower
 * @brief This file describes the Driver class, which reads in election information from a CSV file.
 */

#ifndef DRIVER_H
#define DRIVER_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "election.h"
#include <vector>
#include <fstream>
#include "report.h"
#include "ballot.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for processing the CSV file for information.
 *
 * Uses its various functions to read in the values of variables from each line of the CSV file
 */
class Driver{
    public:
        /**
        * @brief The constructor for the Driver class.
        *
        * This function will be used to create a new driver to process a CSV file with the given filename.
        *
        * The file is assumed to be formatted correctly, so there is no exception handling for incorrect CSV files.
        * If the CSV file is not arranged as expected, this can lead to issues with program function, but it is considered improper use of the system and should not be expected to execute.
        *
        * @param[in] fileNames strings indicating the name of the file to be read from.
        *
        * @return Driver object with given fileName
        */
        Driver(std::vector<std::string> fileNames);
        /**
        * @brief Sets the election type to either IR or OPL based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInElectionType(std::ifstream *fh, int flag);
        /**
        * @brief Sets the number of candidates in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInNumCandidates(std::ifstream *fh, int flag);
        /**
        * @brief Sets the list of candidates in the election based on the data in the CSV file
        *
        * @return number of candidates.
        */
        int ReadInCandidates(std::ifstream *fh, int flag);
        /**
        * @brief Sets the list of ballots in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInBallots(void);
        /**
        * @brief Sets the number of ballots in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInNumberOfBallots(std::ifstream *fh, int flag);
        /**
        * @brief Sets the number of seats in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInNumberOfSeats(std::ifstream *fh, int flag);
        /**
        * @brief Calls all of the above ReadIn functions to read in all of the data from the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ProcessCSV(void);
        /**
        * @brief Reads the data from the given line into the given vector of strings, splitting based on the delim character passed
        * Does not delete lines after reading them
        *
        * @param[in] line string of text from a line of the CSV file
        *
        * @param[in] &words pointer to a vector<string> which each individual word from the line is loaded into
        *
        * @param[in] delim char which devices each word in the line
        */
        void ParseLine(std::string line, std::vector<std::string> &words, char delim);
        /**
        * @brief Reads the data from the given line into the given vector of strings, split>
        * Deletes lines after reading them
        *
        * @param[in] line string of text from a line of the CSV file
        *
        * @param[in] &words pointer to a vector<string> which each individual word from the>
        *
        * @param[in] delim char which devices each word in the line
        */
        void ParseLine2(std::string line, std::vector<std::string> &words, char delim);
        /**
        * @brief Reads the data from the given line to determine which candidate a ballot is voting for
        *
        * @param[in] line string of text from a line of the CSV file
        *
        * @return int indicating the location in the line where the vote is, or -1 if there is no vote for any candidate
        */
        int GetOPLVote(std::string line);
        /**
        * @brief Passes control to the election class by calling election.RunElection(), then closes reports after the election simulation has finished
        *
        * @return int indicating 0 for success.
        */
        int ComputeElection();

        /**
         * @brief Adds ballots to one large ballot file.
         * 
         * @return int indicating 0 for success.
         */
        int AppendToBallotFile(std::ifstream *fh, int numBallots);

        /**
         * @brief Retrieves number of files inputted.
         * 
         * @return int indicating the number of CSV files inputted.
         */
        int GetNumInputFiles(void);

        /**
         * @brief Check if the provided IR ballot ranks at least half of the candidates.
         * 
         * @return bool indicating if the ballot is valid (true- valid, flase- invalid)
         */
        bool CheckIfIRBallotValid(Ballot* ballot);

    private:
        std::string fileName;
        std::vector<std::ifstream*> fileHandles;
        Election election;
        std::ofstream ballotFile;
        std::ifstream ballotFileCompleted;
        std::string ballotFileName;
};



#endif
