#include <string>
#include <map>
#include "candidate.h"
#include "report.h"
#include <vector>

using namespace std;

Election::Election(){

}

/*
Election(){
    electionType            = "NONE";
    numberOfCandidates      = -1;
    numberOfBallots         = -1;
    numberOfSeats           = -1;
    quota                   = -1;
}
*/
/*
int GetVotesForParty(string party_name);
int SetVotesForParty(string party_name, int num_votes);
int IncrementVotesForParty(string party_name);
int GetNumberOfSeats();
int SetNumberOfSeats(int num);
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
int AddCandidate(Candidate candidate);
int RemoveCandidate(string name);
string FindCandidateToRemove();
int AddBallot(Ballot balllot);
Candidate CheckForMajority();
int RedistributeBallots();
int SetCandidateRoundCountVotesElement(string name, int cout, int vote_num);
int ResolveTie(int num_candidates);



string electionType;
int numberOfCandidates;
int numberOfBallots;
vector<Candidate> candidates;
int numberOfSeats;
int quota;
Report report;
vector<string> parties;
map<string, int> seatsPerPartyWholeNumber;
map<string, int> seatsPerPartyRemainder;
map<string, int> numVotesForParty;
map<string, vector<Candidate>> candidateRankings;
map<string, vector<int>> candidateRoundCountVotes;


*/
