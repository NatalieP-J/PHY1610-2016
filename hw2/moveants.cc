#include <rarray>
#include <rarrayio>
#include <cmath>
#include "arrayfill.h"


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

rarray<float,2> moveants(int start,int nrows,int ncols, float frac_move,float velocity_amplitude,rarray<float,2> antarray,rarray<float,2> antvelocity){
    rarray<float,2> new_antarray = arrayfill(start,nrows,ncols,zerofill);
    for (int i=start;i<nrows;i++) {
            for (int j=start;j<ncols;j++) {
                int di = velocity_amplitude*sin(antvelocity[i][j]);
                int dj = velocity_amplitude*cos(antvelocity[i][j]);
                int i2 = i + di;
                int j2 = j + dj;
                // some ants do not walk
                new_antarray[i][j]+=(1-frac_move)*antarray[i][j];
                // the rest of the ants walk, but some fall of the table
                if (i2>=start and i2<nrows and j2>=start and j2<ncols) {
                    new_antarray[i2][j2]+=frac_move*antarray[i][j];
                }
            }
        }
    return new_antarray;
}

float sumants(int nrows, int ncols,float totants,rarray<float,2> antarray){
    for (int i=0;i<nrows;i++) {
        for (int j=0;j<ncols;j++) {
            totants += antarray[i][j];
        }
    }
    return totants;
}