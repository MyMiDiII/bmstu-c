#ifndef __FILEIO_H__

#define __FILEIO_H__

#include <stdio.h>
#include "matrix.h"

int fopen_by_mode(FILE **file, const char *const name, const int mode);

int fread_matrix(FILE *file, matrix_t *const matrix);

int read_size(FILE *file, size_t *const number);

int fwrite_matrix(FILE *file, const matrix_t *const matrix);

void fclose_by_error(FILE **file, int *const exit_code, const int error);

#endif