#include <rarray>
#include <rarrayio>
#include <tuple>

#ifndef ARRAYFILL_H
#define ARRAYFILL_H
rarray<float,2> arrayfill(int start, int nrows, int ncols, float (*f)(int,int,int));

float zerofill(int i,int j,int nrows);

float velocityfill(int i,int j,int nrows);

rarray<float,2> assignants(int start, int nrows, int ncols, float numants, rarray<float,2> antarray);

std::tuple<rarray<float,2>,rarray<float,2>,rarray<float,2>> initialize(int start, int nrows, int ncols,float total_ants);
#endif