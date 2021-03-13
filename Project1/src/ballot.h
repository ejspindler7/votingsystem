#ifndef BALLOT_H
#define BALLOT_H


#include <string>
#include <vector>

using namespace std;


class Ballot{
    public:
        Ballot(int id);
        void SetCurrDis(int dis);        
        void SetId(int id);
        void AddCandidate(string name);
        int GetCurrDis();
        int GetId();
        void Print();
        int GetCandidatesSize();
        string GetCandidateName(int idx);
    private:
        int currentDistribution;
        int id;
        vector<string> candidates;
};



#endif
