// Natalie Price-Jones Mar 2016
#include <fstream> 
#include <rarray> 
#include <rarrayio> 
#include <complex> 
#include "readcols.h"

int main(){

  // Set directory
  std::string directory = "gwdata";
  std::string fname = "GWprediction.rat";
  
  data_cols cols = readcols(directory,fname);
    

  // open the file 
  //std::ifstream prediction("gwdata/GWprediction.rat"); 
  // create empty arrays 
  //rarray<double,1> ptimes; 
  //rarray<std::complex<double>,1> psignal; 

  // read in the signal 
  //prediction >> ptimes; 
  //prediction >> psignal; 

}
