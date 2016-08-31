#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define TAM 8	

int A[TAM][TAM], B[TAM][TAM], C[TAM][TAM];

void llenar(int m[TAM][TAM])
{
    for (int i=0; i<TAM; i++)
    {
        for (int j=0; j<TAM; j++)
            m[i][j] = rand()%100;
    }
}

void print(int m[TAM][TAM])
{
    for (int i=0; i<TAM; ++i) 
    {
        for (int j=0; j<TAM; ++j)
            printf("%d\t", m[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    int comm_sz; 
    int	my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_TAM(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank==0)
    {
        fill(A);
        fill(B);
        print(A);
        print(B);
    }

    int ini = my_rank*TAM/comm_sz;
    int end = (my_rank+1)*TAM/comm_sz;

    MPI_Bcast (B, TAM*TAM, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter (A, TAM*TAM/comm_sz, MPI_INT, A[ini], TAM*TAM/comm_sz, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = ini; i < end; ++i)
    { 
        for (int j = 0; j < TAM; ++j) 
        {
            for (int k = 0; k < TAM; ++k)
                C[i][j]+=A[i][k]*B[k][j];
        }
    }

    MPI_Gather(C[ini], TAM*TAM/comm_sz, MPI_INT, C, TAM*TAM/comm_sz, MPI_INT, 0, MPI_COMM_WORLD);

    if (my_rank==0)
        print(C);

    MPI_Finalize();

	return 0;
}