#! /bin/bash


echo "#########"
echo "Serial"
echo "#########"
./daxpy_serial
echo ""

echo "#########"
echo "OpenMP"
echo "#########"
for np in 1 2 4
do
  echo "${np} threads"
  OMP_NUM_THREADS=${np} ./daxpy_OpenMP
  echo ""
done
echo ""

echo "#########"
echo "MPI"
echo "#########"
for np in 1 2 4
do
  echo "${np} ranks"
  mpiexec -n ${np} ./daxpy_MPI
  echo ""
done