CC = g++
CXXFLAGS = -std=c++14

all: runtests

test: runtests
	./runtests

runtests: main.o 
	$(CC) $(CXXFLAGS) -o runtests main.o

main.o: main.cpp errors.h serializer.h deserializer.h ../catch/catch.hpp
	$(CC) $(CXXFLAGS) -c main.cpp

clean:
	rm -rf *.o runtests test.txt
