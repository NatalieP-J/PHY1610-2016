// Natalie Price-Jones Jan 2016

// standard modules
#include <rarray>
#include <tuple> // c++11 specific

#ifndef ARRAYFILL_H
#define ARRAYFILL_H

// function that cycles through an array with nrows rows and ncols columns and
// fills it with values according to function f
rarray<float,2> arrayfill(int start, int nrows, int ncols,\
                         float (*f)(int,int,int));

// function that returns zero to be called by arrayfill
float zerofill(int i,int j,int nrows);

// function that returns ant velocity depending on ant position
float velocityfill(int i,int j,int nrows);

// function that assigns ants to starting positions
rarray<float,2> assignants(int start, int nrows, int ncols, float numants, \
                           rarray<float,2> antarray);

// function that returns three arrays, filled with the appropriate values
std::tuple<rarray<float,2>,rarray<float,2>,rarray<float,2>> \
initialize(int start, int nrows, int ncols,float total_ants);

#endif