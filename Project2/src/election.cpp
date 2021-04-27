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
#include <ctime>

using namespace std;

// Default constructor
Election::Election(){
    electionType       = "NONE";
    numberOfCandidates = -1;
    numberOfBallots    = 0;
    numberOfSeats      = -1;
    quota              = -1;
    string time = GetDateAndTime();
    string auditReportName = "AuditReport_" + time;
    string mediaReportName = "MediaReport" + time;
    audit.open(auditReportName);
    media.open(mediaReportName);
}


// Gets the number of votes for a specific party, party_name
int Election::GetVotesForParty(string party_name){
    int total_votes = 0;
    for (int i = 0; i < candidates.size(); i++){               // Iterates through all candidates
        if (candidates.at(i).GetParty() == party_name){        // Check if the current candidate has party party_name
            total_votes+= candidates.at(i).GetBallotListSize();// Adds the votes to the total number of votes for that specific party
        }
    }
    return total_votes;
}

// Sets the vote count of a specific party
int Election::SetVotesForParties(){
    for (int i = 0; i < parties.size(); i++){
        numVotesForParty[parties.at(i)] = GetVotesForParty(parties.at(i)); // Updates the total vote counts for all parties
    }
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

// Adds a candidate to the election
int Election::AddCandidate(Candidate &candidate){    
    candidates.push_back(candidate);
    return 0; 
}

// Removes a candidate from the election
int Election::RemoveCandidate(int idx){
	if (candidates.size() > 0){
		candidates.erase(candidates.begin() + idx);
	}

    return 0;
}

// Finds which candide to remove (lowest number of votes)
int Election::FindCandidateToRemove(){
    vector<int> candidates_tied;  // Using vector incase of a tie
    int current_min = INT_MAX;
    int candidate_to_remove_idx;

	// Traverse all candidates, searching for which candidate to remove
    for (int i = 0; i < candidates.size(); i++){                     // Iterates through all candidates
        if (candidates.at(i).GetBallotListSize() < current_min){     // Does the current candidate have a fewer number of votes then the candidate we want to remove
            current_min = candidates.at(i).GetBallotListSize();      // Book keeping for the min vote algorithm
            candidate_to_remove_idx = i; 
            candidates_tied.clear();                                 // Clears tie because we found a new lowest candidate
        }
        else if (candidates.at(i).GetBallotListSize() == current_min){  // See if the candidate tied for lowest number of votes
            candidates_tied.push_back(candidate_to_remove_idx);         // Add candidate to list of tied candidates for lowest
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

    return candidate_to_remove_idx; // The index of the candidate to remove from 'candidates'

}

// Gets the number of unique parties in the election
int Election::GetNumberParties(){
    return parties.size();
}
    
// Adds a party to the election
int Election::AddParty(string party_name){
    bool party_already_exists = false;

    for(int i = 0; i < parties.size(); i++){ // Iterate through all parties and see if it has already been added
        if (party_name == parties.at(i)){
            party_already_exists = true;     // Party has already been added
            break;
        }
    }
    
    if (!party_already_exists){              // Party already exists?
        parties.push_back(party_name);       // If not, add party to list of parties
    }
    return 0;
}

// See if any of the current candidates have a majority
int Election::CheckForMajority(){
    int majority = -1;
    int winning_idx = -1;
    int num_to_beat = numberOfBallots/2 ;
    
    // Incase it is the last candidate
    if (candidates.size() == 1){
        return 0;
    }

    for (int i = 0; i < candidates.size(); i++){                                 // Iterate through all candidates
        string line = "Candidate " + candidates.at(i).GetName() + " now has " + 
            to_string(candidates.at(i).GetBallotListSize()) + " ballots.";
        cout << line << endl;       // Writes line to stdout
        WriteLineToAudit(line);     // Writes line to audit file
        WriteLineToMedia(line);     // Writes line to media file

       if (candidates.at(i).GetBallotListSize() > majority){    // Checking for majority
            majority = candidates.at(i).GetBallotListSize();    // Update the winning idx with candidate that has majority
            winning_idx = i;
       }
       else if (candidates.at(i).GetBallotListSize() == majority){ // See if candidates are tied with current majority candidate
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

// Updates the ballot's current distribution (which candidate the ballot counts for)
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

// Redistributes the ballots for IR election
int Election::RedistributeBallots(int eliminated_candidate){
    string line = "-- Redistributing Ballots ---";
    WriteLineToAudit(line);

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
            if (candidates.at(i).GetName() == ballot->GetCandidateName(ballot->GetCurrDis())){ // Iterates through all candidates
                string line = "Ballot Id; " + to_string(ballot->GetId()) + " now goes to " + candidates.at(i).GetName();
                WriteLineToAudit(line);            // Writes line to audit file
                candidates.at(i).AddBallot(ballot);// Adds ballot to candidate
            }
        }
        ballot = candidates.at(eliminated_candidate).RemoveBallot(); // Removes ballot from candidate
    }
    return 0;
}
// Fair coin flip
int Election::ResolveTie(int num_candidates){
    // Return random integer between [0 - num_candidates]
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);


    int constant = now->tm_sec * num_candidates * 73;
    int rand_number;
    for (int i = 0; i < constant; i++){ // Random loop to prime the random number
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

    while (!found_winner){ // Found winner?
        string line = "=========== Round " + to_string(round) + " =========== ";
        cout << line << endl;   // Writes line to stdout
        WriteLineToAudit(line); // Writes line to media report
        WriteLineToMedia(line); // Writes line to audit report
        winning_idx = CheckForMajority();   // See if a particurlar candidate has won
        if (winning_idx != -1){
            // winning Candidate idx is winning_idx
            found_winner = true;
        }
        else{ // No candidates won
            candidate_to_remove_idx = FindCandidateToRemove();  // Find candidate to remove
            RedistributeBallots(candidate_to_remove_idx);       // Redistributes the ballots
            RemoveCandidate(candidate_to_remove_idx);           // Removes a candidate
        }
       round++; // Updates the current round
    }

    string equal = "============================================";
    string winningCandidate = "Winning Candidate: " + candidates.at(winning_idx).GetName() + " (" 
        + candidates.at(winning_idx).GetParty() + ").";
    cout << equal << endl;                  // Writes equal to stdout
    cout << winningCandidate << endl;       // Writes winningCandidate to stdout
    WriteLineToMedia(equal);                // Writes equal to media report
    WriteLineToMedia(winningCandidate);     // Writes winningCandidate to media report
    WriteLineToAudit(winningCandidate);     // Writes winningCandidate to audir report
    return 0;
}

// Computes PO election 
int Election::ComputePOElection(){
    // Stubbed function where PO election would be computed.
    // Didn't have to compute PO election yet because not on Sprint Log
    std::cout << "PO information read into memory." << std::endl;
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
    for (int i = 0; i < parties.size(); i++){   // Iterates through all parties
        int total_party_votes = numVotesForParty[parties.at(i)]; // Book keeping
        int whole_num_seats = total_party_votes / quota;
        remaningSeats = remaningSeats - whole_num_seats;
        remaningVotes[parties.at(i)] = total_party_votes % quota;
        seatsPerPartyWholeNumber[parties.at(i)] = whole_num_seats;

    }

    // Assigns seats to parties based on remainders
    vector<int> tied_parties;
    map<string, int> remaningVotes_local(remaningVotes);
    for(int i = 0; i < remaningSeats; i++){     // Assign remaning seats to candidates
        int party_index = 0;
        // Find party with most remainder votes
        for (int j = 0; j < parties.size(); j++){   // Iterate through all parties
            if (remaningVotes_local[parties.at(party_index)] < remaningVotes_local[parties.at(j)]){ // See if a particular party won the seat (a party has more votes then that party)
                party_index = j;
                tied_parties.clear();
            }
            else if (remaningVotes_local[parties.at(party_index)] == remaningVotes_local[parties.at(j)]){  // Parties tied, must fairly eliminate a loser
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
    for (int i = 0; i < parties.size(); i++){   // Iterate through all parties
        finalPartySeats[parties.at(i)] = seatsPerPartyWholeNumber[parties.at(i)] + 
                                         seatsPerPartyRemainder[parties.at(i)];
    }

    // Distribute seats to candidates
    string wholeNumSeats = "=== Whole Number Seats ===";
    cout << wholeNumSeats << endl;  // Writes wholeNumSeats to stdout
    WriteLineToAudit(wholeNumSeats);// Writes wholeNumSeats to audit file
    WriteLineToMedia(wholeNumSeats);// Writes wholeNumSeats to media file
    for (int i = 0; i < parties.size(); i++){   // Iterates through all parties
        string line = "Party: " + parties.at(i) + " recieved " + 
            to_string(seatsPerPartyWholeNumber[parties.at(i)]) + " seats.";
        cout << line << endl;   // Writes line to stdout
        WriteLineToAudit(line); // Writes line to audit file
        WriteLineToMedia(line); // Writes line to media file
    }

    string remainderNum= "=== Remainder Seat Number ===";
    cout << remainderNum << endl;   // Writes remainderNum to stdout
    WriteLineToAudit(remainderNum); // Writes remainderNum to audit file
    WriteLineToMedia(remainderNum); // Writes remainderNum to media file
    for (int i = 0; i < parties.size(); i++){ // Iterates through all parties
        string line = "Party: " + parties.at(i) + " recieved " + 
           to_string(seatsPerPartyRemainder[parties.at(i)]) + " seats.";
        cout << line << endl;  // Writes line to stdout
        WriteLineToAudit(line);// Writes line to audit report
        WriteLineToMedia(line);// Writes line to media report
    }

    string finalSeats = "=== Total Seat Number ===";
    cout << finalSeats << endl;  // Writes finalSeats to stdout
    WriteLineToAudit(finalSeats);// Writes finalSeats to audit
    WriteLineToMedia(finalSeats);// Writes finalSeats to media
    for (int i = 0; i < parties.size(); i++){ // Iterates through all parties
        string line = "Party: " + parties.at(i) + " recieved " + 
            to_string(finalPartySeats[parties.at(i)]) + " total seats.";
        cout << line << endl;  // Writes line to stdout
        WriteLineToAudit(line);// Writes line to audit file
        WriteLineToMedia(line);// Writes line to media file
    }


    vector<int> tied_candidates;
    vector<int> c_winners;
    for (int party = 0; party < parties.size(); party++){    // Iterate through all parties
        int seats_to_give = finalPartySeats[parties.at(party)];

        for (int seat = 0; seat < seats_to_give; seat++){ // Go through seats to give, giving away a seat each iteration to a party
            int winner_idx = 0;
            int winner_votes = -1; 
            tied_candidates.clear();
            for (int c = 0; c < candidates.size(); c++){ // Iterate through all candidates
                // Current candidate did not already win
                if (!(std::count(c_winners.begin(), c_winners.end(), c))){
                    // The are the same party
                    if (parties.at(party) == candidates.at(c).GetParty()){
                        // current candidate has more votes than winning candidate
                        if (winner_votes < candidates.at(c).GetBallotListSize()){
                            winner_idx = c;
                            winner_votes = candidates.at(c).GetBallotListSize();
                        }
                        // Candidates tied for winner
                        else if(winner_votes == candidates.at(c).GetBallotListSize()){// If candidate tied, add them to tied_candidates to resolve ties later
                            tied_candidates.push_back(winner_idx);
                            tied_candidates.push_back(c);
                        }
                    }
                }
            }

            // Check and resolve ties
            if(tied_candidates.size() != 0){
                sort(tied_candidates.begin(), tied_candidates.end());
                tied_candidates.erase(unique(tied_candidates.begin(), tied_candidates.end()), tied_candidates.end());

                // Give seat to party 
                winner_idx = tied_candidates.at(ResolveTie(tied_candidates.size()));
            }
            c_winners.push_back(winner_idx);
        }
    }

    string winners = "====== WINNERS  ======";
    cout << winners << endl;  // Writes winners to stdout
    WriteLineToAudit(winners);// Writes winners to audit file
    WriteLineToMedia(winners);// Writes winners to media file
    for (int winner = 0; winner < c_winners.size(); winner++){ // Iterate through all winners
        string line = to_string(winner + 1) + ". " + candidates.at(c_winners.at(winner)).GetName() + 
            " (" + candidates.at(c_winners.at(winner)).GetParty() + ") ";
        cout << line << endl;   // Write line to stdout
        WriteLineToAudit(line); // Wrtie line to audit file
        WriteLineToMedia(line); // Write line to media file
    }

 return 0;
}


// Computes election results
int Election::RunElection(){

    // Printing
    string line = "** Candidates **";
    cout << line << endl;   // Writes line to stdout
    WriteLineToAudit(line); // Writes line to audit file
    WriteLineToMedia(line); // Witess line to media file


    for (int i = 0; i < candidates.size(); i++){ // Iterates though all candidates
        string cands = candidates.at(i).GetName() + " (" + candidates.at(i).GetParty() + ") ";
        cout << cands << endl;  // Writes cands to stdout
        WriteLineToAudit(cands);// Writes cands to audit file
        WriteLineToMedia(cands);// Writes cands to media file
    }


    if (electionType == "OPL"){ // Election type is OPL
        quota = numberOfBallots / numberOfSeats; // Calculate quota
        ComputeOPLElection();                    // Compute OPL Election
    }
    else if (electionType == "IR"){// Election type is IR
        ComputeIRElection();       // Compute IR election
    }
    else if (electionType == "PO"){ // Election type is PO
        ComputePOElection();        // Compute PO election
    }
    else{
        cout << "Didn't recognize election type." << endl;        
    }

    return 0;
}

// Gets the candidate at idx
Candidate& Election::GetCandidate(int idx){
    return candidates.at(idx);
}

// Gets the current date and time
string Election::GetDateAndTime(){
    // Got idea from: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
    time_t now = time(0); // Grabs current time.
    char* dt = ctime(&now); // Converts to string form
    string str(dt);         // Converts time to string object
    return dt;
}

// Writes a line to an audit file
int Election::WriteLineToAudit(string line){
    audit<<line + "\n" ;
    return 0;
}

// Writes a line to the media file
int Election::WriteLineToMedia(string line){
    media<<line + "\n" ;
    return 0;
}


// Saves the reports
int Election::CloseReports(){
    audit.close();
    media.close();
    return 0;
}






