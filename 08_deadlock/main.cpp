#include <iostream>
#include <cmath>
#include <omp.h>

int main() {
#pragma omp parallel default(none) shared(std::cout)
  {
    const int thread_num = omp_get_thread_num();

    if(thread_num == 0) {
      std::cout << "I've caused a deadlock!" << std::endl;
    } else {
#pragma omp barrier
    }

#pragma omp critical
    std::cout << "I'm thread " << thread_num << std::endl;
  }

  return 0;
}
