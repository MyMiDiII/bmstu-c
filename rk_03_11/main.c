#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define OK 0 

int main(int argc, char **argv)
{
    FILE *in;
    FILE *out;
    matrix_t matrix;

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    read_matrix(in, &matrix);
    count_negative_neighbors(&matrix);
    delete_zero_columns(&matrix);
    write_matrix(out, &matrix);

    free_matrix(&matrix);
    fclose(in);
    fclose(out);

    return OK;
}