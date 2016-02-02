// Natalie Price-Jones Jan 2016

#include <rarray>
#include <rarrayio>
#include <cmath>
#include "arrayfill.h"

// function that moves ants over single timestep
rarray<float,2> moveants(int start,int nrows,int ncols, float frac_move,\
                         float velocity_amplitude,rarray<float,2> antarray,\
                         rarray<float,2> antvelocity){
    rarray<float,2> new_antarray = arrayfill(start,nrows,ncols,zerofill);
    for (int i=start;i<nrows;i++) {
            for (int j=start;j<ncols;j++) {
                // calculate how far ants have moved
                int di = velocity_amplitude*sin(antvelocity[i][j]);
                int dj = velocity_amplitude*cos(antvelocity[i][j]);
                // calculate which part of the table ants move to
                int i2 = i + di;
                int j2 = j + dj;
                // some ants do not walk
                new_antarray[i][j]+=(1-frac_move)*antarray[i][j];
                // the rest of the ants walk, but some fall of the table
                // those that remain are added at appropriate part of the table
                if (i2>=start and i2<nrows and j2>=start and j2<ncols) {
                    new_antarray[i2][j2]+=frac_move*antarray[i][j];
                }
            }
        }
    return new_antarray;
}

// function that sums all ants contained in an array
float sumants(int nrows, int ncols,float totants,rarray<float,2> antarray){
    for (int i=0;i<nrows;i++) {
        for (int j=0;j<ncols;j++) {
            totants += antarray[i][j];
        }
    }
    return totants;
}

// function that produces console output for each timestep
void timestep_output(int t, int nrows, int ncols, rarray<float,2> antarray){
    // count how many ants we start with
    float startants = 0.0;
    // calculate the total number of ants, given we started with startants
    float totants = sumants(nrows,ncols,startants,antarray);
    // print timestep and total number of ants to console
    std::cout << t<< " " << totants << std::endl;

}

// function that updates ant positions and produces output for a single timestep
rarray<float,2> timestep(int t,int start, int nrows, int ncols, float frac_move,\
                         float velocity_amplitude,rarray<float,2> antarray,\
                         rarray<float,2> antvelocity){
    // print console output
    timestep_output(t,nrows,ncols,antarray);
    // move the ants into new positions
    rarray<float,2> new_antarray=moveants(start,nrows,ncols,frac_move,\
                                          velocity_amplitude,antarray,\
                                          antvelocity);
    return new_antarray;   
}

