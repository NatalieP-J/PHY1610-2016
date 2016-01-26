# Make file for ants.cc

# Choose compiler
CPP = g++
CXXFLAGS = -std=c++11 -O2


all: ants

ants: ants.o arrayfill.o moveants.o
	${CPP} arrayfill.o ants.o moveants.o -o ants

ants.o: ants.cc
	${CPP} ${CXXFLAGS} ants.cc -c -o ants.o

moveants.o: moveants.cc
	${CPP} ${CXXFLAGS} moveants.cc -c -o moveants.o

arrayfill.o: arrayfill.cc
	${CPP} ${CXXFLAGS} arrayfill.cc -c -o arrayfill.o

clean:
	rm arrayfill.o moveants.o ants.o ants