CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = nqueens.o nqueens_functions.o

nqueens: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o $@ nqueens.o nqueens_functions.o

nqueens.o: nqueens.cpp nqueens.h nqueens_functions.cpp
		$(CXX) -g $(CXXFLAGS) -c nqueens.cpp

nqueens_functions.o: nqueens_functions.cpp nqueens.h
		$(CXX) -g $(CXXFLAGS) -c nqueens_functions.cpp

clean:
	rm *.o
	rm nqueens