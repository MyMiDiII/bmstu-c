#include <stdlib.h>

#include "matrix.h"
#include "errors.h"
#include "macrologger.h"

int matrix_init(size_t rows, size_t columns, matrix_t *const matrix)
{
    LOG_INFO("%s", "matrix_init was started");

    if (!rows || !columns)
    {
        LOG_ERROR("%s", "ERR_ZERO_DEMENSIONS");
        return ERR_ZERO_DEMENSIONS;
    }

    matrix->rows = rows;
    matrix->columns = columns;

    LOG_DEBUG("matrix->rows = %lu, matrix->columns = %lu",
              matrix->rows, matrix->columns);

    matrix->data = allocate_data(rows, columns);

    LOG_DEBUG("matrix->data = %p", (void *) matrix->data);

    if (!matrix->data)
    {
        LOG_ERROR("%s", "ERR_MEMORY_ALLOCATION");
        return ERR_MEMORY_ALLOCATION;
    }

    LOG_INFO("%s", "matrix_init was done successfully!");

    return OK;
}

double **allocate_data(size_t rows, size_t columns)
{
    LOG_INFO("%s", "matrix_init was started");

    double **data = malloc(sizeof(double *) * columns +
                           sizeof(double) * rows * columns);

    LOG_DEBUG("data = %p", (void *) data);

    if (!data)
    {
        LOG_ERROR("%s", "Memory allocation error!");
        return NULL;
    }

    char *ptr_cur_column = (char *) data + columns * sizeof(double *);
    LOG_DEBUG("ptr_cur_row = %p", ptr_cur_column);
    memset(ptr_cur_column, 0, sizeof(double) * rows * columns);

    for (size_t i = 0; i < columns; i++)
    {
        data[i] = (double *) ptr_cur_column;
        LOG_DEBUG("data[i] = %p", (void *) data[i]);

        ptr_cur_column += rows * sizeof(double);
        LOG_DEBUG("ptr_cur_row = %p", ptr_cur_column);
    }

    LOG_INFO("%s", "allocate_matrix was done successfully!");

    return data;
}

void free_data(double **data)
{
    LOG_INFO("%s", "free_matrix was started");
    free(data);
    LOG_INFO("%s", "free_matrix was done successfully!");
}