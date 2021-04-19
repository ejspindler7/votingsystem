#include "driver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "candidate.h"
#include "ballot.h"
#include <assert.h>
#include <map>
#include <stdio.h>
#include <cmath>


Driver::Driver(std::vector<std::string> files){
    // Used to combine all balltos into one file
    ballotFileName = "ballotfile.csv";
    remove(ballotFileName.c_str());

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

// Reads in the election type and sets it 
int Driver::ReadInElectionType(std::ifstream *fh, int flag){
    std::vector<std::string> words;
    std::string tmp = ""; 
    if (*fh){
        getline(*fh, tmp);
        if (!flag){
            election.SetElectionType(tmp);
        }
    }
    else{
        std::cout << "File Handle is not open for Election Type." << std::endl;
    }
    
    return 0;
}

// Checks if IR ballot is valid
bool Driver::CheckIfIRBallotValid(Ballot* ballot){
    int minValidNum =std::ceil(((double) election.GetNumberOfCandidates()) / 2);
    return ((ballot->GetCandidatesSize()) >= minValidNum );
}

//Reads in the the number of candidates and Sets the number of Candidates
int Driver::ReadInNumCandidates(std::ifstream *fh, int flag){
    int num_candidates = -1;
    std::string input = "";
    getline(*fh, input);
    if (flag){
        // Already read in candidates
        return 0;
    }
    if (*fh){
        num_candidates = std::stoi(input); 
        election.SetNumberOfCandidates(num_candidates);   
    }
    return 0;
}

// Parses and creates candidates from CSV file
int Driver::ReadInCandidates(std::ifstream *fh, int flag){
    std::string tmp = "";
    getline(*fh, tmp);

    if (flag){
        // Already read in candidates
        return 0;
    }

    if (election.GetElectionType() == "OPL" || election.GetElectionType() == "PO"){
        std::vector<std::string> candidates; 
        if (*fh){
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
        if (*fh){
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
    // case for if election type is invalid
    else{
        std::cout << "Did not recognize election type: " << election.GetElectionType() << endl;
        return -1;
    }
    
    return 0;
}
//reads in ballots in accordance to election type
int Driver::ReadInBallots(){
    string ballDistribution = " ==== Ballot Distribution ====";
    election.WriteLineToAudit(ballDistribution);
    std::string line;
    std::vector<std::string> votes;
    int ballot_id = 1;
    ballotFileCompleted.open(ballotFileName);
    if (ballotFileCompleted.is_open()){
        while(getline(ballotFileCompleted, line)){
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
                        string data = "Ballot Id: " + to_string(ballot->GetId()) + " goes to " + 
                            election.GetCandidate(vote_map[0]).GetName();
                        election.WriteLineToAudit(data);
                    }
                    // Update candidate list
                    ballot->AddCandidate(election.GetCandidate(vote_map[mapped.at(i)]).GetName());
                }
                // Checks for valid ballot
                if (CheckIfIRBallotValid(ballot)){
                    // Skip ballot because it is invalid
                    (election.GetCandidate(vote_map[0])).AddBallot(ballot);
                }else{
                    std::cout << "Invalid ballot " << ballot_id << std::endl;
                }

                votes.clear();

            }
            else if ( election.GetElectionType() == "PO"){
                int candidate_idx = this->GetOPLVote(line);
                ballot->AddCandidate((election.GetCandidate(candidate_idx)).GetName());
                (election.GetCandidate(candidate_idx)).AddBallot(ballot);
                string data = "Ballot: " + to_string(ballot->GetId()) + " goes towards " 
                    + election.GetCandidate(candidate_idx).GetName() + " (" 
                    + election.GetCandidate(candidate_idx).GetParty() + ")";
                election.WriteLineToAudit(data);
                // Used to prove info was read in properly.
                std::cout << data << std::endl;

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


int Driver::AppendToBallotFile(std::ifstream *fh, int numBallots){
    ballotFile.open(ballotFileName, std::ios_base::app);
    std::string tmp;
    getline(*fh, tmp);
    
    for (int i = 0; i < numBallots; i++){
        ballotFile <<tmp + "\n";
        tmp = "";
        getline(*fh, tmp);
    }
    ballotFile.close();
    return 0;
}

int Driver::ReadInNumberOfBallots(std::ifstream *fh, int flag){
    int num_ballots= -1;
    std::string input = "";
    getline(*fh, input);
    if (flag){
        // Already read in number of ballots
        return 0;
    }
    //Sets the number of Ballots in election
    if (*fh){
        num_ballots= std::stoi(input);    
        election.SetNumberOfBallots(num_ballots);
    }
    return 0;
}

int Driver::ReadInNumberOfSeats(std::ifstream *fh, int flag){
    int num_seats= -1;
    std::string input = "";
    getline(*fh, input);
    if (flag){
        // Already read in number of seats.
        return 0;
    }
    //Sets the number of Seats in the Election
    if (*fh){
        num_seats= std::stoi(input);    
        election.SetNumberOfSeats(num_seats);

    }

    return 0;
}

int Driver::ProcessCSV(){
    int num_candidates = 0;

    //gets information for each election using helper functions
    for (int i = 0; i < fileHandles.size(); i++){
        ReadInElectionType(fileHandles.at(i), i);    
        ReadInNumCandidates(fileHandles.at(i), i);
        ReadInCandidates(fileHandles.at(i), i);
        

        
        if (election.GetElectionType() == "OPL"){
            ReadInNumberOfSeats(fileHandles.at(i), i);
            ReadInNumberOfBallots(fileHandles.at(i), i);
        }
       
        else if (election.GetElectionType() == "IR" || election.GetElectionType() == "PO"){
            ReadInNumberOfBallots(fileHandles.at(i), i);
        }
        
        else{
            std::cout << "Election type not recognized." << std::endl;
        }
        AppendToBallotFile(fileHandles.at(i), election.GetNumberOfBallots());
        
 
    }

    // Loads ballots into memory
    ReadInBallots();


    // ====== Reporting ======
    // Election Type
    string line = "Compute " + election.GetElectionType() + " election.";
    election.WriteLineToAudit(line);
    election.WriteLineToMedia(line);
    cout << line << endl;
    
    // Number of Candidates
    line = "Number of candidates: " + to_string(election.GetNumberOfCandidates());
    election.WriteLineToAudit(line);
    election.WriteLineToMedia(line);
    cout << line << endl;

    if (election.GetElectionType() == "OPL"){
        // Number of Seats
        line = "Number of seats: " + to_string(election.GetNumberOfSeats());
        cout << line << endl;
        election.WriteLineToAudit(line);
        election.WriteLineToMedia(line);
    }
    
    // Number of Ballots
    line = "Number of ballots: " + to_string(election.GetNumberOfBallots());
    cout << line << endl;
    election.WriteLineToAudit(line);
    election.WriteLineToMedia(line);

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

int Driver::GetNumInputFiles(){
    return fileHandles.size();
}










