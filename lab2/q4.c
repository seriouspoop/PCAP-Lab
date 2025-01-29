#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        int num, recv;
        scanf(" %d", &num);

        MPI_Send(&num, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
        MPI_Recv(&recv, 1, MPI_INT, size - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Recv: %d\n", recv);
        fflush(stdout);
    }
    else
    {
        int recv;
        MPI_Recv(&recv, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Recv: %d\n", recv);
        recv++;
        MPI_Send(&recv, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}