#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;

    if (argv == NULL || argc < 3)
    {
        perror("invalid arguments");
        exit(EXIT_FAILURE);
    }

    int op1 = atoi(argv[1]), op2 = atoi(argv[2]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    switch (rank)
    {
    case 1:
        printf("%d+%d=%d\n", op1, op2, op1 + op2);
        break;
    case 2:
        printf("%d-%d=%d\n", op1, op2, op1 - op2);
        break;
    case 3:
        printf("%d*%d=%d\n", op1, op2, op1 * op2);
        break;
    case 4:
        printf("%d/%d=%f\n", op1, op2, (double)op1 / op2);
        break;
    case 5:
        printf("%d%%d=%d\n", op1, op2, op1 % op2);
        break;
    default:
        printf("operator not defined\n");
        break;
    }

    MPI_Finalize();
    return 0;
}