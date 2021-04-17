#include "driver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "candidate.h"
#include "ballot.h"
#include <assert.h>
#include <map>

Driver::Driver(std::vector<std::string> files){
    // Primes ifstream pointers        
    for (int i = 0; i < files.size(); i++){
        fileHandles.push_back(new std::ifstream);
    }

    // Opens all CSV files
    for (int i = 0; i < files.size(); i++){
        fileHandles.at(i)->open(files.at(i));
        if (!fileHandles.at(i)->is_open()){
            std::cout << "File not valid. " << files.at(i) << std::endl;
            exit(0);
        }
    }
  
}


int Driver::ReadInElectionType(std::ifstream *fh, int flag){
    std::vector<std::string> words;
    std::string tmp; 
    if (*fh){
        if (!flag){
            getline(*fh, tmp);
            election.SetElectionType(tmp);

            string line = "Compute " + tmp + " election.";
            election.WriteLineToAudit(line);
            election.WriteLineToMedia(line);
            cout << line << endl;
        }
    }
    else{
        std::cout << "File Handle is not open for Election Type." << std::endl;
    }
    
    return 0;
}

/*
int Driver::ReadInNumCandidates(){
    int num_candidates = -1;
    std::string input;

    if (fileHandle.is_open()){
        getline(fileHandle, input);
        num_candidates = std::stoi(input);    
        election.SetNumberOfCandidates(num_candidates);
        
        string line = "Number of candidates: " + to_string(num_candidates);
        election.WriteLineToAudit(line);
        election.WriteLineToMedia(line);
        cout << line << endl;
    }
        

    return 0;
}

// Parses and creates candidates from CSV file
int Driver::ReadInCandidates(){
    if (election.GetElectionType() == "OPL"){
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
                    election.AddParty(party);
                    Candidate* candidate = new Candidate(name, party);
                    election.AddCandidate(*candidate);
                }
                else{
                    name = candidates.at(i);
                }
            }

        }
        else{
            std::cout << "File handle is not open." << std::endl;
        }
        
    }
    else if (election.GetElectionType() == "IR"){
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
                Candidate* candidate = new Candidate(parts.at(0), parts.at(1));
                election.AddCandidate(*candidate);
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
    string ballDistribution = " === Ballot Distribution ====";
    election.WriteLineToAudit(ballDistribution);
    std::string line;
    std::vector<std::string> votes;
    int ballot_id = 1;
    if (fileHandle.is_open()){
        while(getline(fileHandle, line)){
            Ballot* ballot = new Ballot(ballot_id);
            if (line == ""){
                break;
            }
            if (election.GetElectionType() == "OPL"){
                int candidate_idx = this->GetOPLVote(line);
                ballot->AddCandidate((election.GetCandidate(candidate_idx)).GetName());
                (election.GetCandidate(candidate_idx)).AddBallot(ballot);
                string data = "Ballot: " + to_string(ballot->GetId()) + " goes towards " 
                    + election.GetCandidate(candidate_idx).GetName() + " (" 
                    + election.GetCandidate(candidate_idx).GetParty() + ")";
                election.WriteLineToAudit(data);

                // OPL REPORT HERE

            }
            else if (election.GetElectionType() == "IR"){
                std::map<int, int> vote_map;
                std::vector<int> mapped;
                bool setFirstCandidate = false;
                int firstCandidate;
                ParseLine2(line, votes, ',');

                for (int pos = 0; pos < votes.size(); pos++){
                    if (votes.at(pos) != ""){
                        int choice = (std::stoi(votes.at(pos))) - 1;
                        mapped.push_back(choice);
                        vote_map[choice] = pos;
                    }
                }
              
                // Sorts vector
                if (mapped.size() > 0){
                    sort(mapped.begin(), mapped.end());
                }

                for (int i = 0; i < mapped.size(); i++){
                    if (mapped.at(i) == 0){
                        // Add ballot to first choice candidate 
                        (election.GetCandidate(vote_map[0])).AddBallot(ballot);
                        string data = "Ballot Id: " + to_string(ballot->GetId()) + " goes to " + 
                            election.GetCandidate(vote_map[0]).GetName();
                        election.WriteLineToAudit(data);
                    }
                    // Update candidate list
                    ballot->AddCandidate(election.GetCandidate(vote_map[mapped.at(i)]).GetName());
                }

                votes.clear();

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
        string line = "Number of ballots: " + to_string(num_ballots);
        cout << line << endl;
        election.WriteLineToAudit(line);
        election.WriteLineToMedia(line);

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
        string line = "Number of seats: " + to_string(num_seats);
        cout << line << endl;
        election.WriteLineToAudit(line);
        election.WriteLineToMedia(line);
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
*/
int Driver::ProcessCSV(){
    for (int i = 0; i < fileHandles.size(); i++){
        ReadInElectionType(fileHandles.at(i), i);   
        /*
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
        */
    }
    std::cout << election.GetElectionType() << std::endl;
    return 0;
}
/*
// Got the parsing from
//https://www.tutorialspoint.com/How-to-read-and-parse-CSV-files-in-Cplusplus
// https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
void Driver::ParseLine(std::string line, std::vector<std::string> &words, char delim){
    std::stringstream s_tmp(line); 
    std::string tmp;

    // Iterate through line, deliminating by ','
    while(std::getline(s_tmp, tmp, delim)){
       tmp.erase(remove(tmp.begin(), tmp.end(), ' '), tmp.end());
       if (!tmp.empty()){
           words.push_back(tmp);
       }
    }
    
    return;
}

void Driver::ParseLine2(std::string line, std::vector<std::string> &words, char delim){
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

int Driver::ComputeElection(){
    election.RunElection();
    election.CloseReports();
    return 0;
}


*/







