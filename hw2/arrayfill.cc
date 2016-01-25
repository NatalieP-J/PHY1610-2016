#include <rarray>
#include <rarrayio>

rarray<float,2> arrayfill(int start, int nrows, int ncols, float (*f)(int,int)){

    rarray<float,2> outarray(nrows,ncols);
    for (int i=start;i<nrows;i++){
        for (int j=start;j<ncols;j++){
            outarray[i][j] = (*f)(i,j);
        }
    }
    return outarray;
}

float zerofill(int i,int j){
    return 0.0;
}
