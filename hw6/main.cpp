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

  rarray<std::complex<double>,1> powerspec = powerspectrum(cols.signal); 

  std::cout << powerspec[216164] << " " << cols.signal[216164] << "\n";
}
