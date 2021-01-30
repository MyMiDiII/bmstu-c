#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include "matrix.h"

int find_determinant(const matrix_t *const matrix, double *const det);

int add_matrixes(const matrix_t *const matrix1,
                 const matrix_t *const matrix2,
                 matrix_t *const result);

int multiply_matrixes(const matrix_t *const matrix1,
                      const matrix_t *const matrix2,
                      matrix_t *const result);

#endif