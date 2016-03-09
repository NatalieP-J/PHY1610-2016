// Natalie Price-Jones Mar 2016
#include <fstream> 
#include <iostream>
#include <rarray> 
#include <rarrayio> 
#include <complex> 
#include "readcols.h"
#include "correlation.h"

int main(){

  // Set directory
  std::string directory = "gwdata";
  std::string fname = "GWprediction.rat";
  
  data_cols cols = readcols(directory,fname);

  rarray<std::complex<double>,1> prediction_FT = FT(cols.signal);
  rarray<double,1> powerspec = powerspectrum(prediction_FT);
  double corr = correlate(powerspec,powerspec);

  

  return 0;
}
