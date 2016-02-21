// Natalie Price-Jones Feb 2016

#include <iostream>
#include <rarray>
#include <gsl/gsl_roots.h>
#include "energy.h"



double root_diff(double mass, void* mass_energy){
  energy m_energy(mass);
  f_min_all(mass,m_energy);
  return abs(m_energy.root1-m_energy.root2);
}

double maximum_load(){
  energy zeromass(0);
  double precision = 1e-5;
  double maxiter = 100;
  double mass_lo = 1.;
  double mass_hi = 5.;
  double maxmass = f_min(mass_lo,mass_hi,maxiter,precision,zeromass,root_diff);
  std::cout << "maximum mass load " << maxmass << " kg" <<"\n";
  return maxmass;
}
