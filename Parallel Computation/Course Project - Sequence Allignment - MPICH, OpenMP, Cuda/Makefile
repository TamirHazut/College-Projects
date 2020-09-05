build:
	mpicxx -fopenmp -c main.c -o main.o
	mpicxx -fopenmp -c GeneralFunc.c -o GeneralFunc.o
	mpicxx -fopenmp -c OpenMPFunc.c -o OpenMPFunc.o
	nvcc -I./inc -c CudaFunc.cu -o CudaFunc.o
	mpicxx -fopenmp -o mpiCudaOpenMP main.o GeneralFunc.o OpenMPFunc.o CudaFunc.o /usr/local/cuda-9.1/lib64/libcudart_static.a -ldl -lrt

clean:
	rm -f *.o ./mpiCudaOpenMP

run:
	mpiexec -np 2 ./mpiCudaOpenMP $(FILE)

runOn2:
	mpiexec -np 2 -machinefile  mf  -map-by  node  ./mpiCudaOpenMP $(FILE)
