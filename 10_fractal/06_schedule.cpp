#include <math.h>
#include <cmath>
#include <chrono>
#include <iostream>
#include <complex>
#include <vector>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {
  //const bool PLOT_ENABLED = true;
  //const int NPOINTS_X = 68;
  //const int NPOINTS_Y = 31;

  const bool PLOT_ENABLED = false;
  const int NPOINTS_X = 1024;
  const int NPOINTS_Y = NPOINTS_X;
  const int MAXITER = 1024;

  double x_min = -2.0;
  double x_max = 0.42;
  double y_max = 0.85;
  double y_min = -y_max;

  double dx = (x_max - x_min)/(NPOINTS_X-1);
  double dy = (y_max - y_min)/(NPOINTS_Y-1);

  std::complex<double> z, c;
  int n_outside = 0;

  std::vector<char> plot(NPOINTS_X*NPOINTS_Y);

  auto start = high_resolution_clock::now();

  // Iterate over entire domain
#pragma omp parallel for private(z, c) reduction(+:n_outside) collapse(2) schedule(guided)
  for(int i=0; i<NPOINTS_X; ++i) {
    for(int j=0; j<NPOINTS_Y; ++j) {
      // Set c to point inside domain
      c.real(x_min + i*dx);
      c.imag(y_min + j*dy);

      // Initial condition for z is c
      z = c;
      bool is_outside = false;

      for (int iter=0; iter<MAXITER; iter++){
        // Iterate z = z^2 + c
        z = z*z + c;

        // If |z| > 2, point is outside Mandelbrot set
        is_outside = std::abs(z) > 2.0;
        if (is_outside) {
          n_outside++; 
          break;
        }
      }

      if(PLOT_ENABLED) {
        if (is_outside) {
          plot[i*NPOINTS_Y + j] = ' ';
        } else {
          plot[i*NPOINTS_Y + j] = '*';
        }
      }
    }
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start).count();

  double prop_inside = (double)(NPOINTS_X*NPOINTS_Y-n_outside)/(double)(NPOINTS_X*NPOINTS_Y);
  double area = (x_max-x_min)*(y_max-y_min)*prop_inside;
  double error = std::abs(area - 1.506484);

  if(PLOT_ENABLED) {
    for(int j=0; j<NPOINTS_Y; ++j) {
      for(int i=0; i<NPOINTS_X; ++i) {
        std::cout << plot[i*NPOINTS_Y + j];
      }
      std::cout << "\n";
    }
  }

  std::cout << "Area of Mandlebrot set = " << area << std::endl;
  std::cout << "Error = " << error << std::endl;
  std::cout << "Time = " << duration << " ms" << std::endl;
}
