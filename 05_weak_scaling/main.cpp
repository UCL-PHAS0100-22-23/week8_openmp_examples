#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include "timer.hpp"

using namespace std;

int main() {
  const int n_threads = omp_get_max_threads();
  const int N = 100'000'000 * n_threads;
  vector<double> vec(N);

#pragma omp parallel for
  for(int i=0; i<vec.size(); ++i) {
    vec[i] = sin(M_PI*float(i)/N);
  }

  double sum = 0.;

  Timer timer;

#pragma omp parallel for reduction(+:sum)
  for(int i=0; i<vec.size(); ++i) {
    sum += vec[i];
  }

  double elapsed = timer.elapsed();

  cout << "| " << n_threads << " | " << N << " | " << elapsed << " |\n";

  return 0;
}
