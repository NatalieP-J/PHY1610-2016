// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <random>

// perform a single time step for the random walkers
// pos: the positions of Z walkers. Z=pos.size()
// N: the number of grid points. All positions should remain between 0
//    and N-1, with periodic boundary conditions
// p: the probability to jump to the left. Also the probability to just right.
//    the probability to stay on the same spot is thus 1-2p.
void perform_time_step(rarray<int,1>& pos, int N, double p)
{
    // PART OF THE ASSIGNMENT!
}


