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
  double mass;

public:
  energy(double m);
  double spring_potential(double x);
  double grav_potential(double x);
  double total_energy(double x);
  ~energy();

};
