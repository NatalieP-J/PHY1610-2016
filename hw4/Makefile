# Natalie Price-Jones Feb 2016

# Make file for rfex.cc

# For running locally
#SCINET_GSL_INC = /usr/local/include
#SCINET_GSL_LIB = /usr/local/lib

# Choose compiler
CXX = g++
# Set compiler flags
CXXFLAGS = -std=c++11 -O2 -g
# Include flags
INCFLAGS = -I${SCINET_GSL_INC}
# Library flags
LIBFLAGS = -L${SCINET_GSL_LIB} -lgsl -lgslcblas

all: rfex

rfex: rfex.o
	${CXX} ${CXXFLAGS} ${LIBFLAGS} rfex.o -o rfex

rfex.o: rfex.cpp
	${CXX} ${CXXFLAGS} ${INCFLAGS} -c rfex.cpp -o rfex.o
