#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

void read_matrix(FILE *file, matrix_t *const matrix)
{
    fscanf(file, "%d%d", &matrix->rows, &matrix->columns);

    matrix_init(matrix);

    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            fscanf(file, "%d", &matrix->data[j][i]);
}

void matrix_init(matrix_t *const matrix)
{
    matrix->data = malloc(matrix->columns * sizeof(int *));

    for (int j = 0; j < matrix->columns; j++)
        matrix->data[j] = malloc(matrix->rows * sizeof(int));
}

void count_negative_neighbors(matrix_t *const matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            if (matrix->data[j][i] == 0)
            {
                for (int k = j - 1; k <= j + 1; k++)
                {
                    if (i != 0 && k > -1 && k < matrix->columns &&
                        matrix->data[k][i - 1] == -1)
                        matrix->data[j][i]++;

                    if (k > -1 && k < matrix->columns && k != j
                        && matrix->data[k][i] == -1)
                        matrix->data[j][i]++;

                    if (i != matrix->rows - 1 && k > -1
                        && k < matrix->columns && matrix->data[k][i + 1] == -1)
                        matrix->data[j][i]++;
                }
            }
        }
    }
}

void delete_zero_columns(matrix_t *const matrix)
{
    for (int j = 0; j < matrix->columns; j++)
    {
        int count_nonzero = 0;
        for (int i = 0; i < matrix->rows && !count_nonzero; i++)
        {
            if (matrix->data[j][i] != 0)
                count_nonzero++;
        }

        if (!count_nonzero)
        {
            free(matrix->data[j]);
            matrix->columns--;
            for (int k = j; k < matrix->columns; k++)
                matrix->data[j] = matrix->data[j + 1];
        }
    }
}

void write_matrix(FILE *file, const matrix_t *const matrix)
{
    int nonzeros = 0;

    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            if (matrix->data[j][i] != 0)
                nonzeros++;

    fprintf(file, "%d %d %d\n", matrix->rows, matrix->columns,
            nonzeros);

    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            if (matrix->data[j][i] != 0)
                fprintf(file, "%d %d %d\n", i + 1, j + 1, matrix->data[j][i]);
}

void free_matrix(matrix_t *matrix)
{
    for (int j = 0; j < matrix->columns; j++)
        free(matrix->data[j]);

    free(matrix->data);
    matrix->rows = 0;
    matrix->columns = 0;
}