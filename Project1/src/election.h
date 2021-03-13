#ifndef ELECTION_H
#define ELECTION_H

#include <string>
#include <map>
#include "candidate.h"
#include "report.h"
#include <vector>
#include "ballot.h"

using namespace std;


class Election{
    public:
        Election();
        int GetVotesForParty(string party_name);
        int SetVotesForParties();
        int SetElectionType(string election_type);
        int SetNumberOfCandidates(int num);
        int IncrementVotesForParty(string party_name);
        int GetNumberOfSeats();
        int SetNumberOfSeats(int num);
        int SetNumberOfBallots(int num);
        int GetQuota();
        int SetQuota(int quota);
        string GetElectionType();
        int GetNumberOfCandidates();
        int IncreaseNumberOfCandidates();
        int GetNumberOfBallots();
        int IncreaseNumberOfBallots();
        int RunElection();
        int ComputeIRElection();
        int ComputeOPLElection();
        int AddCandidate(Candidate &candidate);
        int RemoveCandidate(int idx);
        int FindCandidateToRemove();
        int AddParty(string party_name);
        int CheckForMajority();
        int RedistributeBallots(int eliminated_candidate);
        int SetCandidateRoundCountVotesElement(string name, int cout, int vote_num);
        int ResolveTie(int num_candidates);
        int UpdateBallotCurrDis(Ballot *ballot);
        Candidate &GetCandidate(int idx);


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
        map<string, int> finalPartySeats;
        map<string, int> numVotesForParty;
        map<string, vector<int>> winningCandidates;
        map<string, vector<Candidate>> candidateRankings;
        map<string, vector<int>> candidateRoundCountVotes; // Used for reporting

};



#endif
