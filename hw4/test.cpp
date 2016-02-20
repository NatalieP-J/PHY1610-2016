// Natalie Price-Jones Feb 2016

#define BOOST_TEST_MODULE energytest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "energy.h"

BOOST_AUTO_TEST_CAST(energy){
  double mass = 0.1;
  energy* mass_energy = new energy(mass);
}
