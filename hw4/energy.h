// Natalie Price-Jones Feb 2016

#include <tuple>

#ifndef ENERGY_H
#define ENERGY_H

class energy{
private:

  // Constants of energy equations
  const float a = 1; // Joules - energy scale
  const float b = 0.1; // metres - length scale
  const float c = 100; // Newtons/metre - spring constant
  const float d = 0.5; // metres - max spring extension
  const float f = 2500; // stiffness at max extension
  const float g = 9.8; // metres/second^2 - gravitational acceleration
  
public:
  
  // Constructor - used to assign mass
  energy(double m);
  
  // Mass of weight on spring
  double mass; // kg

  // Up to two roots of the function on the interval [0.01,0.49]
  double root1; // metres
  double root2; // metres

  // For passing roots together
  std::tuple<double,double> roots;

  // Calculate spring potential at a position x
  double spring_potential(double x);

  // Calculate gravitational potential at a position x
  double grav_potential(double x);

  // Calculate the total potential energy at a position x
  double total_energy(double x);

  // Calculate the derivative of the spring potential at postion x
  double ddx_spring(double x);

  // Calculate the derivative of the gravitational potential at position x
  double ddx_grav(double x);

  // Function to return tuple of roots
  std::tuple<double,double> get_roots();

  // Destructor
  ~energy();

};

#endif
