#include "driver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "candidate.h"

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
    return 0;
}

int Driver::ReadInNumberOfBallots(){
    return 0;
}

int Driver::ReadNumberOfSeats(){
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












