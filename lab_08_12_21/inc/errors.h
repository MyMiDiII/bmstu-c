#ifndef __ERRORS_H__

#define __ERRORS_H__

#include <stdio.h>

#define OK 0
#define ERR_INVALID_MAIN_PARAMETERS -1
#define ERR_INVALID_NUM_MAIN_PARAMETERS -2
#define ERR_INVALID_ACTION -3
#define ERR_WRONG_MODE -4
#define ERR_OPEN_MATRIX1_FILE -5
#define ERR_OPEN_MATRIX2_FILE -6
#define ERR_OPEN_RESULTS_FILE -7
#define ERR_READ_SIZES -8
#define ERR_READ_FILE -9
#define ERR_WRONG_ELEMENT_PARAMETERS -10
#define ERR_NONSQUARE -11
#define ERR_NULL_POINTER -12
#define ERR_WRONG_MATRIX_SIZES -13
#define ERR_ZERO_DEMENSIONS -14
#define ERR_MEMORY_ALLOCATION -15
#define ERR_FPRINTF -16
#define ERR_FCLOSE -17

void print_error(const int err_code);

int check_main_parameters(int argc, char **argv, int *const mode);

#endif