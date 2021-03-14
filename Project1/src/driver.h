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
        * @param[in] fileName string indicating the name of the file to be read from
        *
        * @return Driver object with given fileName
        */
        Driver(std::string fileName = "NONE");
        /**
        * @brief Sets the election type to either IR or OPL based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInElectionType(void);
        /**
        * @brief Sets the number of candidates in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInNumCandidates(void);
        /**
        * @brief Sets the list of candidates in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInCandidates(void);
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
        int ReadInNumberOfBallots(void);
        /**
        * @brief Sets the number of seats in the election based on the data in the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ReadInNumberOfSeats(void);
        /**
        * @brief Calls all of the above ReadIn functions to read in all of the data from the CSV file
        *
        * @return int indicating 0 for success.
        */
        int ProcessCSV(void);
        /**
        * @brief Sets the name of the CSV file to a new string
        *
        * @param[in] string string indicating the new name of the file to be read from
        *
        * @return int indicating 0 for success.
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

    private:
        std::string fileName;
        std::ifstream fileHandle;
        Election election;
};



#endif
