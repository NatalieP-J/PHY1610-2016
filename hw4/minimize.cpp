// Natalie Price-Jones Feb 2016

#include <iostream>
#include <rarray>
#include <gsl/gsl_roots.h>
#include "energy.h"
#include <tuple>

double f_min(double x_lo, double x_hi, int maxiter, double precision, energy mass_energy,double (*f)(double, void*)){
  gsl_root_fsolver* solver;
  gsl_function fwrapper;
  //std::cout << "Root finder initialized\n";
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
  fwrapper.function = f;
  fwrapper.params = &mass_energy;
  gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
  //std::cout << "iter [lower, upper] root err value\n";
  int status = 1;
  double x_rt = -1;
  for (int iter=0; status and iter<maxiter; iter++){
    gsl_root_fsolver_iterate(solver);
    x_rt = gsl_root_fsolver_root(solver);
    x_lo = gsl_root_fsolver_x_lower(solver);
    x_hi = gsl_root_fsolver_x_upper(solver);
    //std::cout << iter << " " << x_lo << " " << x_hi << " " << x_rt << " " << x_hi-x_lo << "\n";
    status = gsl_root_test_interval(x_lo,x_hi,0,precision);
  }
  gsl_root_fsolver_free(solver);
  return x_rt;
}

double ddx_total(double x, void* mass_energy){
  energy* m_energy = (energy*)mass_energy;
  return m_energy->ddx_spring(x) + m_energy->ddx_grav(x);
}

bool samesign(double x, double y)
{
  return (x >= 0) ^ (y < 0);
}

std::tuple<double,double> f_min_all(double mass,energy mass_energy){
  //std::cout<<"Beginning root finding\n";
  double precision = 1e-5;
  int maxiter = 100;
  double x_lo = 0.1;
  double x_hi = 0.22;
  
  if (samesign(ddx_total(x_lo,&mass_energy),ddx_total(x_hi,&mass_energy))){
    double x_rt_1 = -1;
    mass_energy.root1 = x_rt_1;
  }
  
  else{
    //std::cout << "Calling root finder\n";
    double x_rt_1 = f_min(x_lo,x_hi,maxiter,precision,mass_energy,ddx_total);
    //std::cout << "value at root 1 " << mass_energy.total_energy(x_rt) << "\n";
    mass_energy.root1 = x_rt_1;
  }
  
  x_lo = 0.4;
  x_hi = 0.49;
  
  if (samesign(ddx_total(x_lo,&mass_energy),ddx_total(x_hi,&mass_energy))){
    double x_rt_2 = -2;
    mass_energy.root2 = x_rt_2;
  }
  
  else{
    double x_rt_2 = f_min(x_lo,x_hi,maxiter,precision,mass_energy,ddx_total);
    //std::cout << "value at root 2 " << mass_energy.total_energy(x_rt) << "\n";
    mass_energy.root2 = x_rt_2;
  }
  return mass_energy.get_roots();
}

double root_diff(double mass, void* mass_energy){
  energy m_energy(mass);
  std::tuple<double,double> roots = f_min_all(mass,m_energy);
  return m_energy.total_energy(std::get<1>(roots))-m_energy.total_energy(std::get<0>(roots));
}

double maximum_load(){
  energy zeromass(0);
  double precision = 1e-5;
  double maxiter = 100;
  double mass_lo = 0.16;
  double mass_hi = 0.18;
  double maxmass = f_min(mass_lo,mass_hi,maxiter,precision,zeromass,root_diff);
  std::cout << "maximum mass load " << maxmass << " kg" <<"\n";
  return maxmass;
}
