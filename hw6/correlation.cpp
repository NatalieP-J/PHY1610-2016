// Natalie Price-Jones Mar 2016

#include <complex>
#include <rarray>
#include <rarrayio>
#include <fftw3.h> 
#include <cblas.h>
#include <iostream>
#include <math.h> 
#include "readcols.h"

rarray<std::complex<double>,1> FT(rarray<std::complex<double>,1> signal){
  // Perform a fourier transform on a complex rarray
  rarray<std::complex<double>,1> signal_FT(signal.size());
  fftw_plan plan = fftw_plan_dft_1d(signal.size(),(fftw_complex*)signal.data(),(fftw_complex*)signal_FT.data(),FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);
  fftw_destroy_plan(plan);
  return signal_FT;
}

rarray<double,1> powerspectrum(rarray<std::complex<double>,1> signal_FT){
  // Set up power spectrum output array
  rarray<double,1> powerspectrum(signal_FT.size());
  // For each element compute the absolute value and take the real (and only part)
  // to add to the power spectrum
  for (int i=0;i<signal_FT.size();i++) {
      std::complex<double> product = signal_FT[i]*std::conj(signal_FT[i]);
      double real_element = product.real();
      powerspectrum[i] = product.real();
    }		    
  return powerspectrum;
}


double correlation_coeffecient(rarray<double,1> spec1, rarray<double,1> spec2){
  // Compute all possible dot products of input spectra
  double s1s2 = cblas_ddot(spec1.size(),spec1.data(),1,spec2.data(),1);
  double s1s1 = cblas_ddot(spec1.size(),spec1.data(),1,spec1.data(),1);
  double s2s2 = cblas_ddot(spec2.size(),spec2.data(),1,spec2.data(),1);
  // Return correlation coefficient
  double corr = s1s2/sqrt(s1s1*s2s2);
  return corr;
  
}

double single_file_correlate(std::string directory, std::string fname,rarray<double,1> predictPS){
  // Read in detection signal, do the Fourier transform and compute the power spectrum
  data_cols detection = readcols(directory,fname);
  rarray<std::complex<double>,1> detection_FT = FT(detection.signal);
  rarray<double,1> detectPS = powerspectrum(detection_FT);                             
  return correlation_coeffecient(predictPS,detectPS);
}
