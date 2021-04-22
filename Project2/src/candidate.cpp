

#include <string>
#include "ballot.h"
#include <iostream>
#include "candidate.h"

using namespace std;

// Creates a Candidate
Candidate::Candidate(string name, string party){
   candidateName = name; 
   this->party = party;
}

// Updates the party the candidate is affiliated with
int Candidate::SetParty(string party){
    this->party = party;
    return 0;
}

// Retrieves the party the candidate is affiliated with
string Candidate::GetParty(){
    return party;
}

// Retrieves the candidate's name
string Candidate::GetName(){
    return candidateName;
}

// Updates the candidate's name with the provided name
int Candidate::SetName(string name){
    candidateName = name;
    return 0;
}

// Assignes a bllot to the candidate (the ballot voted for that candidate)
int Candidate::AddBallot(Ballot *ballot){
    this->ballots.push_back(ballot);    
    return 0;    
}

// Removes the first ballot from the candidate's list
Ballot* Candidate::RemoveBallot(){
    if (ballots.size() == 0){ // No candidates to remove
        return NULL;
    }
    Ballot* tmp = ballots.front();
    ballots.erase(ballots.begin());
    return tmp;
}

// Retrieves how many ballots voted for that specific candidate
int Candidate::GetBallotListSize(){
    return this->ballots.size();
}




