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
  // find dimension of (square) F and length of P
  int N = F.extent(0);
  // create array to store result of timestep
  rarray<double,1> new_P(N);
  // matrix multiplication
  cblas_dgemv(CblasRowMajor, CblasNoTrans, N, N, 1.0, F.data(), N, P.data(), 1, 0.0, new_P.data(),1);
  // update P to new values
  P = new_P.copy();
}

// fill the matrix needed in perform_time_step
// F: matrix that describes the time evolution
// D: the diffusion constant
// dt: the time step to be used
// dx: the spatial resolution
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
  // calculate the elements of F
  double off_diagonal = (D*dt)/pow(dx,2);
  double diagonal = 1 - 2*off_diagonal;
  // F is mostly zeros, so fill with that
  F.fill(0.0);
  // find dimension of (square) F
  int N = F.extent(0);
  // fill F from the second row.
  for (int i=1; i<N; i++){
    F[i-1][i] = off_diagonal;
    F[i][i] = diagonal;
    F[i][i-1] = off_diagonal;
  }
  // set remaining values needed to have periodic boundaries
  F[N-1][0] = off_diagonal;
  F[0][N-1] = off_diagonal;
  F[0][0] = diagonal;
}
