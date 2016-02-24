// Natalie Price-Jones Feb 2016

#include <iostream> // to write maximum mass load to console
#include <gsl/gsl_roots.h> // root finding functions
#include "energy.h" // energy class
#include <tuple> 

// Function to find a root of given funtion f within in [x_lo,x_hi] to given precision
double f_min(double x_lo, double x_hi, int maxiter, double precision, energy mass_energy,double (*f)(double, void*)){
  // Initialize solver and function wrapper
  gsl_root_fsolver* solver;
  gsl_function fwrapper;
  // Choose solver to be Brent
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
  // Specify function to use and the function's parameters
  fwrapper.function = f;
  fwrapper.params = &mass_energy;
  // Set up solver with function, interval, initial root guess and status
  gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
  int status = 1;
  double x_rt = (x_hi-x_lo)/2.;
  // Iterate solver until status is successful or maximum iterations reached
  for (int iter=0; status and iter<maxiter; iter++){
    gsl_root_fsolver_iterate(solver);
    x_rt = gsl_root_fsolver_root(solver);
    x_lo = gsl_root_fsolver_x_lower(solver);
    x_hi = gsl_root_fsolver_x_upper(solver);
    status = gsl_root_test_interval(x_lo,x_hi,0,precision);
  }
  // Free up solver memory
  gsl_root_fsolver_free(solver);
  return x_rt;
}

// Function to minimize: derivative of total energy in position
double ddx_total(double x, void* mass_energy){
  energy* m_energy = (energy*)mass_energy;
  return m_energy->ddx_spring(x) + m_energy->ddx_grav(x);
}

// Function to check if two doubles are the same sign
bool samesign(double x, double y)
{
  return (x >= 0) ^ (y < 0);
}

// Function to calculate both minima of the energy function
std::tuple<double,double> f_min_all(double mass,energy mass_energy){
  // Set precision, maximum number of iterations and first interval
  double precision = 1e-5;
  int maxiter = 100;
  double x_lo = 0.1;
  double x_hi = 0.22;
  
  // Check whether there is a root in this interval
  if (samesign(ddx_total(x_lo,&mass_energy),ddx_total(x_hi,&mass_energy))){
    double x_rt_1 = sqrt(-1.);
    mass_energy.root1 = x_rt_1;
  }
  
  // If root exists in the interval, solve for it
  else{
    double x_rt_1 = f_min(x_lo,x_hi,maxiter,precision,mass_energy,ddx_total);
    mass_energy.root1 = x_rt_1;
  }
  
  // Set second interval
  x_lo = 0.4;
  x_hi = 0.49;
  
  // Check whether there is a root in this interval
  if (samesign(ddx_total(x_lo,&mass_energy),ddx_total(x_hi,&mass_energy))){
    double x_rt_2 = sqrt(-1.);
    mass_energy.root2 = x_rt_2;
  }
  
  // If root exists in the interval solve for it
  else{
    double x_rt_2 = f_min(x_lo,x_hi,maxiter,precision,mass_energy,ddx_total);
    mass_energy.root2 = x_rt_2;
  }  
  return mass_energy.get_roots();
}

// Calculate the difference in energy at the two roots
double root_diff(double mass, void* mass_energy){
  energy m_energy(mass);
  std::tuple<double,double> roots = f_min_all(mass,m_energy);
  double diff = m_energy.total_energy(std::get<1>(roots))-m_energy.total_energy(std::get<0>(roots));
  if (isnan(diff)){
    return 10.;
  }
  else{
    return diff;
  }
}

// Calculate the mass at which the total energy values are equal at both roots
double maximum_load(){
  // Initialize zero mass energy to use f_min (this is not actually called anywhere in root_diff, so it is unused
  energy zeromass(0);
  // Set precision, maximum number of iteration and mass intervals
  double precision = 1e-5;
  double maxiter = 100;
  double mass_lo = 0.16;
  double mass_hi = 0.18;
  // Solve for the maximum mass load
  double maxmass = f_min(mass_lo,mass_hi,maxiter,precision,zeromass,root_diff);
  std::cout << "maximum mass load " << maxmass << " kg" <<"\n";
  return maxmass;
}
