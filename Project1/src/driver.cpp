#include "driver.h"
#include <iostream>
#include <fstream>
#include <sstream>


Driver::Driver(std::string file){
    fileName = file;
    fileHandle.open(fileName);
}

int Driver::ReadInElectionType(){
    std::vector<std::string> words;
    std::string tmp; 
    if (fileHandle.is_open()){
        getline(fileHandle, tmp);
        std::cout << tmp << std::endl;
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
        std::cout << "Num candidates: " << num_candidates << std::endl;
    }
        

    return 0;
}


int Driver::ReadInCandidates(){
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
    return 0;
}

// Got the parsing from
//https://www.tutorialspoint.com/How-to-read-and-parse-CSV-files-in-Cplusplus
std::vector<std::string>& ParseLine(std::string line, std::vector<std::string>& words){
    std::stringstream s_tmp(line); 
    std::string tmp;

    // Iterate through line, deliminating by ','
    while(std::getline(s_tmp, tmp, ',')){
       words.push_back(tmp);
    }
    return words;
}
