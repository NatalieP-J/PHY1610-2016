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

test: test.o energy.o
	${CXX} ${CXXFLAGS} ${BOOSTFLAGS} test.o energy.o -o test
	./test > boost_test_LOG

# Make libary files

energy.o: energy.cpp
	${CXX} ${CXXFLAGS} -c energy.cpp -o energy.o

test.o: test.cpp
	${CXX} ${CXXFLAGS} ${BOOSTFLAGS} -c -o test.o test.cpp

clean: 
	rm energy.o test.o boost_test_LOG