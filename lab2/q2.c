#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, x;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;

    if (rank == 0)
    {
        x = 3;
        for (int i = 1; i < size; i++)
        {
            MPI_Send(&x, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&x, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        printf("Received number is: %d\n", x);
    }

    MPI_Finalize();
    return 0;
}