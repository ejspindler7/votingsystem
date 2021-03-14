/**
 * @file ballot.h
 */

#ifndef BALLOT_H
#define BALLOT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for tracking ballot information.
 *
 * Uses its various functions to set and get all of the relevant information about the ballot.
 */
class Ballot{
    public:
	/**
        * @brief The constructor for the Ballot class.
        *
        * This function will be used to create a new ballot with the given ID.
        *
        * @param[in] id The ID of the ballot being created.
        *
        * @return Ballot object with id.
        */
        Ballot(int id);
        /**
        * @brief Sets the index into the list of candidates indicating which candidate the ballot is for.
        *
        * @param[in] dis The index indicating the ballot's candidate.
        */
        void SetCurrDis(int dis);
        /**
        * @brief Sets the id for the ballot to a new value.
        *
        * @param[in] id The ballot's new ID.
        */
        void SetId(int id);
        /**
        * @brief Adds an additional candidate to the ballot.
        *
        * @param[in] name The candidate's name.
        */
        void AddCandidate(string name);
        /**
        * @brief Returns the index into the list of candidates indicating which candidate the ballot is voting for.
        *
        * @return int indicating the candidate the ballot votes for.
        */
        int GetCurrDis();
        /**
        * @brief Returns the id of the ballot.
        *
        * @return int indicating the ballot's ID.
        */
        int GetId();
        /**
        * @brief Prints the ID, list of candidates, and index into list of candidates for the ballot.
        */
        void Print();
    private:
        int currentDistribution;
        int id;
        vector<string> candidates;
};



#endif
