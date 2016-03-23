// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <random>

// initialize random number generator
std::default_random_engine engine;
std::uniform_real_distribution<double> uniform(0.0,1.0);

// perform a single time step for the random walkers
// pos: the positions of Z walkers. Z=pos.size()
// N: the number of grid points. All positions should remain between 0
//    and N-1, with periodic boundary conditions
// p: the probability to jump to the left. Also the probability to jump right.
//    the probability to stay on the same spot is thus 1-2p.
void perform_time_step(rarray<int,1>& pos, int N, double p)
{
  int numwalkers = pos.size();
  for (int walker = 0; walker < numwalkers; walker++){
    double state = uniform(engine);
    // check state to see if you need to move
    if (0.0 <= state and state < p){
      // move left
      pos[walker] -= 1;
      // implement periodicity
      if (pos[walker] < 0){
	pos[walker] = N + pos[walker];
      }
    }
    else if (p <= state and state < 2*p){
      // move right
      pos[walker] += 1;
      // implement periodicity
      if (pos[walker] > N){
	pos[walker] = pos[walker] - N;
      }
    }
    else if (2*p <= state and state < 1){
      // stay
      pos[walker] = pos[walker];
    }
  }
    

}


