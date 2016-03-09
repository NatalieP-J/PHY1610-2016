// Natalie Price-Jones Mar 2016

#include <rarray>
#include <complex>
#include <rarrayio>
#include <string>

#ifndef CORRELATION_H
#define CORRELATION_H

rarray<std::complex<double>,1> FT(rarray<std::complex<double>,1> signal);

rarray<double,1> powerspectrum(rarray<std::complex<double>,1> signal);

double single_file_correlate(std::string directory, std::string fname,rarray<double,1> predictPS);

#endif
