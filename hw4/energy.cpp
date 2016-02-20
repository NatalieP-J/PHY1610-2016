#include <cmath>

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
  
  double mass;

  // Calculate spring potential at a position x
  double spring_potential(double x);

  // Calculate gravitational potential at a position x
  double grav_potential(double x);

  // Calculate the total energy
  double total_energy(double x);
  
  // Tests:
  // grav_potential == 0 if mass == 0
  // total_energy==spring_potential if mass == 0
  // Other notes:
  // How to handle x==0 case?

  // Destructor
  ~energy();
};

energy::energy(double m){
  mass = m;
}

double energy::spring_potential(double x){
  // Return energy in Joules                                                           
  return a*((b/x) + ((pow(d,2))/(f*pow((x-d),2)))-exp((-c*pow((x-b),2))/(2*a))); 
}

double energy::grav_potential(double x){
  // Return energy in Joules                                                           
  return -mass*g*x;
}

double energy::total_energy(double x){
  // Return energy in Joules
  return spring_potential(x) + grav_potential(x);
}

energy::~energy(){
}
