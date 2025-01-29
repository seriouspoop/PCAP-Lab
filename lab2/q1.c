#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mpi.h>

#define MAX_SIZE 100

char *toggleString(char string[], size_t size)
{
    char *temp = malloc(size + 1);
    for (int i = 0; i < size; i++)
    {
        if (islower(string[i]))
        {
            temp[i] = toupper(string[i]);
        }
        else if (isupper(string[i]))
        {
            temp[i] = tolower(string[i]);
        }
        else
        {
            temp[i] = string[i];
        }
    }
    temp[size] = '\0';
    return temp;
}

int main(int argc, char *argv[])
{

    int rank;

    char *buffer, *new_buffer;

    buffer = malloc(MAX_SIZE * sizeof(char));
    new_buffer = malloc(MAX_SIZE * sizeof(char));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;

    if (rank == 0)
    {
        printf("Enter value in master process: ");
        scanf(" %s", buffer);

        MPI_Ssend(buffer, MAX_SIZE, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(new_buffer, MAX_SIZE, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);

        printf("Toggled string: %s\n", new_buffer);
        fflush(stdout);
    }
    else if (rank == 1)
    {
        MPI_Recv(buffer, MAX_SIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        new_buffer = toggleString(buffer, MAX_SIZE);
        MPI_Ssend(new_buffer, MAX_SIZE, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
        fflush(stdout);
    }

    free(buffer);
    free(new_buffer);

    MPI_Finalize();
    return 0;
}