#ifndef __MATRIX_H__

#define __MATRIX_H__

#include <stddef.h>

typedef struct matrix
{
    size_t rows;
    size_t columns;
    double **data;
} matrix_t;

int matrix_init(size_t rows, size_t columns, matrix_t *const matrix);

double **allocate_data(size_t rows, size_t columns);

void free_data(double **data);

#endif