#include <string>
#include <map>
#include "candidate.h"
#include "report.h"
#include <vector>

using namespace std;


Election::Election(){
    electionType            = "NONE";
    numberOfCandidates      = -1;
    numberOfBallots         = -1;
    numberOfSeats           = -1;
    quota                   = -1;
}

int Election::GetVotesForParty(string party_name){
    return 0;
}


int Election::SetVotesForParty(string party_name, int num_votes){
    return 0;
}

int Election::IncrementVotesForParty(string party_name){
    return 0;
}
int Election::GetNumberOfSeats(){
    return 0;
}

int Election::SetNumberOfSeats(int num){
    return 0;
}

int Election::GetQuota(){
    return 0;
}

int Election::SetQuota(int quota){  
    return 0;
} 

string Election::GetElectionType(){
    return "BLaah";
}

int Election::GetNumberOfCandidates(){
    return 0;
}

int Election::IncreaseNumberOfCandidates(){
    return 0;
}

int Election::GetNumberOfBallots(){
    return 0;
}

int Election::IncreaseNumberOfBallots(){
    return 0;
}

int Election::RunElection(){
    return 0;
}

int Election::ComputeIRElection(){
    return 0;
}

int Election::ComputeOPLElection(){
    return 0;
}

int Election::AddCandidate(Candidate candidate){    
    return 0; 
}

int Election::RemoveCandidate(string name){
    return 0;
}

string Election::FindCandidateToRemove(){
    return "AASDF";
}
    
int ElectionAddBallot(Ballot balllot){
    return 0;
}
/*
Candidate Election::CheckForMajority(){
    return NULL;
}
*/

int Election::RedistributeBallots(){
    return 0;
}
    
int Election::SetCandidateRoundCountVotesElement(string name, int cout, int vote_num){
    return 0;
}

int Election::ResolveTie(int num_candidates){
    return 0;
}






















