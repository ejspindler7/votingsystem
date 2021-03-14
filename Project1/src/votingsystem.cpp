#include <iostream>
#include "driver.h"

int main(int argc, char *argv[]){
    if (argc <= 1){
        std::cout << "Usage: votingsystem path/to/CSVfile" << std::endl;
        return 0;
    }

    Driver driver = Driver(argv[1]);

    if (driver.ProcessCSV() != 0){
        std::cout << "Failed to process CSV " << argv[1] << std::endl;
        return 0;
    }
    if (driver.ComputeElection() != 0){
        std::cout << "Failed to compute election in voitingsystem." << std::endl;
    }

    return 0;
}
