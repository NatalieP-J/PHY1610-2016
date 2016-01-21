// firstprogram.cc - creates a file with three columns, 
// where the second two are the sin of twice the first 
// and cosine of thrice the first respectively

// Natalie Price-Jones, Jan 2016
 
#include <fstream>
#include <cmath>

// Set up prototype functions of f and g
double f(double x);
double g(double x);

int main()
{

    // Set bounds of x columns
    double col_min = -5;
    double col_max = -col_min;
    
    // Set length of x column
    int col_len = 100;

    // Calculate step size
    double step = (col_max-col_min)/(col_len);
    
    // Create output file name and open it
    std::string fname="lissajous.txt";
    std::ofstream fout(fname);

    // Loop over x column values
    for (double x=col_min; x<col_max-step; x+=step){
        // Assign y and z values
        double y = f(x);
        double z = g(x);
        // Write a line of the three columns to file
        fout << x << " " << y << " " << z << "\n";
  
    }

    // Close output file
    fout.close();

    return 0;

}

// Function to return the sin of twice an input double
double f(double x){
    return sin(2*x);
}

// Function to return the cos of thrice an input double
double g(double x){
    return cos(3*x);
}