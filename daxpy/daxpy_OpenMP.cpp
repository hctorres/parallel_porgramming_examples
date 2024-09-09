#include <iostream>
#include <vector>
#include <cmath>
#include <exception>

#include "omp.h"

// Precondition
//   x.size() == y.size()
void daxpy(const double a, const std::vector<double>& x, std::vector<double>& y) {
  #pragma omp parallel for
  for (std::vector<double>::size_type i = 0; i < x.size(); ++i) {
    y[i] = a*x[i] + y[i];
  }
}

void check_result(const std::vector<double>& result_vector, const double truth_value) {

  for (const double & value : result_vector) {
    if (value != truth_value) {
      throw std::runtime_error("Error: An element in the result vector does not match the truth value.");
    }
  }

}

int main() {

  // Input
  std::size_t vector_size = pow(10,8);
  double a = 2.0;
  double x_initial_value = 1.0;
  double y_initial_value = 1.0;

  // Expected output
  double truth_value = a*x_initial_value + y_initial_value;

  // Initialize vectors
  std::vector<double> x(vector_size, x_initial_value);
  std::vector<double> y(vector_size, y_initial_value);

  // Do the math and time it
  double time_begin = omp_get_wtime();
  daxpy(a, x, y);
  double time_end = omp_get_wtime();

  double run_time_seconds = time_end - time_begin;

  check_result(y, truth_value);

  std::cout << "vector size = " << vector_size << std::endl;
  std::cout << "run time = " << run_time_seconds << " [s]" << std::endl;

  return 0;
}