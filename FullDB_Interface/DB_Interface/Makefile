#compiler
  CPP = g++

#flags
  CFLAGS = -g -Wall -pedantic

default: main

main: database_interface.o main.o
	$(CPP) $(CFLAGS) database_interface.o main.o -o main

database_interface.o: database_interface.hpp database_interface.cpp
	$(CPP) $(CFLAGS) -c database_interface.cpp 

main.o: main.cpp
	$(CPP) $(CFLAGS) -c main.cpp

clean:
	rm -rf *.o 
	rm -rf *.hpp.gch
	rm -rf main