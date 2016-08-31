#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char const *argv[])
{
	int comm_sz; 
	int	my_rank;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int val=0;

	if (my_rank==0)
	{
		printf("Proceso %d tiene valor %d\n",my_rank,val);
		sleep(1);
		val++;
		MPI_Send(&val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	while(val<=20)
	{
		MPI_Recv(&val, 1, MPI_INT, (my_rank+comm_sz-1)%comm_sz, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Proceso %d tiene valor %d\n",my_rank,val);
		sleep(1);
		val++;
		MPI_Send(&val, 1, MPI_INT, (my_rank+1)%comm_sz, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}