# Natalie Price-Jones Jan 2016
# Make file for ants.cc

# Choose compiler
CPP = g++
# Set compiler flags
CXXFLAGS = -std=c++11 -O2 -g -pg
# Set library flags
LDFLAGS = -g
# Choose profiler
PROF = gprof


all: profile

# Rule to do gprof profiling
profile: run
	${PROF} ants gmon_ants.out > gprof_ants_LOG
	${PROF} ants_original gmon_orig.out > gprof_orig_LOG

# Rule to run ants and save output
run: ants ants_original
	(time ./ants) &> time_ants_LOG
	mv gmon.out gmon_ants.out
	(time ./ants_original) &> time_orig_LOG
	mv gmon.out gmon_orig.out

# Make original ants.cc
ants_original: ants_original.o
	${CPP} ${CXXFLAGS} ants_original.o -o ants_original

ants_original.o: ants_original.cc
	${CPP} ${CXXFLAGS} ants_original.cc -c -o ants_original.o

# Link library files
ants: ants.o arrayfill.o moveants.o
	${CPP} ${CXXFLAGS} arrayfill.o ants.o moveants.o -o ants

# Create library files
ants.o: ants.cc
	${CPP} ${CXXFLAGS} ants.cc -c -o ants.o

moveants.o: moveants.cc moveants.h
	${CPP} ${CXXFLAGS} moveants.cc -c -o moveants.o

arrayfill.o: arrayfill.cc arrayfill.h
	${CPP} ${CXXFLAGS} arrayfill.cc -c -o arrayfill.o

ticktock.o: ticktock.cc ticktock.h
	${CXX} ${CXXFLAGS} -c -o ticktock.o ticktock.cc

# Remove library files and executables
clean:
	rm arrayfill.o moveants.o ants.o ants ants_original gmon_ants.out \
	gmon_orig.out gprof_ants_LOG gprof_orig_LOG time_ants_LOG time_orig_LOG \
	ticktock.o
