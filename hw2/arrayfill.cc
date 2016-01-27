// Natalie Price-Jones Jan 2016

#include <rarray>
#include <rarrayio>
#include <cmath>
#include <tuple>

// function that cycles through an array with nrows rows and ncols columns and
// fills it with values according to function f
rarray<float,2> arrayfill(int start, int nrows, int ncols, \
                         float (*f)(int,int,int)){

    rarray<float,2> outarray(nrows,ncols);
    for (int i=start;i<nrows;i++){
        for (int j=start;j<ncols;j++){
            // fill the array with the results of function f
            outarray[i][j] = (*f)(i,j,nrows);
        }
    }
    return outarray;
}

// function that returns zero to be called by arrayfill
float zerofill(int i,int j,int nrows){
    return 0.0;
}

// function that returns ant velocity depending on ant position
float velocityfill(int i,int j,int nrows){
    return M_PI*(sin((2*M_PI*(i+j))/(nrows*10))+1);
}

// function that assigns ants to starting positions
rarray<float,2> assignants(int start, int nrows, int ncols, float numants, \
                           rarray<float,2> antarray){
    // initialize ant counter
    int n = 0;
    float z = 0;
    // while we have not used all of our ants, assign ants
    while (n < numants) {
        for (int i=start;i<nrows;i++) {
            for (int j=start;j<ncols;j++) {
                z += sin(0.3*(i+j));
                if (z>1 and n!=numants) {
                    antarray[i][j] += 1;
                    n += 1;
                }
            }
        }
    }
    return antarray;
}

// function that returns three arrays, filled with the appropriate values
std::tuple<rarray<float,2>,rarray<float,2>,rarray<float,2>> \
initialize(int start, int nrows, int ncols,float total_ants){
    
    // initialize arrays
    // fill number_of_ants with zero at all table locations to start
    rarray<float,2> number_of_ants(nrows,ncols);
    number_of_ants = arrayfill(start,nrows,ncols,zerofill);
    
    // initialize array to hold results of ant movement after a timestep
    rarray<float,2> new_number_of_ants(nrows,ncols);
    
    // set the velocity of ants in each part of the grids
    rarray<float,2> velocity_of_ants(nrows,ncols);
    velocity_of_ants = arrayfill(start,nrows,ncols,velocityfill);

    // distribute ants across the table
    number_of_ants = assignants(start,nrows,ncols,total_ants,number_of_ants);

    // return all three arrays
    return std::make_tuple(number_of_ants,new_number_of_ants,velocity_of_ants);
}