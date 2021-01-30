#include <stdlib.h>

#include "actions.h"
#include "matrix.h"
#include "macrologger.h"
#include "errors.h"

int det(double **data, const size_t demention,
        double *const determinant)
{
    LOG_INFO("%s", "det was started");

    if (!data || !determinant)
    {
        LOG_ERROR("%s", "ERR_NULL_POINTER");
        return ERR_NULL_POINTER;
    }

    LOG_DEBUG("demention = %lu", demention);
    if (1 == demention)
    {
        *determinant = data[0][0];
        return OK;
    }
    
    if (2 == demention)
    {
        *determinant = data[0][0] * data[1][1] - data[0][1] * data[1][0];
        return OK;
    }

    int sign = 1;
    for (size_t i = 0; i < demention; i++)
    {
        double **subdata = malloc(sizeof(double *) * (demention - 1));
        if (!subdata)
        {
            LOG_ERROR("%s", "ERR_MEMORY_ALLOCATION");
            return ERR_MEMORY_ALLOCATION;
        }

        size_t subindex = 0;
        for (size_t j = 0; j < demention; j++)
        {
            if (j != i)
            {
                subdata[subindex++] = data[j] + 1;

                LOG_DEBUG("subdata[%lu] = %p", subindex - 1,
                          (void *) subdata[subindex - 1]);
                LOG_DEBUG("data[%lu] = %p", j, (void *) data[j]);
            }
        }

        double subdet;
        int exit_code = det(subdata, demention - 1, &subdet);
        free(subdata);

        if (exit_code)
            return exit_code;

        LOG_DEBUG("sign = %d", sign);
        LOG_DEBUG("data[0][%lu] = %lf", i, data[i][0]);
        LOG_DEBUG("subdet = %lf", subdet);

        *determinant += sign * data[i][0] * subdet;

        LOG_DEBUG("determinant = %lf", *determinant);
        sign *= -1;
    }

    LOG_INFO("%s", "det was done successfully!");
    return OK;
}

int find_determinant(const matrix_t *const matrix, double *const determinant)
{
    LOG_INFO("%s", "find_determinant was started!");

    if (!matrix->rows || !matrix->columns)
    {
        LOG_ERROR("%s", "ERR_ZERO_DEMENSIONS");
        return ERR_ZERO_DEMENSIONS;
    }
    if (matrix->rows != matrix->columns)
    {
        LOG_ERROR("%s", "ERR_NONSQUARE");
        return ERR_NONSQUARE;
    }

    *determinant = 0;
    return det(matrix->data, matrix->rows, determinant);
}

int add_matrixes(const matrix_t *const matrix1,
                 const matrix_t *const matrix2,
                 matrix_t *const result)
{
    LOG_INFO("%s", "add_matrixes was started!");

    if (!matrix1 || !matrix2 || !result)
    {
        LOG_ERROR("%s", "ERR_NULL_POINTER");
        return ERR_NULL_POINTER;
    }

    if (matrix1->rows != matrix2->rows ||
        matrix1->columns != matrix2->columns)
    {
        LOG_ERROR("%s", "ERR_WRONG_MATRIX_SIZES");
        return ERR_WRONG_MATRIX_SIZES;
    }

    int exit_code = matrix_init(matrix1->rows, matrix1->columns, result);

    if (exit_code)
        return exit_code;

    for (size_t i = 0; i < matrix1->rows; i++)
    {
        for (size_t j = 0; j < matrix2->columns; j++)
        {
            result->data[j][i] = matrix1->data[j][i] + matrix2->data[j][i];
            LOG_DEBUG("result->data[%lu][%lu] = %lf", j, i, result->data[j][i]);
        }
    }

    LOG_INFO("%s", "add_matrixes was done successfully!");
    return OK;
}

int multiply_matrixes(const matrix_t *const matrix1,
                      const matrix_t *const matrix2,
                      matrix_t *const result)
{
    LOG_INFO("%s", "multiply_matrixes was started!");

    if (!matrix1 || !matrix2 || !result)
    {
        LOG_ERROR("%s", "ERR_NULL_POINTER");
        return ERR_NULL_POINTER;
    }

    if (matrix1->columns != matrix2->rows)
    {
        LOG_ERROR("%s", "ERR_WRONG_MATRIX_SIZES");
        return ERR_WRONG_MATRIX_SIZES;
    }

    int exit_code = matrix_init(matrix1->rows, matrix2->columns, result);

    if (exit_code)
        return exit_code;

    for (size_t i = 0; i < result->rows; i++)
    {
        for (size_t j = 0; j < result->columns; j++)
        {
            result->data[j][i] = 0;
            for (size_t k = 0; k < matrix1->columns; k++)
            {
                result->data[j][i] += matrix1->data[k][i] * matrix2->data[j][k];
                LOG_DEBUG("%lf", result->data[j][i]);
            }
        }
    }

    LOG_INFO("%s", "multiply_matrixes was done successfully!");
    return OK;
}