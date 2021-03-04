#include "driver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "candidate.h"
#include "ballot.h"

Driver::Driver(std::string file){
    fileName = file;
    fileHandle.open(fileName);
}

int Driver::ReadInElectionType(){
    std::vector<std::string> words;
    std::string tmp; 
    if (fileHandle.is_open()){
        getline(fileHandle, tmp);
        election.SetElectionType(tmp);
        
        std::cout << election.GetElectionType() << std::endl;
    }
    else{
        std::cout << "File Handle is not open for Election Type." << std::endl;
    }
    
    return 0;
}

int Driver::ReadInNumCandidates(){
    int num_candidates = -1;
    std::string input;

    if (fileHandle.is_open()){
        getline(fileHandle, input);
        num_candidates = std::stoi(input);    
        election.SetNumberOfCandidates(num_candidates);
        std::cout << "Num candidates: " << num_candidates << std::endl;
    }
        

    return 0;
}

// Parses and creates candidates from CSV file
int Driver::ReadInCandidates(){
    if (election.GetElectionType() == "OPL"){
        std::cout << "READING in candidates for OPL " << std::endl;
        std::vector<std::string> candidates; 
        if (fileHandle.is_open()){
            std::string tmp;
            getline(fileHandle, tmp);
            ParseLine(tmp, candidates, ',');
            // Removefs '[' or ']' from word.
            for (int i = 0; i < candidates.size(); i++){
                candidates.at(i).erase(remove(candidates.at(i).begin(), candidates.at(i).end(), '['), candidates.at(i).end());
                candidates.at(i).erase(remove(candidates.at(i).begin(), candidates.at(i).end(), ']'), candidates.at(i).end());
            }

            std::string name;
            std::string party;
            // Adding candidates to election
            for(int i = 0; i < candidates.size(); i++){
                if (i % 2 == 1){
                    party = candidates.at(i);
                    std::cout << "Adding Candidates: " << name << "(" << party << ")" << std::endl;
                    Candidate* candidate = new Candidate(name, party);
                    election.AddCandidate(*candidate);
                }
                else{
                    name = candidates.at(i);
                }
            }

            // Prints out the candidates
            for(int i = 0; i < candidates.size(); i++){
                std::cout<< candidates.at(i) << std::endl;
            }
        }
        else{
            std::cout << "File handle is not open." << std::endl;
        }
        
    }
    else if (election.GetElectionType() == "IR"){
        std::cout << "Reading candidates for IR" << std::endl;
        std::vector<std::string> candidates; 
        if (fileHandle.is_open()){
            std::string tmp;
            getline(fileHandle, tmp);
            ParseLine(tmp, candidates, ',');
            // Adds candidate to election
            for(int i = 0; i < candidates.size(); i++){
                std::vector<std::string> parts;
                ParseLine(candidates.at(i), parts, '(');
                parts.at(1).erase(remove(parts.at(1).begin(), parts.at(1).end(), ')'), parts.at(1).end());
                std::cout << "Adding Candidates: " << parts.at(0) << "(" << parts.at(1)<< ")" << std::endl;
                Candidate* candidate = new Candidate(parts.at(0), parts.at(1));
                election.AddCandidate(*candidate);
            }



            // Prints out the candidates
            for(int i = 0; i < candidates.size(); i++){
                std::cout<< candidates.at(i) << std::endl;
            }
        }
    }
    else{
        std::cout << "Did not recognize election type: " << election.GetElectionType() << endl;
        return -1;
    }
    return 0;
}

int Driver::ReadInBallots(){
    std::string line;
    std::vector<std::string> votes;
    int ballot_id = 1;
    if (fileHandle.is_open()){
        while(getline(fileHandle, line)){
            Ballot* ballot = new Ballot(ballot_id);
            if (election.GetElectionType() == "OPL"){
                int candidate_idx = this->GetOPLVote(line);
                ballot->AddCandidate((election.GetCandidate(candidate_idx)).GetName());
                (election.GetCandidate(candidate_idx)).AddBallot(ballot);

            }
            else if (election.GetElectionType() == "IR"){
                ParseLine(line, votes, ',');
                // Adds candidates to ballot file
                for(int i = 0; i < votes.size(); i++){
                    ballot->AddCandidate((election.GetCandidate(std::stoi(votes.at(i))).GetName()));
                }
                //ballot->Print();


            }
            else{
                std::cout << "Did not recognize election type." << std::endl;
                exit(1);
            }
            ballot_id++;
        }
    }
    else{
        std::cout << "FIle not open." << std::endl;
        return -1;
    }
    return 0;
}

int Driver::ReadInNumberOfBallots(){
    int num_ballots= -1;
    std::string input;

    if (fileHandle.is_open()){
        getline(fileHandle, input);
        num_ballots= std::stoi(input);    
        election.SetNumberOfBallots(num_ballots);
        std::cout << "Num ballots: " << num_ballots<< std::endl;
    }
    return 0;
}

int Driver::ReadInNumberOfSeats(){
    int num_seats= -1;
    std::string input;

    if (fileHandle.is_open()){
        getline(fileHandle, input);
        num_seats= std::stoi(input);    
        election.SetNumberOfSeats(num_seats);
        std::cout << "Num seats: " << num_seats<< std::endl;
    }

    return 0;
}

int Driver::SetFileName(std::string name){
       fileName = name; 
       return 0;
}

std::string Driver::GetFileName(){
    return fileName;
}

int Driver::ProcessCSV(){
    ReadInElectionType();   
    ReadInNumCandidates();
    ReadInCandidates();
    if (election.GetElectionType() == "OPL"){
        ReadInNumberOfSeats();
        ReadInNumberOfBallots();
    }
    else if (election.GetElectionType() == "IR"){
        ReadInNumberOfBallots();
    }
    else{
        std::cout << "Election type not recognized." << std::endl;
    }
    ReadInBallots();
    return 0;
}

// Got the parsing from
//https://www.tutorialspoint.com/How-to-read-and-parse-CSV-files-in-Cplusplus
// https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
void Driver::ParseLine(std::string line, std::vector<std::string> &words, char delim){
    std::stringstream s_tmp(line); 
    std::string tmp;

    // Iterate through line, deliminating by ','
    while(std::getline(s_tmp, tmp, delim)){
       tmp.erase(remove(tmp.begin(), tmp.end(), ' '), tmp.end());
       words.push_back(tmp);
    }
    return;
}

int Driver::GetOPLVote(std::string line){
    for(int i = 0; i < line.size(); i++){
        if(line.at(i) == '1'){
            return i;
         }
    }
    return -1;
}












