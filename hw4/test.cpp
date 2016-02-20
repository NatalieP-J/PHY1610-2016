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
  double masscheck = zeromass.mass;
  double test_pot = zeromass.total_energy(test_pos);
  BOOST_CHECK_MESSAGE(test_pot < precision, "Zero mass object has weight");
}
