#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[])
{
	int comm_sz; 
	int	my_rank;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int val=0;

	if(my_rank==0)
	{
		val=123;
		printf("Enviando val=%d\n", val);
		for (int i = 1; i < comm_sz; ++i)
			MPI_Send(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Proceso %d recibe val=%d\n",my_rank,val);
	}
	
	MPI_Finalize();
	return 0;
}