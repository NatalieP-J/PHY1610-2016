#include <cmath>
#include <iostream>
#include "ticktock.h"
int main()
{
    TickTock stopwatch;

    stopwatch.tick();
    // ants walk on a table
    float number_of_ants[356][356];
    float new_number_of_ants[356][356];
    float velocity_of_ants[356][356];
    const int total_ants = 1010; // initial number of ants
    // initialize
    for (int i=0;i<356;i++) {
        for (int j=0;j<356;j++) {
            velocity_of_ants[i][j] = M_PI*(sin((2*M_PI*(i+j))/3560)+1);
        }
    }
    int n = 0;
    float z = 0;
    for (int i=0;i<356;i++) {
        for (int j=0;j<356;j++) {
            number_of_ants[i][j] = 0.0;
        }
    }
    while (n < total_ants) {
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                z += sin(0.3*(i+j));
                if (z>1 and n!=total_ants) {
                    number_of_ants[i][j] += 1;
                    n += 1;
                }
            }
        }
    }

    stopwatch.tock("Array initialization: ");

    TickTock totaltime;

    totaltime.tick();
    // run simulation
    for (int t = 0; t < 40; t++) {
        stopwatch.tick();
        
        float totants = 0.0;
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                totants += number_of_ants[i][j];
            }
        }
        
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                new_number_of_ants[i][j] = 0.0;
            }
        }
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                int di = 1.9*sin(velocity_of_ants[i][j]);
                int dj = 1.9*cos(velocity_of_ants[i][j]);
                int i2 = i + di;
                int j2 = j + dj;
                // some ants do not walk
                new_number_of_ants[i][j]+=0.8*number_of_ants[i][j];
                // the rest of the ants walk, but some fall of the table
                if (i2>=0 and i2<356 and j2>=0 and j2<356) {
                    new_number_of_ants[i2][j2]+=0.2*number_of_ants[i][j];
                }
            }
        }
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                number_of_ants[i][j] = new_number_of_ants[i][j];
            }
        }

        double runtime = stopwatch.silent_tock();

        std::cout << "time step: " << t << " number of ants: " << totants <<  " runtime: " << runtime << std::endl;
    }

    totaltime.tock("Total moving ant runtime: ");

    return 0;
}             
   
