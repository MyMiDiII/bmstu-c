#include <stdio.h>

#include "fileio.h"
#include "errors.h"
#include "macrologger.h"
#include "modes.h"
#include "matrix.h"

int fopen_by_mode(FILE **file, const char *const name, const int mode)
{
    LOG_INFO("%s", "fopen_by_mode was started");
    LOG_DEBUG("name = %s", name);

    if (MATRIX1_MODE == mode || MATRIX2_MODE == mode)
        *file = fopen(name, "r");
    else if (RESULTS_MODE == mode)
        *file = fopen(name, "w");
    else
        return ERR_WRONG_MODE;

    if (!*file)
    {
        if (MATRIX1_MODE == mode)
        {
            LOG_ERROR("%s", "ERR_OPEN_MATRIX1_FILE");
            return ERR_OPEN_MATRIX1_FILE;
        }
        else if (MATRIX2_MODE == mode)
        {
            LOG_ERROR("%s", "ERR_OPEN_MATRIX1_FILE");
            return ERR_OPEN_MATRIX2_FILE;
        }
        else
        {
            LOG_ERROR("%s", "ERR_OPEN_RESULTS_FILE");
            return ERR_OPEN_RESULTS_FILE;
        }
    }

    LOG_INFO("%s", "fopen_by_mode was done successfully!");

    return OK;
}

int fread_matrix(FILE *file, matrix_t *const matrix)
{
    LOG_INFO("%s", "fread_matrix was started");

    size_t rows, columns, nonzeros;

    if (read_size(file, &rows) || read_size(file, &columns) ||
        read_size(file, &nonzeros))
    {
        LOG_ERROR("%s", "ERR_READ_SIZES");
        return ERR_READ_SIZES;
    }

    if (nonzeros > rows * columns)
    {
        LOG_ERROR("%s", "ERR_WRONG_MATRIX_SIZES");
        return ERR_WRONG_MATRIX_SIZES;
    }

    int exit_code = matrix_init(rows, columns, matrix);

    if (exit_code)
    {
        LOG_ERROR("%s", "matrix_init error");
        return exit_code;
    }

    for (size_t i = 0; i < nonzeros; i++)
    {
        size_t cur_row, cur_column;
        double element;

        if (read_size(file, &cur_row) || read_size(file, &cur_column)
            || fscanf(file, "%lf", &element) != 1)
        {
            LOG_ERROR("%s", "ERR_READ_FILE");
            return ERR_READ_FILE;
        }

        if (cur_row > rows || cur_column > columns)
        {
            LOG_ERROR("%s", "ERR_WRONG_ELEMENT_PARAMETERS");
            return ERR_WRONG_ELEMENT_PARAMETERS;
        }

        LOG_DEBUG("cur_row = %lu", cur_row - 1);
        LOG_DEBUG("cur_column = %lu", cur_column - 1);
        LOG_DEBUG("element = %lf", element);
        LOG_DEBUG("rows = %ld", matrix->rows);
        LOG_DEBUG("volumns = %ld", matrix->columns);

        matrix->data[cur_column - 1][cur_row - 1] = element;
    }

    LOG_INFO("%s", "fread_matrix was done successfully!");

    return OK;
}

int read_size(FILE *file, size_t *const number)
{
    LOG_INFO("%s", "read_sizes was started");

    long long int llnum;

    if (fscanf(file, "%lld", &llnum) != 1)
    {
        LOG_ERROR("%s", "ERR_READ_SIZES");
        return ERR_READ_SIZES;
    }

    LOG_DEBUG("llnum = %lld", llnum);

    if (llnum <= 0 || llnum > __SIZE_MAX__)
    {
        LOG_ERROR("%s", "ERR_READ_SIZES");
        return ERR_READ_SIZES;
    }

    *number = (size_t) llnum;

    LOG_DEBUG("number = %lu", *number);

    LOG_INFO("%s", "read_sizes was done successfully!");
    
    return OK;
}

int fwrite_matrix(FILE *file, const matrix_t *const matrix)
{
    LOG_INFO("%s", "fwrite_matrix was started");

    size_t rows = matrix->rows;
    size_t columns = matrix->columns;

    LOG_DEBUG("rows = %lu", rows);
    LOG_DEBUG("rows = %lu", columns);

    if (fprintf(file, "%lu %lu\n", rows, columns) < 0)
    {
        LOG_ERROR("%s", "ERR_FPRINTF");
        return ERR_FPRINTF;
    }

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            LOG_DEBUG("cur_element = %lf", matrix->data[j][i]);

            if (fprintf(file, "%lf%s", matrix->data[j][i],
                (j == columns - 1) ? "\n" : " ") < 0)
            {
                LOG_ERROR("%s", "ERR_FPRINTF");
                return ERR_FPRINTF;
            }
        }
    }

    LOG_INFO("%s", "fwrite_matrix was done successfully!");

    return OK;
}

void fclose_by_error(FILE **file, int *const exit_code, const int error)
{
    if (*exit_code < error || !*exit_code)
        if (fclose(*file) == EOF)
            *exit_code = ERR_FCLOSE;
}