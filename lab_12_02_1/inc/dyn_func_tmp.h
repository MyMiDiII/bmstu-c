#ifndef __DYN_FUNC_TMP_H__

#define __DYN_FUNC_TMP_H__

#include <stdio.h>

#include "array.h"

typedef void (*fn_print_error_t)(const int);

typedef int (*fn_check_main_parametrs_t)(int, char **);

typedef int (*fn_check_open_file_t)(FILE *, const int);

typedef void (*fn_close_and_free_t)(FILE *, FILE *,
             array_t *, array_t *, const int, int *const);

typedef int (*fn_count_num_t)(FILE *, size_t *const);

typedef int (*fn_create_array_t)(FILE *, const size_t, array_t *const);

typedef int (*fn_write_to_file_t)(FILE *, const array_t *const);

typedef int (*fn_compare_int_t)(const void *const, const void *const);

typedef void (*fn_mysort_t)(void *, size_t, size_t, int (*)(const void *, const void *));

typedef int (*fn_key_t)(const int *, const int *, int **, int **);

#endif
