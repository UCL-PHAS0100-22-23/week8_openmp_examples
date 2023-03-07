#include <iostream>
#include <omp.h>

using namespace std;

int main() {

  int a = -1;

  cout << a << endl;

  #pragma omp parallel default(none) firstprivate(a) shared(std::cout)
  {
    std::cout << a << std::endl;
    a = omp_get_thread_num();
    std::cout << a << std::endl;
  }

  cout << a << endl;

  return 0;
}
