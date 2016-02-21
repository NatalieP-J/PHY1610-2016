#ifndef ENERGY_H
#define ENERGY_H

class energy{
private:

  const float a = 1;
  const float b = 0.1;
  const float c = 100;
  const float d = 0.5;
  const float f = 2500;
  const float g = 9.8;
  
public:
  energy(double m);
  double mass;
  double root1;
  double root2;
  double spring_potential(double x);
  double grav_potential(double x);
  double total_energy(double x);
  double ddx_spring(double x);
  double ddx_grav(double x);
  double ddx_total(double x);
  double f_min(double x_lo, double x_hi, int maxiter, double precision, double (*f)(double));
  void f_min_all();
  double root_diff();
  ~energy();

};

maximum_load();

#endif
