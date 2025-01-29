#include <stdio.h>
#include <mpi.h>
#include <math.h>

int factorial(int num)
{
    if (num == 0)
    {
        return 1;
    }
    return num * factorial(num - 1);
}

int fibb(int num)
{
    if (num == 0 || num == 1)
        return num;
    return fibb(num - 1) + fibb(num - 2);
}

int main(int argc, char *argv[])
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Rank: %d, Fact: %d, Fibb: %d\n", rank, factorial(rank), fibb(rank));

    MPI_Finalize();

    return 0;
}