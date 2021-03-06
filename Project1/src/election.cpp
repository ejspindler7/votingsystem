#include <string>
#include <map>
#include "candidate.h"
#include "report.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

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
    
    return total_votes;
}


int Election::SetVotesForParties(){
    for (int i = 0; i < parties.size(); i++){
        numVotesForParty[parties.at(i)] = GetVotesForParty(parties.at(i));
    }
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
    // Retrun random integer between [0:num_candidates]
    int rand_number;
    for (int i = 0; i < 73 * num_candidates; i++){
        rand_number = rand() % num_candidates;
    }
    return rand_number;
}

// Computes election results for IR election
int Election::ComputeIRElection(){
    // TODO
    return 0;
}

// Computes results for OPL election
int Election::ComputeOPLElection(){
    // Sets up maps
    for (int i = 0; i < parties.size(); i++){
        seatsPerPartyWholeNumber[parties.at(i)] = 0;
        seatsPerPartyRemainder[parties.at(i)] = 0;
        numVotesForParty[parties.at(i)] = 0;

    }
    // Iterate through parties and get their total votes
    SetVotesForParties();
    map<string, int> remaningVotes;
    int remaningSeats = numberOfSeats;

    //PRINTS OUT STUFF
    for (int i = 0; i < parties.size(); i++){
        cout << "Party: " << parties.at(i) << " had: " << numVotesForParty[parties.at(i)] << endl;
    }
   
    // Assign seats to parties based on whole numbers
    cout << "Whole numbers =================" << endl;
    for (int i = 0; i < parties.size(); i++){
        int total_party_votes = numVotesForParty[parties.at(i)];
        int whole_num_seats = total_party_votes / quota;
        cout << parties.at(i) << ": " << whole_num_seats << endl;
        remaningSeats = remaningSeats - whole_num_seats;
        remaningVotes[parties.at(i)] = total_party_votes % quota;
        seatsPerPartyWholeNumber[parties.at(i)] = whole_num_seats;

    }

    // DEBUGGIN
    cout << "Remaning votes." << endl;
    for (int i = 0; i < parties.size(); i++){
        cout << "Party: " << remaningVotes[parties.at(i)] << endl;
    }


    // Assigns seats to parties based on remainders
    vector<int> tied_parties;
    cout << "Remaning seats: " << remaningSeats << endl;
    map<string, int> remaningVotes_local(remaningVotes);
    for(int i = 0; i < remaningSeats; i++){
        int party_index = 0;
        // Find party with most remainder votes
        for (int j = 0; j < parties.size(); j++){
            if (remaningVotes_local[parties.at(party_index)] < remaningVotes_local[parties.at(j)]){
                party_index = j;
                tied_parties.clear();
            }
            else if (remaningVotes_local[parties.at(party_index)] == remaningVotes_local[parties.at(j)]){
                tied_parties.push_back(party_index);
                tied_parties.push_back(j);
            }
            else{
                continue;
            }
        }

        // Check if parties tied
        if(tied_parties.size() != 0){
            sort(tied_parties.begin(), tied_parties.end());
            tied_parties.erase(unique(tied_parties.begin(), tied_parties.end()));

            // Give seat to party 
            party_index = ResolveTie(tied_parties.size());
        }




        // Assign seat to party_index
        seatsPerPartyRemainder[parties.at(party_index)] = 1;
        remaningVotes_local[parties.at(party_index)] = -1; // Allow other parties to get seat
        remaningSeats--;
    }

    // Sum up seats to give
    for (int i = 0; i < parties.size(); i++){
        finalPartySeats[parties.at(i)] = seatsPerPartyWholeNumber[parties.at(i)] + 
                                         seatsPerPartyRemainder[parties.at(i)];
    }


    // Distribute seats to candidates
    vector<int> c_winners;
    cout << endl <<c_winners.size() << endl;
    cout << "====== Results ======" << endl;
    for (int party = 0; party < parties.size(); party++){
        cout << "Party: " << parties.at(party) << endl;
        int seats_to_give = finalPartySeats[parties.at(party)];
        int winner_idx = 0;
        int winner_votes = -1;
        for (int seat = 0; seat < seats_to_give; seat++){
            
            for (int c = 0; c < candidates.size(); c++){
                // Current candidate did not already win
                if (!(std::count(c_winners.begin(), c_winners.end(), c))){
                    // The are the same party
                    if (parties.at(party) == candidates.at(c).GetParty()){
                        // current candidate has more votes than winning candidate
                        if (winner_votes < candidates.at(c).GetBallotListSize()){
                            winner_idx = c;
                            winner_votes = candidates.at(c).GetBallotListSize();
                        }
                    }
                }
            }

            c_winners.push_back(winner_idx);

        }
    }
    cout << "Results" << endl;
    for (int winner = 0; winner < c_winners.size(); winner++){
        cout << candidates.at(winner).GetName() << endl;
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




