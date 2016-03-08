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
    
  std::cout << "element" << cols.time[0] << cols.signal[0]<<"\n";
  rarray<std::complex<double>,1> signal_FT = FT(cols.signal); 

}
