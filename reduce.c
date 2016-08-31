#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int val;

	int count=2;

	int comm_sz; 
	int	my_rank;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	val=15;
	printf("Proceso %d tiene valor %d\n", my_rank, val);

	while(count<=comm_sz)
	{
		if(my_rank%count==0)
		{
			printf("proceso %d recibe\n", my_rank);
			int tmp=val;
			MPI_Recv(&val, 1, MPI_INT, my_rank+(count/2), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			val+=tmp;
			printf("Proceso %d ahora tiene valor %d\n", my_rank, val);
		}
		else if((my_rank-(count/2))%count==0)
		{
			printf("proceso %d manda\n", my_rank);
			MPI_Send(&val, 1, MPI_INT, my_rank-(count/2), 0, MPI_COMM_WORLD);
		}
		count=count*2;
	}
	

	MPI_Finalize();
	return 0;
}