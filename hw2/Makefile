# Make file for ants.cc

# Choose compiler
CPP = g++

all: ants

ants: ants.o arrayfill.o
	${CPP} arrayfill.o ants.o -o ants

ants.o: ants.cc
	${CPP} ants.cc -c -o ants.o

arrayfill.o: arrayfill.cc
	${CPP} arrayfill.cc -c -o arrayfill.o

clean:
	rm arrayfill.o ants.o ants