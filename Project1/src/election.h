/**
 * @file election.h
 */

#ifndef ELECTION_H
#define ELECTION_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <map>
#include "candidate.h"
#include "report.h"
#include <vector>

using namespace std;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for tracking election information and running the election.
 *
 * Uses its various functions to set and get all of the relevant information about the election.
 * Uses this election information to simulate the election and determine its results.
 */
class Election{
    public:
        /**
        * @brief The constructor for the Election class.
        *
        * This function will be used to create a new election with the variables initialized to their starting values.
        *
        * @return Election object.
        */
        Election();
        /**
        * @brief Gets the number of votes for the given party.
        *
        * @param[in] party_name string indicating the name of the party.
        *
        * @return int indicating the number of votes for the party in this election
        */
        int GetVotesForParty(string party_name);
        /**
        * @brief Sets the number of votes for the given party to the given int.
        *
        * @param[in] party_name string indicating the name of the party.
        *
        * @param[in] num_votes int indicating the number of votes forthe party.
        *
        * @return int 0 for success or 1 for failure
        */
        int SetVotesForParty(string party_name, int num_votes);
        /**
        * @brief Sets the type of the election to the given string.
        *
        * @param[in] election_type string indicating the type of the election
        *
        * @return int 0 for success or 1 for failure
        */
        int SetElectionType(string election_type);
        /**
        * @brief Sets the number of candidates in the election to the given int.
        *
        * @param[in] num int indicating the number of candidates in the election
        *
        * @return int 0 for success or 1 for failure
        */
        int SetNumberOfCandidates(int num);
        /**
        * @brief Increases the number of votes for the given party by one.
        *
        * @param[in] string party_name of the party whose votes are being increased
        *
        * @return int new number of votes for the party
        */
        int IncrementVotesForParty(string party_name);
        /**
        * @brief Gets the number of seats to be assigned.
        *
        * @return int indicating the number of seats to be assigned between all candidates in this election
        */
        int GetNumberOfSeats();
        /**
        * @brief Sets the number of seats to be assigned in the election.
        *
        * @param[in] num int indicating the number of seats to be assigned in the election.
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int SetNumberOfSeats(int num);
        /**
        * @brief Sets the number of seats to be assigned in the election.
        *
        * @param[in] num int indicating the number of seats to be assigned in the election.
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int SetNumberOfBallots(int num);
        /**
        * @brief Gets the quota, used to determine the proper number of seats per party in an open party election
        *
        * @return int quota for the election
        */
        int GetQuota();
        /**
        * @brief Sets the quota for the election.
        *
        * @param[in] quota int indicating the new quota to be used in the election.
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int SetQuota(int quota);
        /**
        * @brief Gets the election type for this selection
        *
        * @return string indicating the type of the election
        */
        string GetElectionType();
        /**
        * @brief Gets the number of candidates participating in the election
        *
        * @return int number of candidates in the election
        */
        int GetNumberOfCandidates();
        /**
        * @brief Increases the number of candidates in the election by one
        *
        * @return int new number of candidates in the election
        */
        int IncreaseNumberOfCandidates();
        /**
        * @brief Gets the number of ballots in the election
        *
        * @return int number of ballots voting for all candidates/parties in the election
        */
        int GetNumberOfBallots();
        /**
        * @brief Increases the number of ballots in the election by one
        *
        * @return int new number of ballots in the election
        */
        int IncreaseNumberOfBallots();
        /**
        * @brief Main function for running the election
        * Updates the audit and media file
        * Calls the correct election computation function based on the election type
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int RunElection();
        /**
        * @brief Main function for computing instant runoff election results
        * Updates the audit and media file
        * Calls the relevant helper functions to destermine the winning candidate
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int ComputeIRElection();
        /**
        * @brief Main function for computing instant runoff election results
        * Updates the audit and media file
        * Calls the relevant helper functions to destermine the winning parties and candidates
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int ComputeOPLElection();
        /**
        * @brief Adds the given candidate to the election.
        *
        * @param[in] candidate Candidate to be added to the election.
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int AddCandidate(Candidate &candidate);
        /**
        * @brief Removes the candidate with the given name from the election.
        *
        * @param[in] name string indicating the name of the candidate to remove from the election.
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int RemoveCandidate(string name);
        /**
        * @brief Determines the candidate with the lowest number of votes and removes them from the election.
        * In case of ties, the loser is determined based on a coinflip
        *
        * @return string indicating the name of the candidate to remove
        */
        string FindCandidateToRemove();
        /**
        * @brief Adds the given ballot to the election.
        *
        * @param[in] ballot Ballot to be added to the election.
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int AddBallot(Ballot balllot);
        /**
        * @brief Determines if any candidate has the majority of votes, and if so, returns their ID
        *
        * @return int indicating the id of the candidate with the most votes, or -1 if none such candidate exists
        */
        int CheckForMajority();
        /**
        * @brief Given the id of a candidate who has been eliminated, redistributes their ballots among the other candidates
        *
        * @param[in] eliminated_candidate int indicating the id of the candidate who has been removed
        *
        * @return int indicating 0 for success or 1 for failure
        */
        int RedistributeBallots(int eliminated_candidate);
        int SetCandidateRoundCountVotesElement(string name, int cout, int vote_num);
        /**
        * @brief Given a number of candidates, generates a random number to indicate a winner
        *
        * @param[in] num_candidates int indicating the number of candidates to select from
        *
        * @return int from 0 to num_candidates - 1 indicating which candidate was randomly selected to win
        */
        int ResolveTie(int num_candidates);
        /**
        * @brief Given an index, returns the candidate at that index in the candidates array
        *
        * @param[in] idx int indicating the index of the candidate to return
        *
        * @return Candidate candidate located at the given index in the candidates array
        */
        Candidate GetCandidate(int idx);


    private:
        string electionType;
        int numberOfCandidates;
        int numberOfBallots;
        vector<Candidate> candidates;
        int numberOfSeats;
        int quota;
        //Report report;
        vector<string> parties;
        map<string, int> seatsPerPartyWholeNumber;
        map<string, int> seatsPerPartyRemainder;
        map<string, int> numVotesForParty;
        map<string, vector<Candidate>> candidateRankings;
        map<string, vector<int>> candidateRoundCountVotes;

};



#endif
