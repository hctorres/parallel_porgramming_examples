#include <iostream>
#include <vector>
#include <cmath>
#include <exception>

#include "mpi.h"

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

  MPI_Init(NULL, NULL);

  // Input
  std::size_t global_vector_size = pow(10,8); // This is the size of the global vector that distributed accross all ranks.
  double a = 2.0;
  double x_initial_value = 1.0;
  double y_initial_value = 1.0;

  // Expected output
  double truth_value = a*x_initial_value + y_initial_value;

  // Initialize vectors
  int comm_size;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  int comm_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

  std::size_t local_vector_size = global_vector_size/comm_size;

  // Fix the local vector size in for last rank:
  //     parallel                last rank                  problem size not evenly divisable
  if ((comm_size > 1) && (comm_rank == (comm_size-1)) && ((global_vector_size%comm_size) != 0) ) {
    local_vector_size = global_vector_size - (comm_rank*local_vector_size);
  }

  std::vector<double> x(local_vector_size, x_initial_value);
  std::vector<double> y(local_vector_size, y_initial_value);

  // Do the math and time it
  double time_begin = MPI_Wtime();
  daxpy(a, x, y);
  double time_end = MPI_Wtime();

  double run_time_seconds = time_end - time_begin;

  check_result(y, truth_value);

  // Take the maximum runtime across all ranks as the runtime of the program
  double max_time;
  MPI_Reduce(&run_time_seconds, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  // Optional print of runtime on each rank
  //std::cout << "rank = " << comm_rank << ", local vector size = " << local_vector_size << ", local run time = " << run_time_seconds << " [s]" << std::endl;

  if (comm_rank == 0) {
    std::cout << "global vector size = " << global_vector_size << ", run time = " << max_time << " [s]" << std::endl;
  }

  MPI_Finalize();

  return 0;
}