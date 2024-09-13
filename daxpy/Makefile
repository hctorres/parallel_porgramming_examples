
all: daxpy_serial daxpy_OpenMP daxpy_MPI daxpy_CUDA

daxpy_serial: daxpy_serial.cpp
	$(CXX) -o daxpy_serial daxpy_serial.cpp

daxpy_OpenMP: daxpy_OpenMP.cpp
	$(CXX) -o daxpy_OpenMP daxpy_OpenMP.cpp -fopenmp 

daxpy_MPI: daxpy_MPI.cpp
	$(MPICXX) -o daxpy_MPI daxpy_MPI.cpp

daxpy_CUDA: daxpy_CUDA.cu
	nvcc -o daxpy_CUDA daxpy_CUDA.cu

clean:
	rm -f daxpy_serial daxpy_OpenMP daxpy_MPI daxpy_CUDA