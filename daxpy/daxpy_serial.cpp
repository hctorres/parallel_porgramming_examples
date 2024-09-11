#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <exception>

// Precondition
//   x.size() == y.size()
void daxpy(const double a, const std::vector<double>& x, std::vector<double>& y) {
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

  // Set up the clock to report the elapsed time in seconds
  using clock_t = std::chrono::steady_clock;
  using time_point_t = clock_t::time_point;
  using duration_t  = std::chrono::duration<double, std::chrono::seconds::period>;

  // Do the math and time it
  time_point_t time_begin = clock_t::now();
  daxpy(a, x, y);
  time_point_t time_end = clock_t::now();

  duration_t run_duration = std::chrono::duration_cast<duration_t>(time_end - time_begin);
  double run_time_seconds = run_duration.count();

  check_result(y, truth_value);

  std::cout << "vector size = " << vector_size << std::endl;
  std::cout << "run time = " << run_time_seconds << " [s]" << std::endl;

  return 0;
}