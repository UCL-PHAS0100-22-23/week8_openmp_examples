#include <iostream>
#include <cmath>
#include <omp.h>

int main() {
#pragma omp parallel default(none) shared(std::cout)
  {
//#pragma omp critical
    {
      const int thread_num = omp_get_thread_num();
      std::cout << thread_num << std::endl;
      std::cout << std::sin(M_PI*(thread_num+1)/4) << std::endl;
      std::cout << thread_num << std::endl;
    }
  }

  return 0;
}
