// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>

// perform a single time step for the density field
// F: matrix that describes the time evolution
// P: the density
void perform_time_step(const rarray<double,2>& F, rarray<double,1>& P)
{
  int N = F.extent(0);
  rarray<double,1> new_P(P.size());
  cblas_dgemv(CblasRowMajor, CblasNoTrans, N, N, 1.0, F.data(), N, P.data(), 1, 0.0, new_P.data(),1);
  P = new_P.copy();
}

// fill the matrix needed in perform_time_step
// F: matrix that describes the time evolution
// D: the diffusion constant
// dt: the time step to be used
// dx: the spatial resolution
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
  F.fill(0.0);
  int N = F.extent(0);
  double off_diagonal = (D*dt)/pow(dx,2);
  double diagonal = 1 - 2*off_diagonal;
  for (int i=1; i<N; i++){
    F[i-1][i] = off_diagonal;
    F[i][i] = diagonal;
    F[i][i-1] = off_diagonal;
  }
  F[0][0] = diagonal;
  F[N-1][0] = off_diagonal;
  F[0][N-1] = off_diagonal;
}
