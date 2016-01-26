#include <rarray>
#include <rarrayio>

#ifndef MOVEANTS_H
#define MOVEANTS_H
rarray<float,2> assignants(int start, int nrows, int ncols, float numants, rarray<float,2> antarray);
rarray<float,2> moveants(int start,int nrows,int ncols,float frac_move,float velocity_amplitude,rarray<float,2> antarray,rarray<float,2> antvelocity);
float sumants(int nrows, int ncols,float totants,rarray<float,2> antarray);
#endif