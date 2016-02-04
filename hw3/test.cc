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
    double precision = 1e-5;

    //initialize arrays (and return them to avoid use of global variables)
    std::tuple<rarray<float,2>,rarray<float,2>,rarray<float,2>> arrays \
                          = initialize(corner,tabdim,tabdim,total_ants);

    //extract results from returned tuple
    rarray<float,2> number_of_ants = std::get<0>(arrays);

    rarray<float,2> new_number_of_ants = std::get<1>(arrays);

    rarray<float,2> velocity_of_ants = std::get<2>(arrays);

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
}
