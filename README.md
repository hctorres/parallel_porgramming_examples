# parallel_programming_examples

This repository contains simple example programs illustrating the use of several popular parallel programming methods (OpenMP, MPI, and CUDA). The "problems" that the example programs solve were intentionally selected to be extremely simple. The intent was to allow the reader to focus on the use of the parallel programming model as opposed to the best way (data structures, algorithms, etc...) to solve the problem.

## daxpy
Similar to the level 1 BLAS routine in LAPACK. Performs a constant (a) times a vector ($\vec{x}$) plus a vector ($\vec{y}$). The result is saved in place over the second vector ($\vec{y}$).

$$ \vec{y} = a \vec{x} + \vec{y} $$

If you are familiar with the LAPACK version of this routine then you may notice that our version is slightly simplified. Here we assume that the storage spacing between elements is always 1 for both vectors ($\vec{x}$ and $\vec{y}$).

