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
}

int Election::GetVotesForParty(string party_name){
    int total_votes = 0;
    for (int i = 0; i < candidates.size(); i++){
        if (candidates.at(i).GetParty() == party_name){
            total_votes+= candidates.at(i).GetBallotListSize();
        }
    }
    cout << "Party_name: " << party_name <<  "has : " << total_votes<<endl;
    
    return total_votes;
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
    
int Election::AddBallot(Ballot balllot){
    // TODO
    return 0;
}

int Election::AddParty(string party_name){
    bool party_already_exists = false;

    for(int i = 0; i < parties.size(); i++){
        if (party_name == parties.at(i)){
            party_already_exists = true;
            break;
        }
    }
    
    if (!party_already_exists){
        parties.push_back(party_name);
    }
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
    // Iterate through parties and get their total votes

    for (int i = 0; i < parties.size(); i++){
        int total_party_votes = GetVotesForParty(parties.at(i)); 
        int whole_num_seats = total_party_votes / quota;
        seatsPerPartyWholeNumber[parties.at(i)] = whole_num_seats;
    }

    return 0;
}
// Computes election results
int Election::RunElection(){
    if (electionType == "OPL"){
        quota = numberOfBallots / numberOfSeats;
        ComputeOPLElection();
    }
    else if (electionType == "IR"){
        cout << "IR-> " << quota << endl;
        ComputeIRElection(); 
    }
    else{
        cout << "Didn't recognize election type." << endl;        
    }
    return 0;
}

Candidate& Election::GetCandidate(int idx){
    return candidates.at(idx);
}



















