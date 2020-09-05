build:
	mpicxx -fopenmp -c main.c -o main.o
	mpicxx -fopenmp -c cFunctions.c -o cFunctions.o
	mpicxx -fopenmp -c openMPHistogram.c -o openMPHistogram.o
	nvcc -I./inc -c cudaHistogram.cu -o cudaHistogram.o
	mpicxx -fopenmp -o mpiCudaOpenMP  main.o cFunctions.o openMPHistogram.o cudaHistogram.o  /usr/local/cuda-9.1/lib64/libcudart_static.a -ldl -lrt

clean:
	rm -f *.o ./mpiCudaOpenMP

run:
	mpiexec -np 2 ./mpiCudaOpenMP $(FILE)

runOn2:
	mpiexec -np 2 -machinefile  mf  -map-by  node  ./mpiCudaOpenMP $(FILE)
