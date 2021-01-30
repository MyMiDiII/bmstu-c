#ifndef __MATRIX_H__

#define __MATRIX_H__

#include <stdio.h>

typedef struct matrix
{
    int rows;
    int columns;
    int **data;
} matrix_t;

void read_matrix(FILE *file, matrix_t *const matrix);

void matrix_init(matrix_t *const matrix);

void count_negative_neighbors(matrix_t *const matrix);

void delete_zero_columns(matrix_t *const matrix);

void write_matrix(FILE *file, const matrix_t *const matrix);

void free_matrix(matrix_t *matrix);

#endif