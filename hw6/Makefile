# Natalie Price-Jones Mar 2016

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

all: main
	echo "This program expects all .rat files to be in directory gwdata"

main: main.o readcols.o
	${CXX} ${CXXFLAGS} main.o readcols.o -o main

# Make libary files

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

readcols.o: readcols.cpp
	${CXX} ${CXXFLAGS} -c readcols.cpp -o readcols.o