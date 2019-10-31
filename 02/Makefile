CC = g++
CXXFLAGS = -std=c++11

all: runtests

test: runtests
	./runtests

runtests: main.o allocator.o
	$(CC) $(CXXFLAGS) -o runtests main.o allocator.o

main.o: main.cpp allocator.h catch.hpp
	$(CC) $(CXXFLAGS) -c main.cpp

allocator.o: allocator.cpp allocator.h
	$(CC) $(CXXFLAGS) -c allocator.cpp

clean:
	rm -rf *.o runtests
