#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <chrono>
#include <thread>
#include "timer.hpp"

using namespace std;

int main() {
  const int N = 10'000'000;
  vector<double> vec(N);

  Timer timer;

#pragma omp parallel for schedule(runtime)
  for(int i=0; i<vec.size(); ++i) {
    vec[i] = sin(M_PI*float(i)/N);

    //bool is_thread_even = (omp_get_thread_num()%2 == 0);
    //if (is_thread_even) {
      //std::this_thread::sleep_for(std::chrono::microseconds(1));;
    //}
  }

  std::cout << timer.elapsed() << '\n';

  return 0;
}
