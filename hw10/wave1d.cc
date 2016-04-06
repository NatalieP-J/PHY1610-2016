//
// wave1d.cc - Simulates a one-dimensional damped wave equation modified
// to use pgplot for runtime display of solution with 1 second between frames.  
// 
// SciNet - March 2015

#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <rarray>
#include <cpgplot.h>
#include <mpi.h>
#include "ticktock.h"
#include "inifile.h"

int main(int argc, char* argv[])
{
    // Open inifile and parse (using Inifile class from inifile.h)
    Inifile parameter(argc==1?"default.txt":argv[1]);

    // MPI testing stuff add
    int rank, size;
    int ierr;
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    ierr = MPI_Comm_size(MPI_COMM_WORLD,&size);

    // Physical parameters
    double  c       = parameter.get<double>("c", 1.0);     // wave speed
    double  tau     = parameter.get<double>("tau", 20.0);  // damping time
    double  x1      = parameter.get<double>("x1", -26.0);  // left most x value
    double  x2      = parameter.get<double>("x2", +26.0);  // right most x value

    // Simulation parameters
    double  runtime = parameter.get<double>("runtime", 50.0);   // how long should the simulation try to compute?
    double  dx      = parameter.get<double>("dx", 0.01);        // spatial grid size  //0.02

    // Output parameters
    double  outtime =  parameter.get<double>("outtime", 1.0); // how often should a snapshot of the wave be written out? 

    bool    graphics = parameter.get<bool>("graphics", true);   // output to graphics (with 1 sec delay)  or to a file?

    // Output file name
    const std::string dataFilename = "dataFilename.out";

    // Derived parameters
    int     ngrid   = (x2-x1)/dx;  // number of x points
    int     npnts   = ngrid + 2;   // number of x points including boundary points
    double  dt      = 0.5*dx/c;    // time step size
    int     nsteps  = runtime/dt;  // number of steps of that size to reach runtime
    int     nper    = outtime/dt;  // how many step s between snapshots

    // Report all the values.
    std::cout << "#c        " << c       << std::endl;
    std::cout << "#tau      " << tau     << std::endl;
    std::cout << "#x1       " << x1      << std::endl;
    std::cout << "#x2       " << x2      << std::endl;
    std::cout << "#runtime  " << runtime << std::endl;
    std::cout << "#dx       " << dx      << std::endl;
    std::cout << "#outtime  " << outtime << std::endl; 
    std::cout << "#ngrid    " << ngrid   << std::endl;
    std::cout << "#dt       " << dt      << std::endl;
    std::cout << "#nsteps   " << nsteps  << std::endl;    
    std::cout << "#nper     " << nper    << std::endl;
    std::cout << "#graphics " << int(graphics) << std::endl;

    int local_ngrid = (ngrid/size);
    int local_npnts = (npnts/size); // calculate the number of points (plus guard cells)

    int left_over_npnts = npnts % size;
    
    std::cout << local_npnts << " " << left_over_npnts << std::endl;

    if (left_over_npnts != 0){
      for(int assigned_pts = 0; assigned_pts < left_over_npnts; assigned_pts++){
	if (rank == assigned_pts){
	  local_npnts ++;
	}
      }  
    }

    double local_x1, local_x2;
    int left = rank-1;
    int right = rank+1;
    int tag = 1;
    int istart,isend;
    istart = 0;
    isend = 0;
    if (rank==0){
      local_x1 = x1;
      local_x2 = x1+(local_npnts*dx);
      isend += local_npnts;
      ierr = MPI_Send(&local_x2,1,MPI_DOUBLE,right,tag,MPI_COMM_WORLD);
      ierr = MPI_Send(&isend,1,MPI_INT,right,0,MPI_COMM_WORLD);
    }

    if ((rank>0) && (rank<size-1)){
	ierr = MPI_Recv(&local_x1,1,MPI_DOUBLE,left,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	ierr = MPI_Recv(&istart,1,MPI_INT,left,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	local_x1 += dx;
	local_x2 = local_x1+(local_npnts*dx);
	isend += local_npnts;
	ierr = MPI_Send(&local_x2,1,MPI_DOUBLE,right,tag,MPI_COMM_WORLD);
	ierr = MPI_Send(&isend,1,MPI_INT,right,0,MPI_COMM_WORLD);
      }

    if (rank==size-1){
      ierr = MPI_Recv(&local_x1,1,MPI_DOUBLE,left,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      istart = MPI_Recv(&istart,1,MPI_INT,left,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      local_x1 += dx;
      local_x2 = x2;
    }

    local_npnts+=2;
    std::cout << rank << " " << local_x1 << " " << local_x2 << " " << local_npnts << "\n";
    
    // Define and allocate arrays.
    rarray<float,1> rho_prev(local_npnts); // time step t-1
    rarray<float,1> rho(local_npnts);      // time step t
    rarray<float,1> rho_next(local_npnts); // time step t+1
    rarray<float,1> rho_init(local_npnts); // initial values
    rarray<float,1> x(local_npnts);        // x values

    int global_i;
    // Initialize. Start in the right place and Don't fill guard cells
    for (int i = 1; i < (local_npnts-1); i++) {
      // i-1 -> i-2 to make sure what would be x[0] -> x[1] to preserve the guard cell
      global_i = istart+i
      x[i] = x1 + ((global_i-2)*(x2-x1))/ngrid;
      rho[i] = 0.0;
      rho_prev[i] = 0.0;
      rho_next[i] = 0.0;
      // if local index in appropriate global range, excite
      if (global_i>(npnts/4)+1 && (global_i<3*npnts/4)){
	rho[i] = 0.25 - fabs(float((global_i-1)-npnts/2)/float(npnts));
	rho_prev[i] = rho[i];
	rho_init[i] = rho[i];
	  
			     
      }
    }
       
    // Plot or Write out data.
    std::ofstream dataFile;
    int red, grey, white;

    if (graphics) {
       cpgbeg(0, "/xwindow", 1, 1);
       cpgask(0);
       red = 2; cpgscr(red,1.,0.,0.);
       grey = 3; cpgscr(grey,.2,.2,.2);
       white = 4; cpgscr(white,1.0,1.0,1.0);
       cpgsls(1); cpgslw(6); cpgsci(white);
       cpgslw(2);
       cpgenv(x1, x2, 0., 0.25, 0, 0);
       cpglab("x", "rho", "Wave Test");
       cpgsls(1); cpgslw(6); cpgsci(white);
       cpgline(npnts, x.data(), rho.data());
       cpgsls(2); cpgslw(12); cpgsci(red);
       cpgline(npnts, x.data(), &rho_init[0]);
    } else {     
       dataFile.open(dataFilename.c_str());
       dataFile << nper << ","   
                << npnts       << "\n";
       dataFile << time << "\n";
       for (int i = 0; i < npnts; i++ ) 
          dataFile << x[i] << " " << rho[i] << " \n";  
       dataFile << "\n";
    }
     
    // measure time
    TickTock tt;
    tt.tick();
    
    // Take timesteps
    for (int s = 0; s < nsteps; s++) {

        // Set zero dirichlet boundary conditions
        rho[0] = 0.0;
        rho[ngrid+1] = 0.0;

        // Evolve
        for (int i = 1; i <= ngrid; i++) {
            float laplacian = pow(c/dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
            float friction = (rho[i] - rho_prev[i])/tau;
            rho_next[i] = 2*rho[i] - rho_prev[i] + dt*(laplacian*dt-friction);
        }

        // Rotate array pointers so t+1 becomes the new t etc.
        rarray<float,1> temp;
        temp     = rho_prev;
        rho_prev = rho;
        rho      = rho_next;
        rho_next = temp;  
	
        //Output every nper
        if ((s+1)%nper == 0) {
           if (graphics) {
              cpgbbuf();
              cpgeras();
              cpgsls(1); cpgslw(6); cpgsci(white);
              cpgslw(2);
              cpgenv(x1, x2, 0., 0.25, 0, 0);
              cpglab("x", "rho", "Wave test");  //t=s*dt
              cpgsls(2); cpgslw(12); cpgsci(red);
              cpgline(npnts, x.data(), rho.data());
              cpgsls(1); cpgslw(6); cpgsci(white);
              cpgline(npnts, x.data(), rho_init.data());
              cpgebuf();
              sleep(1); // artificial delay! 
           } else {
              dataFile << time << "\n";
              for (int i = 0; i < npnts; i++ ) 
                 dataFile<< x[i] << " " << rho[i] << "\n"; 
              dataFile << "\n";
           } 
        }
    }
    
    // Output measured runtime.
    std::cout << "Walltime = " << tt.silent_tock() << " sec."  << std::endl;

    // Close file.
    if (not graphics)
       dataFile.close();
    ierr = MPI_Finalize();
    
    return 0;
}
