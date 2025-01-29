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
        int buffer_attached_size = MPI_BSEND_OVERHEAD + sizeof(int) * size;
        int *buffer_attached = (int *)malloc(buffer_attached_size);
        MPI_Buffer_attach(buffer_attached, buffer_attached_size);

        for (int i = 1; i < size; i++)
        {
            int send = i;
            MPI_Bsend(&send, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

        MPI_Buffer_detach(&buffer_attached, &buffer_attached_size);

        free(buffer_attached);
    }
    else
    {
        int recv;
        MPI_Recv(&recv, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (rank % 2 == 0)
        {
            printf("Recv: %d, square: %d\n", recv, recv * recv);
        }
        else
        {
            printf("Recv: %d, cube: %d\n", recv, recv * recv * recv);
        }
    }

    MPI_Finalize();
    return 0;
}