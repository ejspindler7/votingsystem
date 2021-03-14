/**
 * @file ballot.h
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
        * @param[in] fileName string indicating the name of the file to be read from
        *
        * @return Driver object with given fileName
        */
        Driver(std::string fileName = "NONE");
        /**
        * @brief Sets the election type to either IR or OPL based on the data in the CSV file
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int ReadInElectionType(void);
        /**
        * @brief Sets the number of candidates in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int ReadInNumCandidates(void);
        /**
        * @brief Sets the list of candidates in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int ReadInCandidates(void);
        /**
        * @brief Sets the list of ballots in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int ReadInBallots(void);
        /**
        * @brief Sets the number of ballots in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int ReadInNumberOfBallots(void);
        /**
        * @brief Sets the number of seats in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int ReadInNumberOfSeats(void);
        /**
        * @brief Calls all of the above ReadIn functions to read in all of the data from the CSV file
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int ProcessCSV(void);
        /**
        * @brief Sets the name of the CSV file to a new string
        *
        * @param[in] string string indicating the new name of the file to be read from
        *
        * @return int indicating 0 for success or 1 for failure.
        */
        int SetFileName(std::string string);
        /**
        * @brief Returns the string indicating the filename for the CSV file being read from
        *
        * @return string indicating the name of the CSV file
        */
        std::string GetFileName(void);
        //std::vector<std::string> ParseLine(std::string line, std::vector<std::string> words);
        /**
        * @brief Reads the data from the given line into the given vector of strings, splitting based on the delim character passed
        *
        * @param[in] line string of text from a line of the CSV file
        *
        * @param[in] &words pointer to a vector<string> which each individual word from the line is loaded into
        *
        * @param[in] delim char which devices each word in the line
        */
        void ParseLine(std::string line, std::vector<std::string> &words, char delim);
        void ParseLine2(std::string line, std::vector<std::string> &words, char delim);
        int GetOPLVote(std::string line);
        >
        /**
        * @brief Passes control to the election class by calling election.RunElection(), then closes reports after the election simulation has finished
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int ComputeElection();

    private:
        std::string fileName;
        std::ifstream fileHandle;
        Election election;
};



#endif
