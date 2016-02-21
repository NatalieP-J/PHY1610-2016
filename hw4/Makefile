# Natalie Price-Jones Feb 206

# Make file for energy minimization

# Choose compiler
CXX = g++
# Set compiler flags
CXXFLAGS = -std=c++11 -O2 -g
# Set BOOST flags
BOOSTFLAGS = -lboost_unit_test_framework
# Include flags
INCFLAGS = -I${SCINET_GSL_INC}
# Library flags
LIBFLAGS = -L${SCINET_GSL_LIB} -lgsl -lgslcblas

all: test

main: main.o energy.o minimize.o
	${CXX} ${CXXFLAGS} ${LIBFLAGS} minimize.o energy.o main.o -o main

test: test.o energy.o
	${CXX} ${CXXFLAGS} ${BOOSTFLAGS} test.o energy.o -o test
	./test > boost_test_LOG

# Make libary files

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

minimize.o: minimize.cpp minimize.h
	${CXX} ${CXXFLAGS} ${INCFLAGS} -c minimize.cpp -o minimize.o

energy.o: energy.cpp energy.h
	${CXX} ${CXXFLAGS} -c energy.cpp -o energy.o

test.o: test.cpp
	${CXX} ${CXXFLAGS} ${BOOSTFLAGS} -c -o test.o test.cpp

clean: 
	rm energy.o test.o boost_test_LOG