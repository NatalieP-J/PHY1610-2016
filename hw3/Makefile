# Natalie Price-Jones Jan 2016
# Make file for ants.cc

# Choose compiler
CPP = g++
# Set compiler flags
CXXFLAGS = -std=c++11 -O2 -g -pg
# Choose profiler
PROF = gprof


all: profile

# Rule to do gprof profiling
profile: run
	${PROF} ants gmon_ants.out > gprof_ants_LOG
	${PROF} ants_original gmon_orig.out > gprof_orig_LOG

# Rule to run ants and save output
run: ants ants_original
	./ants
	mv gmon.out gmon_ants.out
	./ants_original
	mv gmon.out gmon_orig.out

# Make original ants.cc

original: ants_original
	${CPP} ${CXXFLAGS} ants_original.cc -o ants_original

# Link library files
ants: ants.o arrayfill.o moveants.o
	${CPP} ${CXXFLAGS} arrayfill.o ants.o moveants.o -o ants

# Create library files
ants.o: ants.cc
	${CPP} ${CXXFLAGS} ants.cc -c -o ants.o

moveants.o: moveants.cc
	${CPP} ${CXXFLAGS} moveants.cc -c -o moveants.o

arrayfill.o: arrayfill.cc
	${CPP} ${CXXFLAGS} arrayfill.cc -c -o arrayfill.o

# Remove library files and executables
clean:
	rm arrayfill.o moveants.o ants.o ants ants_original gmon_ants.out \
	gmon_orig.out
