#include <rarray>
#include <rarrayio>
#include <cmath>

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
    return M_PI*(sin((2*M_PI*(i+j))/nrows*10)+1);
}