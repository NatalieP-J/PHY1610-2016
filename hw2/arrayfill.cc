#include <rarray>
#include <rarrayio>
#include <cmath>
#include <tuple>

// function to cycle through an array of a given size from a given starting point, assigning values to each element
rarray<float,2> arrayfill(int start, int nrows, int ncols, float (*f)(int,int,int)){

    rarray<float,2> outarray(nrows,ncols);
    for (int i=start;i<nrows;i++){
        for (int j=start;j<ncols;j++){
            outarray[i][j] = (*f)(i,j,nrows);
        }
    }
    return outarray;
}

// function that can be fed to arrayfill that returns 0
float zerofill(int i,int j,int nrows){
    return 0.0;
}

// function that can be fed to arrayfill that returns a value based on array position and size
float velocityfill(int i,int j,int nrows){
    return M_PI*(sin((2*M_PI*(i+j))/(nrows*10))+1);
}

rarray<float,2> assignants(int start, int nrows, int ncols, float numants, rarray<float,2> antarray){
    int n = 0;
    float z = 0;

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

std::tuple<rarray<float,2>,rarray<float,2>,rarray<float,2>> initialize(int start, int nrows, int ncols,float total_ants){
    // initialize arrays
    rarray<float,2> number_of_ants(nrows,ncols);
    number_of_ants = arrayfill(start,nrows,ncols,zerofill);
    
    rarray<float,2> new_number_of_ants(nrows,ncols);
    
    rarray<float,2> velocity_of_ants(nrows,ncols);
    velocity_of_ants = arrayfill(start,nrows,ncols,velocityfill);

    // distribute ants across the table
    number_of_ants = assignants(start,nrows,ncols,total_ants,number_of_ants);

    return std::make_tuple(number_of_ants,new_number_of_ants,velocity_of_ants);
}