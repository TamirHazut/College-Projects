Instructions:
	A) Run on a single computer: 
		1) run command: 'make build'
		2) run command: 'make run FILE=<filename>'
	B) Run on 2 computers:
		1) copy the file to a same folder location on both computers
		2) write in the mf file the ip addresses of both computers
		   Note: the first ip address is the address of the one who will activate the program
		3) make build on both computers
		4) run command: 'make runOn2 FILE=<filename>'
		   Note: run this command only on the computer whom written his ip address first on the mf file
		   
This program is using MPICH, OpenMP and Cuda to perform a comparison of 2 sequences.
MPICH:
	Used 1 process to handle files (read/write), the work splits on both processes by spliting the offsets tasks,
	Then each process calls a cuda function which returns a result.
Cuda:
	Receives 2 sequences and create a results scores array.
	Each cuda thread is responsible to comapre 2 sequences based on a single offset and mutant combination
	There is a constant matrix(26x26) that was pre-filled with the weight float value based on the comparison of every 2 possible letters according to the signs ('*' ':' '.' ' ')
	the cuda threads are getting a compare result for their indexes values in complexity of O(1) which allows the program to run faster.
	After creating the results scores array cuda sends it to an OpenMP function that will return the index of that array that holds the highest score for this offset.
OpenMP:
	Create multiple threads, and a bucket at the size of the number of threads.
	Each thread keeps track on the mutant index that gives the highest score in the correct cell of the bucket based on his id.
	After all the threads are done a best mutant index search is taking place between the best mutant indexe that each thread have saved
	
Note: The program keeps tracks at all time on the best result (offset, mutant index, score) based on comparison of the score
	