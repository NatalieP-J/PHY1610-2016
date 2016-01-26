//why can there be a fractional number of ants left on the table?

#include "arrayfill.h" // contains arrayfill, zerofill, velocityfill
#include "moveants.h" // contains assignants, sumants, moveants
#include <cmath>
#include <iostream>
#include <rarray>
#include <rarrayio>

int main()
{
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

    // initialize arrays
    rarray<float,2> number_of_ants(tabdim,tabdim);
    number_of_ants = arrayfill(corner, tabdim, tabdim, zerofill);
    
    rarray<float,2> new_number_of_ants(tabdim,tabdim);
    
    rarray<float,2> velocity_of_ants(tabdim,tabdim);
    velocity_of_ants = arrayfill(corner,tabdim,tabdim,velocityfill);

    // distribute ants across the table
    number_of_ants = assignants(corner, tabdim, tabdim, total_ants, number_of_ants);


    // run simulation
    for (int t = tstart; t < tstop; t++) {
        
        float startants = 0.0;
        float totants = sumants(tabdim,tabdim,startants,number_of_ants);
        
        std::cout << t<< " " << totants << std::endl;

        new_number_of_ants = moveants(corner,tabdim,tabdim,frac_move,velocity_amplitude,number_of_ants,velocity_of_ants);

        number_of_ants = new_number_of_ants;
        totants = sumants(tabdim,tabdim,totants,number_of_ants);

    }
    return 0;
}  