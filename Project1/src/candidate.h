#ifndef CANDIDATE_H
#define CANDIDATE_H


#include <string>
#include "ballot.h"

using namespace std;


class Candidate{
    public:
        int SetParty(string party);
        string GetParty();
        string GetName();
        int SetName(string name); 
        int AddBallot(Ballot);
        Ballot RemoveBallot();
        int GetBallotListSize();

    private:
        string party;
        string candidateName;
        vector<Ballot> ballots;

};



#endif
