CC = g++
CXXFLAGS = -std=c++14

all: runtests

test: runtests
	./runtests

runtests: main.o bigint.o
	$(CC) $(CXXFLAGS) -o runtests main.o bigint.o

main.o: main.cpp bigint.h ../catch/catch.hpp
	$(CC) $(CXXFLAGS) -c main.cpp

bigint.o: bigint.cpp bigint.h
	$(CC) $(CXXFLAGS) -c bigint.cpp

clean:
	rm -rf *.o runtests
