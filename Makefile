#compiler
  CPP = g++

#flags
  CFLAGS = -g -Wall -pedantic
  PQXXFLAGS = -lpqxx -lpq
  VERS = -std=c++14

default: main

main: DatabaseInterface.o ClasterState.o TaskInfo.o ClasterStateTable.o \
TaskInfoTable.o MapInfoTable.o TaskPathesTable.o main.o
	$(CPP) $(CFLAGS) DatabaseInterface.o ClasterState.o TaskInfo.o \
ClasterStateTable.o TaskInfoTable.o MapInfoTable.o TaskPathesTable.o main.o -o main $(PQXXFLAGS)

DatabaseInterface.o: FullDB_Interface/DB_Interface/DatabaseInterface.hpp FullDB_Interface/DB_Interface/DatabaseInterface.cpp
	$(CPP) $(CFLAGS) $(VERS) -c FullDB_Interface/DB_Interface/DatabaseInterface.cpp 

ClasterState.o: FullDB_Interface/ClasterState/ClasterState.hpp FullDB_Interface/ClasterState/ClasterState.cpp
	$(CPP) $(CFLAGS) $(VERS) -c FullDB_Interface/ClasterState/ClasterState.cpp

TaskInfo.o: FullDB_Interface/TaskInfo/TaskInfo.hpp FullDB_Interface/TaskInfo/TaskInfo.cpp
	$(CPP) $(CFLAGS) $(VERS) -c FullDB_Interface/TaskInfo/TaskInfo.cpp

ClasterStateTable.o: FullDB_Interface/ClasterStateTable.hpp FullDB_Interface/ClasterStateTable.cpp
	$(CPP) $(CFLAGS) $(VERS) -c FullDB_Interface/ClasterStateTable.cpp $(PQXXFLAGS)

TaskInfoTable.o: FullDB_Interface/TaskInfoTable.hpp FullDB_Interface/TaskInfoTable.cpp
	$(CPP) $(CFLAGS) $(VERS) -c FullDB_Interface/TaskInfoTable.cpp $(PQXXFLAGS)

MapInfoTable.o: FullDB_Interface/MapInfoTable.hpp FullDB_Interface/MapInfoTable.cpp
	$(CPP) $(CFLAGS) $(VERS) -c FullDB_Interface/MapInfoTable.cpp $(PQXXFLAGS)

TaskPathesTable.o: FullDB_Interface/TaskPathesTable.hpp FullDB_Interface/TaskPathesTable.cpp
	$(CPP) $(CFLAGS) $(VERS) -c FullDB_Interface/TaskPathesTable.cpp $(PQXXFLAGS)

main.o: main.cpp
	$(CPP) $(CFLAGS) $(VERS) -c main.cpp $(PQXXFLAGS)

clean:
	rm -rf *.o 
	rm -rf *.hpp.gch
	rm -rf main