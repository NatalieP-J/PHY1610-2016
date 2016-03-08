// Natalie Price-Jones Mar 2016

#include <complex>
#include <rarray>
#include <rarrayio>
#include <fftw3.h> 

rarray<std::complex<double>,1> FT(rarray<std::complex<double>,1> signal){
  rarray<std::complex<double>,1> signal_FT(signal.size());
  // does this only depend on array length? in that case more optimal to save the plan for each signal
  fftw_plan plan = fftw_plan_dft_1d(signal.size(),(fftw_complex*)signal.data(),(fftw_complex*)signal_FT.data(),FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);
  fftw_destroy_plan(plan);
  return signal_FT;
}

rarray<double,1> powerspectrum(rarray<std::complex<double>,1> signal){
  
  return 0;
}
