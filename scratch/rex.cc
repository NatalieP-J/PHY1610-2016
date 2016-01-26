// rex.cc
#include <rarray> 
#include <rarrayio> 
#include <iostream> 
int main() {
  const int n = 3;
  rarray<double,3> a(n,n,n);
  a.fill(4);
  for (int i=0; i<n; i++)
    for (int j=0; j<i; j++)
      for (int k=0; k<j; k++)
        a[i][j][k] =i+j+k;
  std::cout << a << std::endl;
}