
#include "ballot.h"
#include <string>
#include <vector>
#include <iostream>

// Creates a Ballot
Ballot::Ballot(int id){
   this->id = id;
   currentDistribution = 0;
}

// Updates the current distribution of the ballot
void Ballot::SetCurrDis(int dis){
    currentDistribution = dis;
}

// Updates the ballot's id
void Ballot::SetId(int id){
    this->id = id;
}

// Assignes a candidate to the ballot
void Ballot::AddCandidate(string name){
    candidates.push_back(name);
}

// Retrieves the current distribution of the ballot
int Ballot::GetCurrDis(){
    return currentDistribution;
}

// Retrieves the current id of the ballot
int Ballot::GetId(){
    return id;
}

// Retrieves how many candidates the ballot voted for
int Ballot::GetCandidatesSize(){
    return candidates.size();
}

// Retrieves the candidate's name at the provided index the ballot voted for
std::string Ballot::GetCandidateName(int idx){
    return candidates.at(idx);
}

// Prints information about the ballot, used for debugging
void Ballot::Print(){
    for(int i = 0; i < candidates.size(); i++){
        std::cout << candidates.at(i) << std::endl;
    }
}
