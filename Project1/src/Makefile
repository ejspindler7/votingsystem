CC = g++
CFLAGS = -lrt -g
DEPS = ballot.h candidate.h driver.h election.h report.h
OBJ = ballot.o candidate.o driver.o election.o report.o votingsystem.o


%.o: %.cpp $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS) 

votingsystem: $(OBJ)
	$(CC) -g -o  $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o
	rm Media*
	rm Audit*

