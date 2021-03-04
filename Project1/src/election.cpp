#include <string>
#include <map>
#include "candidate.h"
#include "report.h"
#include <vector>
#include <iostream>

using namespace std;


Election::Election(){
    electionType            = "NONE";
    numberOfCandidates      = -1;
    numberOfBallots         = -1;
    numberOfSeats           = -1;
    quota                   = -1;
    // TODO
}

int Election::GetVotesForParty(string party_name){
    // TODO
    return 0;
}


int Election::SetVotesForParty(string party_name, int num_votes){
    // TODO
    return 0;
}

int Election::IncrementVotesForParty(string party_name){
    return 0;
}

// Gets the number of seats
int Election::GetNumberOfSeats(){
    return numberOfSeats;
}

// Sets the number of seats
int Election::SetNumberOfSeats(int num){
    numberOfSeats = num;
    return 0;
}

// Sets the number of ballots
int Election::SetNumberOfBallots(int num){
    numberOfBallots = num;
    return 0;
}

// Sets election type
int Election::SetElectionType(string type){
    electionType = type;
    return 0;
}

// Sets number of candidates
int Election::SetNumberOfCandidates(int num){
    numberOfCandidates = num;
    return 0;
}

// Gets the quota for OPL
int Election::GetQuota(){
    return quota;
}

// Sets the quota
int Election::SetQuota(int quota){  
    this->quota = quota;
    return 0;
} 

// Gets Election type
string Election::GetElectionType(){
    return electionType;
}

// Gets the number of candidates
int Election::GetNumberOfCandidates(){
    return numberOfCandidates;
}

// Increments the number of candidates by 1
int Election::IncreaseNumberOfCandidates(){
    numberOfCandidates++;
    return 0;
}

// Gets the number of Ballots
int Election::GetNumberOfBallots(){
    return numberOfBallots;
}

// Increments the number of ballots
int Election::IncreaseNumberOfBallots(){
    numberOfBallots++;
    return 0;
}

int Election::AddCandidate(Candidate &candidate){    
    cout << "Added candidate: " << candidate.GetName() << endl; 
    candidates.push_back(candidate);
    return 0; 
}

int Election::RemoveCandidate(string name){
    // TODO
    return 0;
}

string Election::FindCandidateToRemove(){
    // TODO
    return "AASDF";
}
    
int ElectionAddBallot(Ballot balllot){
    // TODO
    return 0;
}
/*
Candidate Election::CheckForMajority(){
    // TODO
    return NULL;
}
*/

int Election::RedistributeBallots(){
    // TODO
    return 0;
}
    
int Election::SetCandidateRoundCountVotesElement(string name, int cout, int vote_num){
    // TODO
    return 0;
}


// Fair coin flip
int Election::ResolveTie(int num_candidates){
    // TODO
    return 0;
}

// Computes election results for IR election
int Election::ComputeIRElection(){
    // TODO
    return 0;
}

// Computes results for OPL election
int Election::ComputeOPLElection(){
    // TODO
    return 0;
}
// Computes election results
int Election::RunElection(){
    // TODO
    return 0;
}

Candidate Election::GetCandidate(int idx){
    return candidates.at(idx);
}



















