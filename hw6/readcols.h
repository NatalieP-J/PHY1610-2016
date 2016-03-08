// Natalie Price-Jones Mar 2016

#include <fstream>
#include <tuple>
#include <rarray>
#include <rarrayio>
#include <complex>

#ifndef READCOLS_H
#define READCOLS_H

struct data_cols{
  rarray<double,1> time;
  rarray<std::complex<double>,1> signal;
}

data_cols readcols(std::string directory, std::string fname);

#endif
