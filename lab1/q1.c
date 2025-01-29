#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int rank, x = 5;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("rank: %d, pow(%d,%d) = %lf\n", rank, x, rank, pow(x, rank));
    MPI_Finalize();

    return 0;
}