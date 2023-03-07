#include <iostream>
#include <vector>
#include <cmath>
#include "timer.hpp"

using namespace std;

int main() {
  const int N = 100'000'000;
  vector<double> vec(N);

  Timer timer;

#pragma omp parallel for
  for(int i=0; i<vec.size(); ++i) {
    vec[i] = sin(M_PI*float(i)/N);
  }

  std::cout << "Time: " << timer.elapsed() << '\n';

  return 0;
}
