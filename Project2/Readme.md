#The program can be run by execuitng the commands in the src directory.
1. `make clean`
2. `make`
3. `./votingsystem `
4. `<path/to/csv/file>` (command can be run multiple times to add multiple CSV files)
5. `d` when done adding files

The output will be displayed to the screen. The corresponding media and audit report will be saved 
in the src directory.

#The following commands can be entered to compile and run the unit tests

**Ballot Unit Test** 
`cd testing`

`g++ -std=c++0x ../src/ballot.cpp ballot_unittests.cc -lgtest -lgtest_main -pthread -o ballottest`

`./ballottest`

**Candidate Unit Test** 
`cd testing`

`g++ -std=c++0x ../src/ballot.cpp ../src/candidate.cpp candidate_unittests.cpp -lgtest -lgtest_main -pthread -o candidatetest`

`./candidatetest`

**Election Unit Test** 
`cd testing`

`g++ -std=c++0x ../src/ballot.cpp ../src/candidate.cpp ../src/driver.cpp ../src/election.cpp election_unittests.cpp -lgtest -lgtest_main -pthread -o electiontest`

`./electiontest`

**Driver Unit Test**
`cd testing`

`g++ -std=c++0x ../src/candidate.cpp ../src/ballot.cpp ../src/driver.cpp ../src/election.cpp driver_unittests.cpp -lgtest -lgtest_main -pthread -o drivertest`

`./drivertest`
