// Natalie Price-Jones Feb 2016

#include <iostream>
#include <rarray>
#include "minimize.h"
#include "energy.h"
#include <tuple>

int main(){

  std::tuple<double,double> roots;

  double min_mass = 0.0; // kg
  double max_mass = 0.5; // kg
  int numsteps = 25;
  double inc_mass = (max_mass-min_mass)/numsteps;
  
  //std::cout << "Initialization complete \n";

  double mass = min_mass;
  for (int i=0; i<numsteps; i++){
    std::cout << "i = " << i << " m = " << mass << "\n";
    energy mass_energy(mass);
    roots = f_min_all(mass,mass_energy);
    double rt1 = std::get<0>(roots);
    double rt2 = std::get<1>(roots);
    std::cout << "roots " << rt1 << ", " << rt2 << "\n";
    std::cout << "energy " << mass_energy.total_energy(rt1) << ", " << mass_energy.total_energy(rt2) << "\n";
    mass += inc_mass;
  }

  std::cout << "determining maximum load" << "\n";
  double maxload = maximum_load();
}
