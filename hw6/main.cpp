// Natalie Price-Jones Mar 2016
#include <fstream> 
#include <iostream>
#include <rarray> 
#include <rarrayio> 
#include <complex> 
#include "readcols.h"
#include "correlation.h"
#include <string>
#include <algorithm>

int main(){

  // Define number of detections
  int num_detections = 32;
  // Set the number of most significant detections to list
  int num_maxes = 5;

  // Set directory
  std::string directory = "gwdata";
  // Choose predicted GW signal file
  std::string predict_fname = "GWprediction.rat";
  // Set file info for detection files
  std::string detect_fname = "detection";
  std::string extension = ".rat";
  // Set up string for detection file names
  std::string fname;

  // Set up data_cols object for detection files
  data_cols detection;
  // Read in predicted GW signal and time series
  data_cols prediction = readcols(directory,predict_fname);
  
  // Create array for fourier transform of detection
  rarray<std::complex<double>,1> detection_FT;
  // Find Fourier transform of predicted GW signal
  rarray<std::complex<double>,1> prediction_FT = FT(prediction.signal);
  
  // Create array for power spectrum of detection
  rarray<double,1> detectPS;
  // Compute power spectrum of predicted signal
  rarray<double,1> predictPS = powerspectrum(prediction_FT);

  // Create array to hold correlation coeffecients of each detection with 
  // the predicted signal
  rarray<double,1> correlation_coeffs(num_detections);

  // Cycle through all the detection files
  std::string file_i;
  for (int i=1;i<=num_detections;i++){
    // Construct detection file name
    file_i = std::to_string(i);
    if (i < 10){
      fname = detect_fname+"0"+file_i+extension;
    }
    else{
      fname = detect_fname+file_i+extension;
    }
    // Add correlation coeffecient to output array
    correlation_coeffs[i-1] = single_file_correlate(directory,fname,predictPS);    
  }
  
  // Make a deep copy of the correlation coeffecient to preserve correspondence to 
  // detection file index
  rarray<double,1> CC_copy = correlation_coeffs.copy();
  // Sort correlation_coeffs in descending order
  std::sort(correlation_coeffs.data(),correlation_coeffs.data()+num_detections);
  std::reverse(correlation_coeffs.data(),correlation_coeffs.data()+num_detections);
  // Print out the most significant detections
  std::cout << "Top " << num_maxes << " most siginificant detections \n";
  for (int i=0; i<num_maxes;i++){
    // Find the index of this element of correlation_coeffs in the original array
    int ind = std::distance(CC_copy.data(), std::find(CC_copy.data(), CC_copy.data() + CC_copy.size(), correlation_coeffs[i]));
    std::cout << "dectection " << ind+1 << "\twith correlation coefficient " << correlation_coeffs[i] << "\n";
  }

  return 0;
}
