#include <rarray>
#include <rarrayio>

rarray<float,2> arrayfill(int start, int nrows, int ncols, float (*f)(int,int));

float zerofill(int i,int j);