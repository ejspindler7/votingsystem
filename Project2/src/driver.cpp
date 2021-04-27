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

// Creates a driver for the election
Driver::Driver(std::vector<std::string> files){
    // Used to combine all ballots into one file
    ballotFileName = "ballotfile.csv";
    remove(ballotFileName.c_str());      // Removes ballotfile.csv if it already exists

    // Primes ifstream pointers        
    for (int i = 0; i < files.size(); i++){
        fileHandles.push_back(new std::ifstream);
    }

    // Opens all CSV files
    for (int i = 0; i < files.size(); i++){ // Iterates through all provided files
        fileHandles.at(i)->open(files.at(i));
        if (!fileHandles.at(i)->is_open()){ // Ensures all files open properly, otherwise, error out
            std::cout << "File not valid. " << files.at(i) << std::endl;
            exit(0);
        }
    }
  
}

// Reads in the election type
int Driver::ReadInElectionType(std::ifstream *fh, int flag){
    std::vector<std::string> words;
    std::string tmp = ""; 
    if (fh){
        getline(*fh, tmp);                  // Reads line from CSV file
        if (!flag){                         // Already read in the election type
            election.SetElectionType(tmp);  // Updates the election type
        }
    }
    else{
        std::cout << "File Handle is not open for Election Type." << std::endl;
    }
    
    return 0;
}

// Checks if IR ballot ranked the required number of candidates
bool Driver::CheckIfIRBallotValid(Ballot* ballot){
    int minValidNum =std::ceil(((double) election.GetNumberOfCandidates()) / 2);
    return ((ballot->GetCandidatesSize()) >= minValidNum ); // Bool indicating if the ballot properly ranked the required number of candidates
}

// Reads in the number of candidates from the csv file
int Driver::ReadInNumCandidates(std::ifstream *fh, int flag){
    int num_candidates = -1;
    std::string input = "";
	getline(*fh, input);    // Reads line from CSv file
    if (flag){
        return 0;  // Already read in candidates
    }
    if (fh){
        num_candidates = std::stoi(input);             // Converts the sting to an int
        election.SetNumberOfCandidates(num_candidates);// Updates the number of candidates in the election
    }
    return 0;
}

// Parses and creates candidates from CSV file
int Driver::ReadInCandidates(std::ifstream *fh, int flag){
    std::string tmp = "";
    getline(*fh, tmp); // Reads line from CSV file


    if (flag){ 
        return 0; // Already read in candidates
    }

    if (election.GetElectionType() == "OPL" || election.GetElectionType() == "PO"){ // Determines if the election type is OPL or PO
        std::vector<std::string> candidates; 
        if (*fh){ // Ensures file is opened properly
            ParseLine(tmp, candidates, ','); // Parses line into candidates with delimeter ','
            // Removefs '[' or ']' from word.   
            for (int i = 0; i < candidates.size(); i++){    // Iterates throughout the line removing unnecessary characters
                candidates.at(i).erase(remove(candidates.at(i).begin(), candidates.at(i).end(), '['), candidates.at(i).end());
                candidates.at(i).erase(remove(candidates.at(i).begin(), candidates.at(i).end(), ']'), candidates.at(i).end());
            }

            std::string name;
            std::string party;
            // Adding candidates to election
            for(int i = 0; i < candidates.size(); i++){ // Iterates throgh parsed line
                if (i % 2 == 1){    // Determines if current work is the party or name of candidate
                    party = candidates.at(i);
                    election.AddParty(party);                          // Adds the candidate's party to election if it is not present already
                    Candidate* candidate = new Candidate(name, party); // Creates a new candidate
                    election.AddCandidate(*candidate);                 // Adds new candidate to election
                }
                else{
                    name = candidates.at(i);    // Updates candidates name
                }
            }

        }
        else{
            std::cout << "File handle is not open." << std::endl;
        }
        
    }
    else if (election.GetElectionType() == "IR"){ // Election type is IR
        std::vector<std::string> candidates; 
        if (*fh){
            ParseLine(tmp, candidates, ',');   // Parses line into candidates with delimeter ',' 
            // Adds candidate to election
            for(int i = 0; i < candidates.size(); i++){ // Iterates candidate information
                std::vector<std::string> parts;         // Book keeping, creating candidate
                ParseLine(candidates.at(i), parts, '(');
                parts.at(1).erase(remove(parts.at(1).begin(), parts.at(1).end(), ')'), parts.at(1).end());
                Candidate* candidate = new Candidate(parts.at(0), parts.at(1));
                election.AddCandidate(*candidate);  // Adds the candidate to the election
            }
        }
    }
    else{
        std::cout << "Did not recognize election type: " << election.GetElectionType() << endl;
        return -1;
    }
    return 0;
}

// Loads ballots from ballot file into memroy (Joins multiple files into one big CSV and then process the combined CSV ballot file)
int Driver::ReadInBallots(){
    string ballDistribution = " ==== Ballot Distribution ====";
    election.WriteLineToAudit(ballDistribution); // Writes to audit file
    std::string line;
    std::vector<std::string> votes;
    int ballot_id = 1;
    ballotFileCompleted.open(ballotFileName);       // Opens combined ballotfile to apppend to 
    if (ballotFileCompleted.is_open()){             // Ensures the combined ballotfile is open
        while(getline(ballotFileCompleted, line)){  // Reads line from combined ballot file
            Ballot* ballot = new Ballot(ballot_id); // Creates new ballot
            if (line == ""){ // Reached EOF?
                break;
            }
            if (election.GetElectionType() == "OPL"){                                  // Election type is OPL
                int candidate_idx = this->GetOPLVote(line);                            // Gets the candidate index from the vote
                ballot->AddCandidate((election.GetCandidate(candidate_idx)).GetName());// Adds candidate to the ballot
                (election.GetCandidate(candidate_idx)).AddBallot(ballot);              // Adds ballot to candidate
                string data = "Ballot: " + to_string(ballot->GetId()) + " goes towards " 
                    + election.GetCandidate(candidate_idx).GetName() + " (" 
                    + election.GetCandidate(candidate_idx).GetParty() + ")";
                election.WriteLineToAudit(data);                                        // Writes data to audit file
            }
            else if (election.GetElectionType() == "IR"){               // Election type is IR
                std::map<int, int> vote_map;
                std::vector<int> mapped;
                bool setFirstCandidate = false;
                int firstCandidate;
                ParseLine2(line, votes, ',');                           // Parses line by ',' and stores in 'votes'

                for (int pos = 0; pos < votes.size(); pos++){           // Iterates through the members of 'votes'
                    if (votes.at(pos) != ""){                               // Ensures the current votes is not empty
                        int choice = (std::stoi(votes.at(pos))) - 1;        // Calculates who the vote was for
                        mapped.push_back(choice);                           // Adds the choice to the mapping which tracks votes
                        vote_map[choice] = pos;
                    }
                }
              
                // Sorts vector
                if (mapped.size() > 0){
                    sort(mapped.begin(), mapped.end());
                }

                for (int i = 0; i < mapped.size(); i++){ // Iterates through all mappings
                    if (mapped.at(i) == 0){
                        string data = "Ballot Id: " + to_string(ballot->GetId()) + " goes to " + 
                            election.GetCandidate(vote_map[0]).GetName();
                        election.WriteLineToAudit(data);        // Writes data to audit file
                    }
                    // Update candidate list
                    ballot->AddCandidate(election.GetCandidate(vote_map[mapped.at(i)]).GetName()); // Adds candidate to the ballot
                }
                // Checks for valid ballot
                if (CheckIfIRBallotValid(ballot)){
                    // Skip ballot because it is invalid
                    (election.GetCandidate(vote_map[0])).AddBallot(ballot);
                }else{
                    std::cout << "Invalid ballot " << ballot_id << std::endl;
                }

                votes.clear(); // Flush vote for next iteration

            }
            else if ( election.GetElectionType() == "PO"){                               // Election type is PO
                int candidate_idx = this->GetOPLVote(line);
                ballot->AddCandidate((election.GetCandidate(candidate_idx)).GetName());  // Adds candidate to ballot
                (election.GetCandidate(candidate_idx)).AddBallot(ballot);                // Adds ballot to candidate
                string data = "Ballot: " + to_string(ballot->GetId()) + " goes towards " 
                    + election.GetCandidate(candidate_idx).GetName() + " (" 
                    + election.GetCandidate(candidate_idx).GetParty() + ")";
                election.WriteLineToAudit(data);                                          // Writes data to audit file
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

// Appends the ballot CSV file to a combined ballotfile.csv
int Driver::AppendToBallotFile(std::ifstream *fh, int numBallots){
    ballotFile.open(ballotFileName, std::ios_base::app); // Opens the combined ballotfile.csv
    std::string tmp;
    getline(*fh, tmp);  // Reads line from ballot file to append to ballotfile
    
    for (int i = 0; i < numBallots; i++){   // Iterates through all ballots in the provided ballot file (fh)
        ballotFile <<tmp + "\n";                // Writes line to the combined ballotfile.csv
        tmp = "";
        getline(*fh, tmp);                      // Reads next line from the provieded ballot file (fh)
    }
    ballotFile.close();                     // Saves the combined ballotfile.csv 
    return 0;
}

// Reads in the number of ballots from the CSV ballot file, fh
int Driver::ReadInNumberOfBallots(std::ifstream *fh, int flag){
    int num_ballots= -1;
    std::string input = "";
    getline(*fh, input);    // Reals line from CSV ballot file
    if (flag){ 
        return 0;   // Already read in number of ballots
    }
    if (*fh){
        num_ballots= std::stoi(input);            // Converts number of ballots to an int
        election.SetNumberOfBallots(num_ballots); // Updates the number of ballots in the election 
    }
    return 0;
}

// Reads in the number of seats from the CSV ballot file, fh
int Driver::ReadInNumberOfSeats(std::ifstream *fh, int flag){
    int num_seats= -1;
    std::string input = "";
    getline(*fh, input); // Reads line from CSV ballot file
    if (flag){ 
        return 0;  // Already read in number of seats.
    }
    if (*fh){
        num_seats= std::stoi(input);          // Converts number of seats to an int
        election.SetNumberOfSeats(num_seats); // Updates the number of seats in the election

    }
    return 0;
}

// Loads data from ballot files into memory 
int Driver::ProcessCSV(){
    int num_candidates = 0;
    for (int i = 0; i < fileHandles.size(); i++){   // Iterates through all provided files and loads them into memroy
        ReadInElectionType(fileHandles.at(i), i);       // Reads in the election type
        ReadInNumCandidates(fileHandles.at(i), i);      // Reads in the number of candidates
        ReadInCandidates(fileHandles.at(i), i);         // Reads in the candidates
        

        
        if (election.GetElectionType() == "OPL"){   // Election type is OPL
            ReadInNumberOfSeats(fileHandles.at(i), i);  // Reads in the number of seats
            ReadInNumberOfBallots(fileHandles.at(i), i);// Reads in the number of ballots
        }
       
        else if (election.GetElectionType() == "IR" || election.GetElectionType() == "PO"){ // Election type is IR or PO
            ReadInNumberOfBallots(fileHandles.at(i), i);    // Reads in the number of ballots
        }
        
        else{
            std::cout << "Election type not recognized." << std::endl;
        }
        AppendToBallotFile(fileHandles.at(i), election.GetNumberOfBallots());  // Adds the ballot file data to the combined ballotfile.csv
    }

    // Loads ballots into memory
    ReadInBallots();     // Reads in all ballots from ballotfile.csv


    // ====== Reporting ======
    // Election Type
    string line = "Compute " + election.GetElectionType() + " election.";
    election.WriteLineToAudit(line); // Writes line to audit file
    election.WriteLineToMedia(line); // Writes line to media file
    cout << line << endl;            // Writes line to stdout
    
    // Number of Candidates
    line = "Number of candidates: " + to_string(election.GetNumberOfCandidates());
    election.WriteLineToAudit(line); // Writes line to audit file
    election.WriteLineToMedia(line); // Writes line to media file
    cout << line << endl;            // Writes line to stdout

    if (election.GetElectionType() == "OPL"){ // Election type is OPL
        // Number of Seats
        line = "Number of seats: " + to_string(election.GetNumberOfSeats());
        election.WriteLineToAudit(line); // Writes line to audit file
        election.WriteLineToMedia(line); // Writes line to media file
        cout << line << endl;            // Writes line to stdout
    }
    
    // Number of Ballots
    line = "Number of ballots: " + to_string(election.GetNumberOfBallots());
    election.WriteLineToAudit(line); // Write line to audit file
    election.WriteLineToMedia(line); // Write line to media file
    cout << line << endl;            // Write line to stdout

    return 0;
}

// Got the parsing from
//https://www.tutorialspoint.com/How-to-read-and-parse-CSV-files-in-Cplusplus
// https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/

// Parses line by delim and stores into words
void Driver::ParseLine(std::string line, std::vector<std::string> &words, char delim){
    std::stringstream s_tmp(line); 
    std::string tmp;

    // Iterate through line, deliminating by ','
    while(std::getline(s_tmp, tmp, delim)){                       
       tmp.erase(remove(tmp.begin(), tmp.end(), ' '), tmp.end()); // Remove unnecessary spaces
       if (!tmp.empty()){                                           // Ensures the tmp word is not empty
           words.push_back(tmp);                                    // Adds tmp to the list of words, words
       }    
    }
    
    return;
}

// Parses line by delim and stores into words
void Driver::ParseLine2(std::string line, std::vector<std::string> &words, char delim){
    std::stringstream s_tmp(line); 
    std::string tmp;

    // Iterate through line, deliminating by ','
    while(std::getline(s_tmp, tmp, delim)){                         
       tmp.erase(remove(tmp.begin(), tmp.end(), ' '), tmp.end()); // Remove unnecessary spaces
       words.push_back(tmp);                                      // Adds tmp to the list of words, words (may be emtpy)
    }   
    
    return;
}

// Returns an candidate index representing who the vote is for from the provided line
int Driver::GetOPLVote(std::string line){
    for(int i = 0; i < line.size(); i++){
        if(line.at(i) == '1'){  // Found match
            return i;
        }
    }
    return -1;
}

// Computes the election
int Driver::ComputeElection(){
    election.RunElection();     // Runs the election and computes the results
    election.CloseReports();    // Saves the generated reports
    return 0;
}

// Gets the number of input files passed in
int Driver::GetNumInputFiles(){
    return fileHandles.size();
}

const Election& Driver::GetElection(){
    return election;
}

