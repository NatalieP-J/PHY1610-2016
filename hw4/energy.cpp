#include <cmath>
#include <rarray>
#include <iostream>
#include <gsl/gsl_roots.h>

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

  double root1;
  double root2;

  // Calculate spring potential at a position x
  double spring_potential(double x);

  // Calculate gravitational potential at a position x
  double grav_potential(double x);

  double total_energy(double x);

  // Calculate the derivative of the spring potential at postion x
  double ddx_spring(double x);

  // Calculate the derivative of the gravitational potential at position x
  double ddx_grav(double x);

  double ddx_total(double x);

  double f_min(double x_lo, double x_hi, int maxiter, double precision, double (*f)(double));

  void f_min_all();

  double root_diff();
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
  return spring_potential(x) + grav_potential(x);
}

double energy::ddx_spring(double x){
  return a*((-b/pow(x,2)) + ((-2*pow(d,2))/(f*pow((x-d),3))) + (2*c*(x-b)/(2*a))*exp((-c*pow((x-b),2))/(2*a)));
}

double energy::ddx_grav(double x){
  return -mass*g;
}

double energy::ddx_total(double x){
  return ddx_spring(x) + ddx_grav(x);
}

double energy::f_min(double x_lo, double x_hi, int maxiter, double precision, double (*f)(double)){
  gsl_root_fsolver* solver;
  gsl_function fwrapper;
  //std::cout << "Root finder initialized\n";
  solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
  fwrapper.function = f;
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

void energy::f_min_all(){
  //std::cout<<"Beginning root finding\n";
  double precision = 1e-5;
  int maxiter = 100;
  double x_lo = 0.1;
  double x_hi = 0.22;
  
  if (samesign(ddx_total(x_lo),ddx_total(x_hi))){
    double x_rt = -1;
    root1 = x_rt;
  }
  
  else{
    //std::cout << "Calling root finder\n";
    double x_rt = f_min(x_lo,x_hi,maxiter,precision,ddx_total);
    //std::cout << "value at root 1 " << mass_energy.total_energy(x_rt) << "\n";
    root1 = x_rt;
  }
  
  x_lo = 0.4;
  x_hi = 0.49;
  
  if (samesign(ddx_total(x_lo),ddx_total(x_hi))){
    double x_rt = -2;
    root2 = x_rt;
  }
  
  else{
    double x_rt = f_min(x_lo,x_hi,maxiter,precision,ddx_total);
    //std::cout << "value at root 2 " << mass_energy.total_energy(x_rt) << "\n";
    root2 = x_rt;
  }
  std::cout << "roots "<< root1<<", "<<root2<<"\n";
}

energy::~energy(){
}

double root_diff(double mass){
  energy mass_energy(mass);
  mass_energy.f_min_all();
  return abs(mass_energy.total_energy(mass_energy.root1)-mass_energy.total_energy(mass_energy.root2)));
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


bool samesign(double x, double y)
{
  return (x >= 0) ^ (y < 0);
}
