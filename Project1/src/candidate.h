/**
 * @file candidate.h
 * @author Ryan Mower
 * @brief This file describes the Candidate class, which stores and updates information about each candidate.
 */

#ifndef CANDIDATE_H
#define CANDIDATE_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "ballot.h"

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for tracking candidate information.
 *
 * Uses its various functions to set and get all of the relevant information about the candidate.
 */
class Candidate{
    public:
        /**
        * @brief The constructor for the Candidate class.
        *
        * This function will be used to create a new candidate with the given name and party.
        *
        * @param[in] name string indicating the name of the candidate being created.
        *
        * @param[in] party sting indicating he name of the party of the candidate being created.
        *
        * @return Candidate object with name and party.
        */
        Candidate(string name, string party);
        /**
        * @brief Sets the name of the party for the candidate.
        *
        * @param[in] party The string indicating the candidate's party name.
        *
        * @return int 0 indicating success.
        */
        int SetParty(string party);
        /**
        * @brief Returns the string indicating the name of the candidate's party.
        *
        * @return string indicating the candidate's party name.
        */
        string GetParty();
        /**
        * @brief Returns the string indicating the name of the candidate.
        *
        * @return string indicating the candidate's name.
        */
        string GetName();
        /**
        * @brief Sets the name of the candidate.
        *
        * @param[in] name The string indicating the candidate's name.
        *
        * @return int 0 indicating success.
        */
        int SetName(string name);
        /**
        * @brief Adds another ballot to the list of ballots voting for the candidate.
        *
        * @param[in] ballot The pointer to a ballot which is voting for the candidate.
        *
        * @return int 0 indicating success.
        */
        int AddBallot(Ballot *ballot);
        /**
        * @brief Removess the most recently added ballot voting for the candidate from the list and returns it.
        *
        * @return Ballot* ballot popped from the candidate's list of ballots.
        */
        Ballot* RemoveBallot();
        /**
        * @brief Returns the size of the list of ballots voting for the candidate.
        *
        * @return int number of ballots in the list of ballots voting for the candidate
        */
        int GetBallotListSize();

    private:
        string party;
        string candidateName;
        vector<Ballot*> ballots;

};



#endif
