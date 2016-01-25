# Make file for ants.cc

# Choose compiler
CPP = g++

all: ants

ants: ants.o arrayfill.o moveants.o
	${CPP} arrayfill.o ants.o moveants.o -o ants

ants.o: ants.cc
	${CPP} ants.cc -c -o ants.o

moveants.o: moveants.cc
	${CPP} moveants.cc -c -o moveants.o

arrayfill.o: arrayfill.cc
	${CPP} arrayfill.cc -c -o arrayfill.o

clean:
	rm arrayfill.o moveants.o ants.o ants