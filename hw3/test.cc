// Natalie Price-Jones Feb 2016

#define BOOST_TEST_MODULE myTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <rarray>
#include <cmath>
#include <tuple> // c++11 specific
#include "moveants.h"
#include "arrayfill.h"

BOOST_AUTO_TEST_CASE(my_test){

    const int tabdim = 356; // dimension of the grid on the table
    const int corner = 0; // index of first table grid element
    
    // define ant parameters
    int total_ants = 1010; // initial number of ants
    float frac_move = 0.2; // fraction of ants that move
    float velocity_amplitude=1.9;

    // testing parameters
    double precision = 1e-5; // precision at which to compare doubles

    //initialize arrays (and return them to avoid use of global variables)
    std::tuple<rarray<float,2>,rarray<float,2>,rarray<float,2>> arrays \
                          = initialize(corner,tabdim,tabdim,total_ants);

    //extract results from returned tuple
    rarray<float,2> number_of_ants = std::get<0>(arrays);

    rarray<float,2> new_number_of_ants = std::get<1>(arrays);

    rarray<float,2> velocity_of_ants = std::get<2>(arrays);

    // These are examples of tests to do on arrays - I did not exhaustively perform all permutations, but the gist is there

    BOOST_CHECK_MESSAGE(number_of_ants.size() == new_number_of_ants.size(),"Original ant tracker does not match updated ant tracker size");

    BOOST_CHECK_MESSAGE(number_of_ants.size() == velocity_of_ants.size(),"Ant tracker and ant velocity do not match size");

    BOOST_CHECK_MESSAGE(number_of_ants.extent(0) == new_number_of_ants.extent(0), "Original ant tracker does not match updated ant tracker x-shape");

    BOOST_CHECK_MESSAGE(number_of_ants.extent(1) == new_number_of_ants.extent(1), "Original ant tracker does not match updated ant tracker y-shape");

    double emptytot = sumants(tabdim,tabdim,0,new_number_of_ants);

    BOOST_CHECK_MESSAGE(emptytot<precision,"Updated ant tracker array is not empty");

    // total ants on the table before movement
    double pretot = sumants(tabdim,tabdim,0,number_of_ants);

    BOOST_CHECK_MESSAGE(abs(pretot-total_ants)<precision, "Not all ants were distributed");

    // move the ants
    new_number_of_ants = moveants(corner,tabdim,tabdim,frac_move,\
                                  velocity_amplitude,number_of_ants,\
                                  velocity_of_ants);

    // total ants on the table after movement
    double fintot = sumants(tabdim,tabdim,0, new_number_of_ants);

    BOOST_CHECK_MESSAGE(fintot <= pretot, "Ants were generated during movement");

    BOOST_CHECK_MESSAGE(pretot*frac_move <= fintot, "More ants fell off the table than the fraction that moved");

}
