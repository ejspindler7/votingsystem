#include <string>
#include <map>
#include "candidate.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "ballot.h"
#include <climits>
#include "report.h"
#include <ctime>

using namespace std;


Election::Election(){
    electionType       = "NONE";
    numberOfCandidates = -1;
    numberOfBallots    = -1;
    numberOfSeats      = -1;
    quota              = -1;
    string time = GetDateAndTime();
    string auditReportName = "AuditReport_" + time;
    string mediaReportName = "MediaReport" + time;
    audit.open(auditReportName);
    media.open(mediaReportName);
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

int Election::RemoveCandidate(int idx){
    candidates.erase(candidates.begin() + idx);
    return 0;
}

int Election::FindCandidateToRemove(){
    vector<int> candidates_tied;  // Using vector incase of a tie
    int current_min = INT_MAX;
    int candidate_to_remove_idx;

    for (int i = 0; i < candidates.size(); i++){
        if (candidates.at(i).GetBallotListSize() < current_min){
            current_min = candidates.at(i).GetBallotListSize();
            candidate_to_remove_idx = i; 
            candidates_tied.clear();
        }
        else if (candidates.at(i).GetBallotListSize() == current_min){
            candidates_tied.push_back(candidate_to_remove_idx); 
            candidates_tied.push_back(i); 
        }
    }

    // Check for tied candidates
    if (candidates_tied.size() > 0){
        // Resolve tie here
        // Removes duplicates from tied candidates
        sort( candidates_tied.begin(), candidates_tied.end() );
        candidates_tied.erase( unique( candidates_tied.begin(), candidates_tied.end() ), candidates_tied.end() );
        // Give seat to party 
        candidate_to_remove_idx = candidates_tied.at(ResolveTie(candidates_tied.size()));
    }

    return candidate_to_remove_idx;

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

int Election::CheckForMajority(){
    int majority = -1;
    int winning_idx = -1;
    int num_to_beat = numberOfBallots/2 ;
    
    // Incase it is the last candidate
    if (candidates.size() == 1){
        return 0;
    }

    for (int i = 0; i < candidates.size(); i++){
       if (candidates.at(i).GetBallotListSize() > majority){
            majority = candidates.at(i).GetBallotListSize();
            winning_idx = i;
       }
       else if (candidates.at(i).GetBallotListSize() == majority){
            winning_idx = -1; // Have a tie for majority
       }
    }

    // If there is a tie for majority
    if (winning_idx == -1){
        return winning_idx; 
    }
    else{ // No tie, but ensuring candidate is > numOfBallots/2
        if (majority > num_to_beat){
            return winning_idx;
        }
        else{
            // Candidate did not have
            return -1;
        }
    }
}

int Election::UpdateBallotCurrDis(Ballot* ballot){
  int curDis = ballot->GetCurrDis();
  int newDis = curDis + 1;

  if (newDis >= ballot->GetCandidatesSize()){
    return -1;  // Ran out of candidates
  }

  // Ensure the new name is a candidate stil alive in the election
  while (newDis < ballot->GetCandidatesSize()){
      for (int i = 0; i < candidates.size(); i++){
        if (candidates.at(i).GetName() == ballot->GetCandidateName(newDis)){
            ballot->SetCurrDis(newDis);
            return 0;
        }
      }
      newDis++;  // Try next distribution
  }

  return -1; // Did not find new candidate anywhere
}


int Election::RedistributeBallots(int eliminated_candidate){
    cout << "--- Redistributing Ballots " << endl;
    Ballot *ballot = candidates.at(eliminated_candidate).RemoveBallot();
    while (ballot!= NULL){
        // Continue redistributing ballots
        if (UpdateBallotCurrDis(ballot) != 0){
            // Ballot doesn't have anybody else
            ballot = candidates.at(eliminated_candidate).RemoveBallot();
            continue; // Ignore ballot
        }
        
        // Add ballot to new candidate
        for (int i = 0; i < candidates.size(); i++){
            if (candidates.at(i).GetName() == ballot->GetCandidateName(ballot->GetCurrDis())){
                cout << "Ballot Id: " << ballot->GetId() << " now goes to " << candidates.at(i).GetName() << endl;
                candidates.at(i).AddBallot(ballot);
            }
        }
         

        ballot = candidates.at(eliminated_candidate).RemoveBallot();
    }
    return 0;
}
    
int Election::SetCandidateRoundCountVotesElement(string name, int cout, int vote_num){
    // TODO
    return 0;
}


// Fair coin flip
int Election::ResolveTie(int num_candidates){
    // Return random integer between [0:num_candidates]
    int rand_number;
    for (int i = 0; i < 73 * num_candidates; i++){
        rand_number = rand() % num_candidates;
    }
    return rand_number;
}




// Computes election results for IR election
int Election::ComputeIRElection(){
    // Ensures there are candidates
    if (candidates.size() <= 0){
        cout << "No candidates. " << endl; 
        exit(1);
    }

    int round = 1;
    int candidate_to_remove_idx;
    bool found_winner = false;
    int winning_idx;

    while (!found_winner){
        cout << "=========== Round " << round << " =========== " << endl;;
        winning_idx = CheckForMajority();
        if (winning_idx != -1){
            // winning Candidate idx is winning_idx
            found_winner = true;
        }
        else{
            candidate_to_remove_idx = FindCandidateToRemove();
            RedistributeBallots(candidate_to_remove_idx);
            RemoveCandidate(candidate_to_remove_idx);
        }
       round++;
    }
    cout << "Winning Candidate: " << candidates.at(winning_idx).GetName() << 
                             " (" << candidates.at(winning_idx).GetParty() <<
                               ")" << endl;
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

    // Assign seats to parties based on whole numbers
    for (int i = 0; i < parties.size(); i++){
        int total_party_votes = numVotesForParty[parties.at(i)];
        int whole_num_seats = total_party_votes / quota;
        remaningSeats = remaningSeats - whole_num_seats;
        remaningVotes[parties.at(i)] = total_party_votes % quota;
        seatsPerPartyWholeNumber[parties.at(i)] = whole_num_seats;

    }

    // Assigns seats to parties based on remainders
    vector<int> tied_parties;
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
            tied_parties.erase(unique(tied_parties.begin(), tied_parties.end()), tied_parties.end());

            // Give seat to party 
            party_index = tied_parties.at(ResolveTie(tied_parties.size()));
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
    string wholeNumSeats = "=== Whole Number Seats ===";
    cout << wholeNumSeats << endl;
    WriteLineToAudit(wholeNumSeats);
    WriteLineToMedia(wholeNumSeats);
    for (int i = 0; i < parties.size(); i++){
        string line = "Party: " + parties.at(i) + " recieved " + 
            to_string(seatsPerPartyWholeNumber[parties.at(i)]) + " seats.";
        cout << line << endl;
        WriteLineToAudit(line);
        WriteLineToMedia(line);
    }

    string remainderNum= "=== Remainder Seat Number ===";
    cout << remainderNum << endl;
    WriteLineToAudit(remainderNum);
    WriteLineToMedia(remainderNum);
    for (int i = 0; i < parties.size(); i++){
        string line = "Party: " + parties.at(i) + " recieved " + 
           to_string(seatsPerPartyRemainder[parties.at(i)]) + " seats.";
        cout << line << endl;
        WriteLineToAudit(line);
        WriteLineToMedia(line);
    }

    string finalSeats = "=== Total Seat Number ===";
    cout << finalSeats << endl;
    WriteLineToAudit(finalSeats);
    WriteLineToMedia(finalSeats);
    for (int i = 0; i < parties.size(); i++){
        string line = "Party: " + parties.at(i) + " recieved " + 
            to_string(finalPartySeats[parties.at(i)]) + " total seats.";
        cout << line << endl;
        WriteLineToAudit(line);
        WriteLineToMedia(line);
    }



    vector<int> c_winners;
    for (int party = 0; party < parties.size(); party++){
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

    string winners = "====== WINNERS  ======";
    cout << winners << endl;
    WriteLineToAudit(winners);
    WriteLineToMedia(winners);
    for (int winner = 0; winner < c_winners.size(); winner++){
        string line = to_string(winner + 1) + ". " + candidates.at(winner).GetName() + 
            " (" + candidates.at(winner).GetParty() + ") ";
        cout << line << endl;
        WriteLineToAudit(line);
        WriteLineToMedia(line);
    }

 return 0;
}
// Computes election results
int Election::RunElection(){

    // Printing
    cout << "Candidates." << endl;
    for (int i = 0; i < candidates.size(); i++){
        string cands = candidates.at(i).GetName() + " (" + candidates.at(i).GetParty() + ") ";
        cout << cands << endl;
        WriteLineToAudit(cands);
        WriteLineToMedia(cands);
    }


    if (electionType == "OPL"){
        quota = numberOfBallots / numberOfSeats;
        ComputeOPLElection();
    }
    else if (electionType == "IR"){
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

string Election::GetDateAndTime(){
    // Got idea from: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
    time_t now = time(0); // Grabs current time.
    char* dt = ctime(&now); // Converts to string form
    string str(dt);         // Converts time to string object
    return dt;
}

int Election::WriteLineToAudit(string line){
    audit<<line + "\n" ;
    return 0;
}


int Election::WriteLineToMedia(string line){
    media<<line + "\n" ;
    return 0;
}

int Election::CloseReports(){
    audit.close();
    media.close();
    return 0;
}






