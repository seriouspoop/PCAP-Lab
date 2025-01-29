#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    char buffer[100];

    if (argv == NULL || argc < 2)
    {
        perror("invalid arguments");
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, argv[1]);
    size_t bufflen = strlen(buffer);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank <= bufflen - 1) // negate the null char '\0'
    {

        if (buffer[rank] >= 'a' && buffer[rank] <= 'z')
        {
            buffer[rank] = toupper(buffer[rank]);
        }
        else if (buffer[rank] >= 'A' && buffer[rank] <= 'Z')
        {
            buffer[rank] = tolower(buffer[rank]);
        }

        printf("%d: %s -> %s\n", rank, argv[1], buffer);
    }

    MPI_Finalize();
    return 0;
}