# Natalie Price-Jones Feb 2016

# Make file for ants.cc

# Choose compiler
CPP = g++
# Set compiler flags
CXXFLAGS = -std=c++11 -O2 -pg -gstabs -I/home/b/bovy/njones/code/include
# Set boost flags
BOOSTFLAGS = -lboost_unit_test_framework
# Choose profiler
PROF = gprof
# Choose profiler options
PROFOPT = --line --no-graph

all: profile

# Rule to do gprof profiling
profile: run
	rm gprof_ants_LOG gprof_orig_LOG
	${PROF} ${PROFOPT} ants gmon_ants.out > gprof_ants_LOG
	${PROF} ${PROFOPT} ants_original gmon_orig.out > gprof_orig_LOG

# Rule to run ants and save output
run: compile
	rm time_ants_LOG time_orig_LOG
	(time ./ants) &> time_ants_LOG
	mv gmon.out gmon_ants.out
	(time ./ants_original) &> time_orig_LOG
	mv gmon.out gmon_orig.out

# Rule to create executables for run rule
compile: ants ants_original

# Make ants_original executable
ants_original: ants_original.o ticktock.o
	${CPP} ${CXXFLAGS} ticktock.o ants_original.o -o ants_original

# Make ants executable
ants: ants.o arrayfill.o moveants.o ticktock.o
	${CPP} ${CXXFLAGS} ticktock.o arrayfill.o moveants.o ants.o -o ants

# Test suite for moveants
test: test.o moveants.o arrayfill.o
	${CPP} ${CXXFLAGS} ${BOOSTFLAGS} test.o moveants.o arrayfill.o -o test
	./test > boost_test_LOG

# Create library files
ants.o: ants.cc
	${CPP} ${CXXFLAGS} ants.cc -c -o ants.o

ants_original.o: ants_original.cc
	${CPP} ${CXXFLAGS} ants_original.cc -c -o ants_original.o

moveants.o: moveants.cc moveants.h
	${CPP} ${CXXFLAGS} moveants.cc -c -o moveants.o

arrayfill.o: arrayfill.cc arrayfill.h
	${CPP} ${CXXFLAGS} arrayfill.cc -c -o arrayfill.o

ticktock.o: ticktock.cc ticktock.h
	${CPP} ${CXXFLAGS} -c -o ticktock.o ticktock.cc

test.o: test.cc
	${CPP} ${CXXFLAGS} ${BOOSTFLAGS} -c -o test.o test.cc

# Remove library files, executable and LOG files
clean:
	rm arrayfill.o moveants.o ants.o ants ants_original gmon_ants.out \
	gmon_orig.out gprof_ants_LOG gprof_orig_LOG time_ants_LOG time_orig_LOG \
	ticktock.o
