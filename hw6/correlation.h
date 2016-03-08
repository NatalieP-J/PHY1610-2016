// Natalie Price-Jones Mar 2016

#include <rarray>
#include <complex>
#include <rarrayio>

#ifndef CORRELATION_H
#define CORRELATION_H

rarray<std::complex<double>,1> FT(rarray<std::complex<double>,1> signal);
rarray<std::complex<double>,1> powerspectrum(rarray<std::complex<double>,1> signal);

#endif
