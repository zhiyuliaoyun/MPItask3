#pragma warning(disable:4996)
#include <stdio.h>
#include <mpi.h>
#include <malloc.h>
#include <math.h>
main(int argc, char** argv) {
	int i = 0;
	int my_rank, numprocs;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	if (my_rank % 2 == 0)
	{
		if (my_rank == numprocs - 1){
			printf("end\n");
		}
		else{
			MPI_Send(&i, 1, MPI_INT,my_rank + 1, 20, MPI_COMM_WORLD);
		}
	}
	else if (my_rank % 2 == 1){
		MPI_Recv(&i, 20, MPI_INT, my_rank - 1, 20, MPI_COMM_WORLD, &status);
		printf("%d receive %d from %d\n", my_rank,i,my_rank-1 );
		i = i + 1;
	}
	if (my_rank % 2 == 1){
		if (my_rank == numprocs - 1){
			printf("end\n");
		}
		else{
			MPI_Send(&i, 1, MPI_INT, my_rank + 1, 20, MPI_COMM_WORLD);
		}
	}
	else if (my_rank % 2 == 0){
		MPI_Recv(&i, 1, MPI_INT, my_rank - 1, 20, MPI_COMM_WORLD, &status);
		if (my_rank != 0) {
			printf("%d receive %d from %d\n", my_rank, i, my_rank - 1);
		}
		else {
			printf("i=0\n");
		}
		i = i + 1;
	}

	MPI_Finalize();
}
