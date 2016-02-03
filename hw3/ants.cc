// Natalie Price-Jones Jan 2016

// standard modules
#include <cmath>
#include <iostream>
#include <rarray>
#include <tuple> // c++11 specific

// specific modules
#include "arrayfill.h"  // contains arrayfill, zerofill, velocityfill, 
                        //assignants and initialize
#include "moveants.h"   // contains sumants, moveants, timestep_output and 
                        //timestep
#include "ticktock.h"

int main()
{
    // Start stopwatch for instrumentation
    TickTock stopwatch;
    stopwatch.tick();
    // ants walk on a table
    // define table parameters
    const int tabdim = 356; // dimension of the grid on the table
    const int corner = 0; // index of first table grid element
    
    // define ant parameters
    int total_ants = 1010; // initial number of ants
    float frac_move = 0.2; // fraction of ants that move
    float velocity_amplitude=1.9;

    // define time parameters
    const int tstart = 0;
    const int tstop = 40;

    stopwatch.tock("Variable initialization: ");

    stopwatch.tick();
    //initialize arrays (and return them to avoid use of global variables)
    std::tuple<rarray<float,2>,rarray<float,2>,rarray<float,2>> arrays \
                          = initialize(corner,tabdim,tabdim,total_ants);

    //extract results from returned tuple
    rarray<float,2> number_of_ants = std::get<0>(arrays);

    rarray<float,2> new_number_of_ants = std::get<1>(arrays);

    rarray<float,2> velocity_of_ants = std::get<2>(arrays);

    stopwatch.tock("Array initialization: ");

    TickTock totaltime;

    totaltime.tick();

    // run simulation
    for (int t = tstart; t < tstop; t++) {

        stopwatch.tick();
        new_number_of_ants = moveants(corner,tabdim,tabdim,frac_move,\
                                      velocity_amplitude,number_of_ants,\
                                      velocity_of_ants);
        
        double runtime = stopwatch.silent_tock();
        
        timestep_output(t,tabdim,tabdim, runtime, number_of_ants);

        number_of_ants = new_number_of_ants;
    }

    totaltime.tock("Total moving ant runtime: ");

    return 0;
}  