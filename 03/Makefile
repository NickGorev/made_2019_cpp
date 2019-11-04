CC = g++
CXXFLAGS = -std=c++11

all: runtests

test: runtests
	./runtests

runtests: main.o libparser.a
	$(CC) $(CXXFLAGS) -o runtests main.o -L. -lparser

main.o: main.cpp parser.h ../catch/catch.hpp
	$(CC) $(CXXFLAGS) -c main.cpp

libparser.a: parser.o
	ar rc libparser.a parser.o

parser.o: parser.cpp parser.h
	$(CC) $(CXXFLAGS) -c parser.cpp

clean:
	rm -rf *.o *.a runtests
