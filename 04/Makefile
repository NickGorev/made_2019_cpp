CC = g++
CXXFLAGS = -std=c++14

all: runtests

test: runtests
	./runtests

runtests: main.o matrix.o
	$(CC) $(CXXFLAGS) -o runtests main.o matrix.o

main.o: main.cpp matrix.h ../catch/catch.hpp
	$(CC) $(CXXFLAGS) -c main.cpp

matrix.o: matrix.cpp matrix.h
	$(CC) $(CXXFLAGS) -c matrix.cpp

clean:
	rm -rf *.o runtests
