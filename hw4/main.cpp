// Natalie Price-Jones Feb 2016

#include <iostream>
#include <rarray>
#include "minimize.h"
#include "energy.h"

int main(){

  rarray<double,1> roots(2);

  double min_mass = 0.0; // kg
  double max_mass = 0.5; // kg
  int numsteps = 25;
  double inc_mass = (max_mass-min_mass)/numsteps;
  
  //std::cout << "Initialization complete \n";

  double mass = min_mass;
  for (int i=0; i<numsteps; i++){
    std::cout << "i = " << i << " m = " << mass << "\n";
    energy mass_energy(mass);
    mass_energy.f_min_all();
    std::cout << "roots " << mass_energy.root1 << ", " << mass_energy.root2 << "\n";
    mass += inc_mass;
  }
  double maxload = maximum_load();
}
