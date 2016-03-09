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

  int num_detections = 32;
  int num_maxes = 5;

  // Set directory
  std::string directory = "gwdata";
  std::string predict_fname = "GWprediction.rat";
  std::string detect_fname = "detection";
  std::string extension = ".rat";
  std::string fname;

  data_cols detection;
  data_cols prediction = readcols(directory,predict_fname);

  rarray<std::complex<double>,1> detection_FT;
  rarray<std::complex<double>,1> prediction_FT = FT(prediction.signal);
  
  rarray<double,1> detectPS;
  rarray<double,1> predictPS = powerspectrum(prediction_FT);

  rarray<double,1> correlation_coeffs(num_detections);

  std::string file_i;
  for (int i=1;i<=num_detections;i++){
    file_i = std::to_string(i);
    if (i < 10){
      fname = detect_fname+"0"+file_i+extension;
    }
    else{
      fname = detect_fname+file_i+extension;
    }
    detection = readcols(directory,fname);
    detection_FT = FT(detection.signal);
    detectPS = powerspectrum(detection_FT);
    correlation_coeffs[i-1] = correlate(predictPS,detectPS);
    
  }
  
  rarray<double,1> CC_copy = correlation_coeffs.copy();
  std::sort(correlation_coeffs.data(),correlation_coeffs.data()+num_detections);
  std::reverse(correlation_coeffs.data(),correlation_coeffs.data()+num_detections);
  std::cout << "Top " << num_maxes << " most siginificant detections \n";
  for (int i=0; i<num_maxes;i++){
    int ind = std::distance(CC_copy.data(), std::find(CC_copy.data(), CC_copy.data() + CC_copy.size(), correlation_coeffs[i]));
    std::cout << "dectection " << ind+1 << "\twith correlation coefficient " << correlation_coeffs[i] << "\n";
  }

  return 0;
}
