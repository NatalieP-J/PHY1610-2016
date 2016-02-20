# Natalie Price-Jones Feb 206

# Make file for energy minimization

# Choose compiler
CXX = g++
# Set compiler flags
CXXFLAGS = -std=c++11 -O2 -g
# Include flags
INCFLAGS = -I${SCINET_GSL_INC}
# Library flags
LIBFLAGS = -L${SCINET_GSL_LIB} -lgsl -lgslcblas

# Make libary files

all: energy.o

energy.o: energy.cpp
	${CXX} ${CXXFLAGS} -c energy.cpp -o energy.o
