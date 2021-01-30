#ifndef __FILEIO_H__

#define __FILEIO_H__

#include <stdio.h>

#include "array.h"

int count_num(FILE *file, size_t *const num);

int create_array(FILE *file, const size_t num, array_t *const array);

int write_to_file(FILE *file, const array_t *const array);

#endif