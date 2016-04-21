#
# Makefile for 1dwave code for SciNet's High Performance Scientific Computing
#  
# Modules required
#
#module load gcc/4.8.1
#module load openmpi/gcc/1.6.4
#module load pgplot/5.2.2-gcc


CXX=g++
CPPFLAGS=-I${SCINET_PGPLOT_INC} -I${SCINET_NETCDF_INC}
CXXFLAGS=-g -O0 -std=c++0x
LDLIBS=-lcpgplot -lpgplot -lX11 -lgfortran -lpng -lnetcdf
LDFLAGS=-L${SCINET_PGPLOT_LIB} -L${SCINET_NETCDF_LIB}

all: wave1d

# Makefile for wave equation

wave1d: wave1d.o ticktock.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

wave1d.o: wave1d.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

ticktock.o: ticktock.cc ticktock.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o
