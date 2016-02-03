// Natalie Price-Jones Jan 2016

#include <rarray>
#include <rarrayio>

#ifndef MOVEANTS_H
#define MOVEANTS_H

// function that moves ants over single timestep
rarray<float,2> moveants(int start,int nrows,int ncols,float frac_move,\
                         float velocity_amplitude,rarray<float,2> antarray,\
                         rarray<float,2> antvelocity);

// function that sums all ants contained in an array
float sumants(int nrows, int ncols,float totants,rarray<float,2> antarray);

// function that produces console output for each timestep
void timestep_output(int t, int nrows, int ncols, rarray<float,2> antarray);

// function that updates ant positions and produces output for a single timestep
rarray<float,2> timestep(int t,int start, int nrows, int ncols, float frac_move,\
                         float velocity_amplitude,rarray<float,2> antarray,\
                         rarray<float,2> antvelocity);

#endif