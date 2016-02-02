#include <cmath>
#include <iostream>
#include "moveants.h"
#include "arrayfill.h"
#include <rarray>
int main()
{
    // ants walk on a table
    rarray<float,2> number_of_ants(356,356);
    rarray<float,2> new_number_of_ants(356,356);
    rarray<float,2> velocity_of_ants(356,356);
    const int total_ants = 1010; // initial number of ants
    // initialize

    
    
    int n = 0;
    float z = 0;
    number_of_ants = arrayfill(0,356,356, zerofill);
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
    // run simulation
    for (int t = 0; t < 40; t++) {
        float totants = 0.0;
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                totants += number_of_ants[i][j];
            }
        }
        std::cout << t<< " " << totants << std::endl;
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                new_number_of_ants[i][j] = 0.0;
            }
        }
       // for (int i=0;i<356;i++) {
       //     for (int j=0;j<356;j++) {
       //         int di = 1.9*sin(velocity_of_ants[i][j]);
       //         int dj = 1.9*cos(velocity_of_ants[i][j]);
       //         int i2 = i + di;
       //         int j2 = j + dj;
                // some ants do not walk
       //         new_number_of_ants[i][j]+=0.8*number_of_ants[i][j];
                // the rest of the ants walk, but some fall of the table
       //         if (i2>=0 and i2<356 and j2>=0 and j2<356) {
       //             new_number_of_ants[i2][j2]+=0.2*number_of_ants[i][j];
       //         }
       //     }
       // }
        new_number_of_ants = moveants(0,356,356,0.2,1.9,number_of_ants,velocity_of_ants);
        for (int i=0;i<356;i++) {
            for (int j=0;j<356;j++) {
                number_of_ants[i][j] = new_number_of_ants[i][j];
                totants += number_of_ants[i][j];
            }
        }
    }
    return 0;
}  