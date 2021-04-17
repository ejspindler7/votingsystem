#include <iostream>
#include <string>
#include "driver.h"

int main(int argc, char *argv[]){
    std::string input;
    std::vector<std::string> csv_files;

    std::cout << "Enter name of CSV file (or path to CSV file), or 'd' to be done entering names of CSVs." << std::endl;
    cin >> input;
    while (input != "d"){
        csv_files.push_back(input);
        cin >> input;
    }

   
    Driver driver = Driver(csv_files);
    

    if (driver.ProcessCSV() != 0){
        std::cout << "Failed to process CSV " << argv[1] << std::endl;
        return 0;
    }
    
    std::cout << "Exiting from votingsystem.cpp" << std::endl;
    exit(0);
    if (driver.ComputeElection() != 0){
        std::cout << "Failed to compute election in voitingsystem." << std::endl;
    }

    return 0;
}
