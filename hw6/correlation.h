// Natalie Price-Jones Mar 2016

#include <rarray>
#include <complex>
#include <rarrayio>

#ifndef CORRELATION_H
#define CORRELATION_H

rarray<std::complex<double>,1> FT(rarray<std::complex<double>,1> signal);
rarray<double,1> powerspectrum(rarray<std::complex<double>,1> signal);
double correlate(rarray<double,1> spec1, rarray<double,1> spec2);

#endif
