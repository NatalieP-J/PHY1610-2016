// Natalie Price-Jones Mar 2016

#include <fstream>
#include <tuple>
#include <rarray>
#include <rarrayio>
#include <complex>
#include "readcols.h"

data_cols readcols(std::string directory, std::string fname){
  // Open file
  std::ifstream columns(directory+"/"+fname);
  // Create arrays to hold columns
  data_cols column_data;
  // Read in columns
  columns >> column_data.time;
  columns >> column_data.signal;
  // Close the file
  columns.close();
  return column_data;
}
