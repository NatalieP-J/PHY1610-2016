// Natalie Price-Jones Feb 2016

#include "minimize.h" // f_min_all, maximum_load
#include "energy.h" // energy class
#include <tuple> // used to hold the two roots
#include <fstream> // used for writing to file
#include <math.h> // isnan and min function

int main(){
  
  // Create output file
  
  std::string fname="energyroots.txt";
  std::ofstream fout(fname);

  // Create object to hold roots
  std::tuple<double,double> roots;

  // Set mass range and number of masses for which to perform computation
  double min_mass = 0.0; // kg
  double max_mass = 0.5; // kg
  int numsteps = 25;
  // Calculate the step size in mass
  double inc_mass = (max_mass-min_mass)/numsteps;
  
  fout << "# mass\tx\tE_t(x)\n";

  // Set first mass to be the minimum
  double mass = min_mass;
  for (int i=0; i<numsteps; i++){
    // Create energy object with information about both potentials (spring and gravitational)
    energy spring_energy(mass);
    // Calculate the roots of this energy object
    roots = f_min_all(mass,spring_energy);
    // Extract the two roots
    double x_rt_1 = std::get<0>(roots);
    double x_rt_2 = std::get<1>(roots);

    // Check whether both roots exist and write the lowest existing one to file
    // If no roots exist, write that there were no roots file
    if (not isnan(x_rt_1) and not isnan(x_rt_2)){
      double energy1 = spring_energy.total_energy(x_rt_1);
      double energy2 = spring_energy.total_energy(x_rt_2);
      if (energy1 < energy2){
	fout << mass << "\t" << x_rt_1 << "\t"<< spring_energy.total_energy(x_rt_1)<< "\n";
      }
      if (energy2 < energy1){
	fout << mass << "\t" << x_rt_2 << "\t"<< spring_energy.total_energy(x_rt_2)<< "\n";
      }
    }
    else if (isnan(x_rt_1) and not isnan(x_rt_2)){
      fout << mass << "\t" << x_rt_2 << "\t"<< spring_energy.total_energy(x_rt_2)<< "\n";
    }
    else if (not isnan(x_rt_1) and isnan(x_rt_2)){
      fout << mass << "\t" << x_rt_1 << "\t"<< spring_energy.total_energy(x_rt_1)<< "\n";
    }
    else if (isnan(x_rt_1) and isnan(x_rt_2)){
      fout << mass << "\t" << "no root" <<"\t"<< "N/A"<< "\n";
    }
    // Increase mass
    mass += inc_mass;
  }
  fout.close();
  
  // Calculate the maximum mass load
  double maxload = maximum_load();
}
