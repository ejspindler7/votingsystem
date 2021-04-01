
#include "ballot.h"
#include <string>
#include <vector>
#include <iostream>


Ballot::Ballot(int id){
   this->id = id;
   currentDistribution = 0;
}

void Ballot::SetCurrDis(int dis){
    currentDistribution = dis;
}

void Ballot::SetId(int id){
    this->id = id;
}

void Ballot::AddCandidate(string name){
    candidates.push_back(name);
}

int Ballot::GetCurrDis(){
    return currentDistribution;
}

int Ballot::GetId(){
    return id;
}

int Ballot::GetCandidatesSize(){
    return candidates.size();
}

std::string Ballot::GetCandidateName(int idx){
    return candidates.at(idx);
}

void Ballot::Print(){
    for(int i = 0; i < candidates.size(); i++){
        std::cout << candidates.at(i) << std::endl;
    }
}




