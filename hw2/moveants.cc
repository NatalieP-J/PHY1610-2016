#include <rarray>
#include <rarrayio>
#include <cmath>


rarray<float,2> assignants(int nrows, int ncols, float numants,)

float sumants(int nrows, int ncols,rarray<float,2> antarray){
    float totants = 0.0;
    for (int i=0;i<nrows;i++) {
        for (int j=0;j<ncols;j++) {
            totants += antarray[i][j];
        }
    }
    return totants;
}