#compiler
  CC = g++

#flags
  CFLAGS = -g -Wall -pedantic
  CFLAGS2 = -lzmq -lstdc++ -std=c++14

default: Main

Main: IProcessMQ.o
	$(CC) $(CFLAGS) IProcessMQ.o server.cpp -o Server $(CFLAGS2)
	$(CC) $(CFLAGS) IProcessMQ.o client.cpp -o Client $(CFLAGS2)

IProcessMQ.o: IProcessMQInterface.hpp IProcessMQ.hpp IProcessMQ.cpp
	$(CC) $(CFLAGS) -c IProcessMQ.cpp $(CFLAGS2)

clean:
	rm Server Client *.o