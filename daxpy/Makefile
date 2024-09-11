
all: daxpy_serial daxpy_OpenMP daxpy_MPI

daxpy_serial: daxpy_serial.cpp
	$(CXX) -o daxpy_serial daxpy_serial.cpp

daxpy_OpenMP: daxpy_OpenMP.cpp
	$(CXX) -o daxpy_OpenMP daxpy_OpenMP.cpp -fopenmp 

daxpy_MPI: daxpy_MPI.cpp
	$(MPICXX) -o daxpy_MPI daxpy_MPI.cpp

clean:
	rm -f daxpy_serial daxpy_OpenMP daxpy_MPI