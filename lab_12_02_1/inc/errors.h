#ifndef __ERRORS_H__

#define __ERRORS_H__

#include <stdio.h>

#include "array.h"

#define OK 0
#define ERR_FCLOSE -1
#define ERR_INVALID_MAIN_PARAMETERS -2
#define ERR_OPEN_INPUT_FILE -3
#define ERR_OPEN_OUTPUT_FILE -4
#define ERR_EMPTY_FILE -5
#define ERR_READ_FILE -6
#define ERR_FSEEK -7
#define ERR_CREATE_ARRAY -8
#define ERR_EMPTY_FILTER -9
#define ERR_NULL_POINTER -10
#define ERR_WRONG_POINTERS -11
#define ERR_CREATE_FILTERED_ARRAY -12
#define ERR_FPRINTF -13
#define ERR_ERR_LIB -14
#define ERR_SORT_LIB -15
#define ERR_IO_LIB -16
#define ERR_LIB -17

void print_error(const int err_code);

int check_main_parametrs(int argc, char **argv);

int check_open_file(FILE *file, const int mode);

void close_and_free(FILE *input_file, FILE *output_file,
                    array_t *array, array_t *filtered_array,
                    const int argc, int *const exit_code);

#endif
