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

    // Initialize MPI and associated variables. Retrieve rank and size
    int rank, size;
    int ierr;
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    ierr = MPI_Comm_size(MPI_COMM_WORLD,&size);

    // Calculate the number of points assigned to each process
    int local_npnts = (npnts/size); // (without guard cells)
    
    // Find the number of points left to be assigned after integer division
    int left_over_npnts = npnts % size;

    // Assign each left over point to the processes in numerical sequence  until none are left
    if (left_over_npnts != 0){
      for(int assigned_pts = 0; assigned_pts < left_over_npnts; assigned_pts++){
	if (rank == assigned_pts){
	  local_npnts ++;
	}
      }  
    }

    // Find local x bounds for each process. Also track the global index by finding the global
    // (monolithic) index at which each local array should start
    double local_x1, local_x2;
    // Find the location of the processes to the left and right
    int left = rank-1;
    int right = rank+1;
    // Create tags for the two simultaneous sending processes
    int tag_x = 0;
    int tag_i = 1;
    // Initialize variables for the global index starting point for each process, and the index
    // information to be sent
    int istart,isend;
    istart = 0;
    isend = 0;
    
    // Special left-most edge case
    if (rank==0){
      // Calculate local bounds on x
      local_x1 = x1;
      local_x2 = x1+(local_npnts*dx);
      // Find starting global index of rightward process
      isend += local_npnts;
      if (size > 1){
	// If there are multiple processes, send information
	ierr = MPI_Send(&local_x2,1,MPI_DOUBLE,right,tag_x,MPI_COMM_WORLD);
	ierr = MPI_Send(&isend,1,MPI_INT,right,tag_i,MPI_COMM_WORLD);
      }
    }

    // Case for 'middle' processes
    if ((rank>0) && (rank<size-1)){
      // Recieve from left-hand side
	ierr = MPI_Recv(&local_x1,1,MPI_DOUBLE,left,tag_x,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	ierr = MPI_Recv(&istart,1,MPI_INT,left,tag_i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	local_x2 = local_x1+(local_npnts*dx);
	// Calculate starting global index of rightward process
	isend = istart + local_npnts;
	// Send information
	ierr = MPI_Send(&local_x2,1,MPI_DOUBLE,right,tag_x,MPI_COMM_WORLD);
	ierr = MPI_Send(&isend,1,MPI_INT,right,tag_i,MPI_COMM_WORLD);
      }

    // Special right-most edge case
    if ((rank==size-1) && (rank!=0)){
      // Recieve from left-hand side
      ierr = MPI_Recv(&local_x1,1,MPI_DOUBLE,left,tag_x,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      ierr = MPI_Recv(&istart,1,MPI_INT,left,tag_i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      local_x2 = x2;
    }

    // Add guard cells
    local_npnts+=2;
    // Calculate local_ngrid
    int local_ngrid = (local_x2-local_x1)/dx;
    
    // Define and allocate local arrays.
    rarray<float,1> rho_prev(local_npnts); // time step t-1
    rarray<float,1> rho(local_npnts);      // time step t
    rarray<float,1> rho_next(local_npnts); // time step t+1
    rarray<float,1> rho_init(local_npnts); // initial values
    rarray<float,1> x(local_npnts);        // x values

    // Initialize. Start in the right place and Don't fill guard cells
    for (int i = 1; i < (local_npnts-1); i++) {
      // i-1 -> i-2 to make sure what would be x[0] -> x[1] to preserve the guard cells
      // use the global index to calculate values
      int global_i = istart+i;
      x[i] = x1 + ((global_i-2)*(x2-x1))/ngrid;
      rho[i] = 0.0;
      rho_prev[i] = 0.0;
      rho_next[i] = 0.0;
      // if global index in appropriate global range, excite
      if (global_i>(npnts/4)+1 && (global_i<3*npnts/4)){
	// i -> i-1 to make sure what would be rho[0] -> rho[1] to preserve the guard cells
	rho[i] = 0.25 - fabs(float((global_i-1)-npnts/2)/float(npnts));
	rho_prev[i] = rho[i];
	rho_init[i] = rho[i];
	  
			     
      }
    }
    
    // THE FOLLOWING IS OUTPUT CODE, COMMENTED OUT FOR THE SAKE OF SCALING TESTS
    
    // Plot or Write out data.
    //std::ofstream dataFile;
    int red, grey, white;

    //if (graphics) {
    //   cpgbeg(0, "/xwindow", 1, 1);
    //   cpgask(0);
    //   red = 2; cpgscr(red,1.,0.,0.);
    //   grey = 3; cpgscr(grey,.2,.2,.2);
    //   white = 4; cpgscr(white,1.0,1.0,1.0);
    //   cpgsls(1); cpgslw(6); cpgsci(white);
    //   cpgslw(2);
    //   cpgenv(x1, x2, 0., 0.25, 0, 0);
    //   cpglab("x", "rho", "Wave Test");
    //   cpgsls(1); cpgslw(6); cpgsci(white);
    //   cpgline(npnts, x.data(), rho.data());
    //   cpgsls(2); cpgslw(12); cpgsci(red);
    //   cpgline(npnts, x.data(), &rho_init[0]);
    //} else {     
    //   dataFile.open(dataFilename.c_str());
    //   dataFile << nper << ","   
    //            << npnts       << "\n";
    //   dataFile << time << "\n";
    //   for (int i = 0; i < npnts; i++ ) 
    //      dataFile << x[i] << " " << rho[i] << " \n";  
    //   dataFile << "\n";
    //}
     
    // measure time
    TickTock tt;
    tt.tick();
    
    // Take timesteps
    for (int s = 0; s < nsteps; s++) {

        // Set zero dirichlet boundary conditions
      // Create tags for two send-receive processes
      int tag_to_start = 2;
      int tag_to_end = 3;
      
      if (size > 1){
      // Send appropriate boundary conditions
	if ((rank>=0) && (rank < size-1)){
	  float end = rho[local_ngrid-2];
	  // send end point (value for righthand neighbour's left guard cell)  to the right
	  ierr = MPI_Send(&end,1,MPI_FLOAT,right,tag_to_start,MPI_COMM_WORLD);
	}
	
	if ((rank > 0) && (rank <= size-1)){
	  float start = rho[1];
	  // send start point (value for lefthand neighbour's right guard cell) to the left
	  ierr = MPI_Send(&start,1,MPI_FLOAT,left,tag_to_end,MPI_COMM_WORLD);
	}
      // Recieve appropriate boundary conditions

	if ((rank >= 0) && (rank < size-1)){
	  float end;
	  // recieve end point (right guard cell) from the right
	  ierr = MPI_Recv(&end,1,MPI_FLOAT,right,tag_to_end,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	  rho[local_ngrid-1] = end;
	}
	
	if ((rank > 0) && (rank <= size-1)){
	  float start;
	  // recieve start point (left guard cell) from the left
	  ierr = MPI_Recv(&start,1,MPI_FLOAT,left,tag_to_start,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	  rho[0] = start;
	}

	// Apply Dirichlet
	if (rank==0){
	  rho[0] = 0.0;
	}
	
	if (rank==(size-1)){
	  rho[local_ngrid-1] = 0.0;
	}
      }
      // Handle case with only one process
      else if (size == 1){
	rho[0] = 0.0;
	rho[local_ngrid-1] = 0.0;
      }
      
      // Evolve
        for (int i = 1; i <= local_ngrid; i++) {
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
	
	//THE FOLLOWING IS OUTPUT CODE, COMMENTED OUT FOR THE SAKE OF SCALING TESTS 
	
        //Output every nper
        //if ((s+1)%nper == 0) {
        //   if (graphics) {
        //      cpgbbuf();
        //      cpgeras();
        //      cpgsls(1); cpgslw(6); cpgsci(white);
        //      cpgslw(2);
        //      cpgenv(x1, x2, 0., 0.25, 0, 0);
        //      cpglab("x", "rho", "Wave test");  //t=s*dt
        //      cpgsls(2); cpgslw(12); cpgsci(red);
        //      cpgline(npnts, x.data(), rho.data());
        //      cpgsls(1); cpgslw(6); cpgsci(white);
        //      cpgline(npnts, x.data(), rho_init.data());
        //      cpgebuf();
        //      sleep(1); // artificial delay! 
        //   } else {
        //      dataFile << time << "\n";
        //      for (int i = 0; i < npnts; i++ ) 
        //         dataFile<< x[i] << " " << rho[i] << "\n"; 
        //      dataFile << "\n";
        //   } 
        //}
    }
    
    // Output measured runtime.
    std::cout << "Walltime = " << tt.silent_tock() << " sec."  << std::endl;


    // THE FOLLOWING IS OUTPUT CODE, COMMENTED OUT FOR THE SAKE OF SCALING TESTS 
    // Close file.
    //if (not graphics)
    //   dataFile.close();
    
    // Finish MPI
    ierr = MPI_Finalize();
    
    return 0;
}
