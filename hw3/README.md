# Natalie Price-Jones Feb 2016

Contains two programs to move ants around a table, one monolithic (ants_original.cc) and one modularized (ants.cc).

The accompanying Makefile will create executables, run tests and save output.

make            : Creates executables, runs them and does profiling with gprof
make profile    : Runs executables and does line by line profiling with gprof
make run        : Runs executables and saves output in LOG files
make compile    : Creates executables ants and ants_original
make test       : Runs BOOST tests on ant movement functions and saves output to LOG file
make clean      : Removes executables, library files and LOG files