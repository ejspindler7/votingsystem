# Compiling and Running the Unit Tests

**Ballot Unit Test** 
```
g++ -std=c++0x ../src/ballot.cpp ballot_unittests.cc -lgtest -lgtest_main -pthread -o ballottest

./ballottest
```
**Candidate Unit Test** 
```
g++ -std=c++0x ../src/ballot.cpp ../src/candidate.cpp candidate_unittests.cpp -lgtest -lgtest_main -pthread -o candidatetest

./candidatetest
```
**Election Unit Test** 
```
g++ -std=c++0x ../src/ballot.cpp ../src/candidate.cpp ../src/driver.cpp ../src/election.cpp election_unittests.cpp -lgtest -lgtest_main -pthread -o electiontest

./electiontest
```
**Driver Unit Test**
```
g++ -std=c++0x ../src/candidate.cpp ../src/ballot.cpp ../src/driver.cpp ../src/election.cpp driver_unittests.cpp -lgtest -lgtest_main -pthread -o drivertest

./drivertest
```