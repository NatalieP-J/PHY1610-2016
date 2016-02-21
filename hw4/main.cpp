// Natalie Price-Jones Feb 2016

#include <rarray>
#include "minimize.h"

int main(){

  rarray<double,1> roots;

  double min_mass = 0.0; // kg
  double max_mass = 0.5; // kg
  int numsteps = 25;
  double inc_mass = (max_mass-min_mass)/numsteps;
  
  double mass = min_mass;
  for (int i=0; i<numsteps; i++){
    roots = f_min_all(mass);
    mass += inc_mass;
  }
  
  double maxload = maximum_load();
}
