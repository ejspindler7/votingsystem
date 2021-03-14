

#include <string>
#include "ballot.h"
#include <iostream>
#include "candidate.h"

using namespace std;


Candidate::Candidate(string name, string party){
   candidateName = name; 
   this->party = party;
}


int Candidate::SetParty(string party){
    this->party = party;
    return 0;
}

string Candidate::GetParty(){
    return party;
}

string Candidate::GetName(){
    return candidateName;
}


int Candidate::SetName(string name){
    candidateName = name;
    return 0;
}
int Candidate::AddBallot(Ballot *ballot){
    this->ballots.push_back(ballot);    
    return 0;    
}
Ballot* Candidate::RemoveBallot(){
    if (ballots.size() == 0){
        return NULL;
    }
    Ballot* tmp = ballots.front();
    ballots.erase(ballots.begin());
    return tmp;
}

int Candidate::GetBallotListSize(){
    return this->ballots.size();
}




