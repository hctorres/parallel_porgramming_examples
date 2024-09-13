#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <exception>

#include <cuda_runtime.h>

// Precondition
__global__
void daxpy(const double a, const double * x, double * y, const std::size_t n) {
  std::size_t i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) {
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

  // Initialize vectors on host
  std::vector<double> x(vector_size, x_initial_value);
  std::vector<double> y(vector_size, y_initial_value);

  // Initialize vectors on device
  double* x_device;
  cudaMalloc(&x_device, x.size()*sizeof(double));
  cudaMemcpy(x_device, x.data(), x.size()*sizeof(double), cudaMemcpyHostToDevice);

  double* y_device;
  cudaMalloc(&y_device, y.size()*sizeof(double));
  cudaMemcpy(y_device, y.data(), y.size()*sizeof(double), cudaMemcpyHostToDevice);

  // Set up the clock to report the elapsed time in seconds
  using clock_t = std::chrono::steady_clock;
  using time_point_t = clock_t::time_point;
  using duration_t  = std::chrono::duration<double, std::chrono::seconds::period>;

  int threads_per_block = 256;
  int blocks_per_grid = (x.size() + threads_per_block - 1) / threads_per_block; // int division but rounds up. In case problem size is not evenly divisable by threads_per_block. 

  // Do the math and time it
  time_point_t time_begin = clock_t::now();
  daxpy<<<blocks_per_grid,threads_per_block>>>(a, x_device, y_device, x.size());
  cudaDeviceSynchronize(); // Need this so we time the kernel execution time and not just kernel launch time.
  time_point_t time_end = clock_t::now();

  duration_t run_duration = std::chrono::duration_cast<duration_t>(time_end - time_begin);
  double run_time_seconds = run_duration.count();

  cudaMemcpy(y.data(), y_device, y.size()*sizeof(double), cudaMemcpyDeviceToHost);
  cudaFree(x_device);
  cudaFree(y_device);

  check_result(y, truth_value);

  std::cout << "vector size = " << vector_size << std::endl;
  std::cout << "run time = " << run_time_seconds << " [s]" << std::endl;

  return 0;
}