#include <rarray>
#include <rarrayio>

#ifndef ARRAYFILL_H
#define ARRAYFILL_H
rarray<float,2> arrayfill(int start, int nrows, int ncols, float (*f)(int,int,int));

float zerofill(int i,int j,int nrows);

float velocityfill(int i,int j,int nrows);
#endif