#include <iostream>
#include <string>
#include "driver.h"

int main(int argc, char *argv[]){
    std::string input;
    std::vector<std::string> csv_files;

    // Gets ballot csv files from user
    std::cout << "Enter name of CSV file (or path to CSV file), or 'd' to be done entering names of CSVs." << std::endl;
    cin >> input;
    while (input != "d"){ // Keeps on getting more csv files if they provide them
        csv_files.push_back(input);
        cin >> input;
    }

    // Creates a new driver
    Driver driver = Driver(csv_files);
    
    // Loads CSV files into memory
    if (driver.ProcessCSV() != 0){
        std::cout << "Failed to process CSV " << argv[1] << std::endl;
        return 0;
    }

    // Computse the election based on the loaded CSV files
    if (driver.ComputeElection() != 0){
        std::cout << "Failed to compute election in voitingsystem." << std::endl;
    }

    return 0;
}

