CC = g++
CXXFLAGS = -std=c++11

all: calc

run: calc
	./calc "$(filter-out $@,$(MAKECMDGOALS))"
%:
	@:

test: calc
	./test/runtests.sh ./calc ./test/tests.txt

calc: main.o calculator.o
	$(CC) $(CXXFLAGS) -o calc main.o calculator.o

main.o: main.cpp calculator.h
	$(CC) $(CXXFLAGS) -c main.cpp

calculator.o: calculator.cpp calculator.h
	$(CC) $(CXXFLAGS) -c calculator.cpp

clean:
	rm -rf *.o calc
