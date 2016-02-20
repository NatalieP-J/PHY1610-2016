// Natalie Price-Jones Feb 2016

#define BOOST_TEST_MODULE energytest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "energy.h"

BOOST_AUTO_TEST_CASE(energytest){
  double precision = 1e-10;
  
  double m = 0;
  double test_pos = 0.4;
  
  energy zeromass(m);
  
  double test_grav_pot = zeromass.grav_potential(test_pos);
  BOOST_CHECK_MESSAGE(test_grav_pot < precision, "Zero mass object has weight");
  double test_spring_pot = zeromass.spring_potential(test_pos);
  double test_pot = zeromass.total_energy(test_pos);
  BOOST_CHECK_MESSAGE(abs(test_spring_pot-test_pot) < precision, "Total mass not equal to spring potential even with no gravity");
  double masscheck = zeromass.mass;
  BOOST_CHECK_MESSAGE(abs(masscheck - m) < precision, "Mass changed after energy calculation");


}
