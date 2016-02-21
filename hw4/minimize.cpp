// Natalie Price-Jones Feb 2016

#include <iostream>
#include <rarray>
#include <gsl/gsl_roots.h>
#include "energy.h"

double f_min(double x_lo, double x_hi, int maxiter, double precision, double (*f)(double)){
  gsl_root_fsolver* solver;
  gsl_function fwrapper;
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
  fwrapper.function = f;
  gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
  std::cout << "iter [lower, upper] root err value\n";
  int status = 1;
  double x_rt = -1
  for (int iter=0; status and iter<maxiter; iter++){
    gsl_root_fsolver_iterate(solver);
    x_rt = gsl_root_fsolver_root(solver);
    x_lo = gsl_root_fsolver_x_lower(solver);
    x_hi = gsl_root_fsolver_x_upper(solver);
    std::cout << iter << " " << x_lo << " " << x_hi << " " << x_rt << " " << x_hi-x_lo << "\n";
    status = gsl_root_test_interval(x_lo,x_hi,0,precision);
  }
  gsl_root_fsolver_free(solver);
  return x_rt;
}

rarray<double,1> f_min_all(double mass){
  rarray<double,1> roots(2);
  energy mass_energy(mass);
  double precision = 1e-5;
  int maxiter = 100
  double x_lo = 0.05;
  double x_hi = 0.25;
  double x_rt = f_min(x_lo,x_hi,maxiter,precision,mass_energy.ddx_total);
  std::cout << "value at root 1 " << mass_energy.total_energy(x_rt) << "\n";
  roots[0] = x_rt;
  x_lo = 0.4;
  x_hi = 0.49;
  x_rt = f_min(x_lo,x_hi,maxiter,precision,mass_energy.ddx_total);
  std::cout << "value at root 2 " << mass_energy.total_energy(x_rt) << "\n";
  roots[1] = x_rt;
  return roots;
  
}

double root_diff(double mass){
  rarray<double,1> roots = f_min_all(mass);
  return abs(roots[0]-roots[1]);
}

double maximum_load(){
  double precision = 1e-5;
  double maxiter = 100;
  double mass_lo = 1.;
  double mass_hi = 5.;
  double maxmass = f_min(mass_lo,mass_hi,maxiter,precision,root_diff);
  std::cout << "maximum mass load " << maxmass << " kg" <<"\n";
  return maxmass;
}
