#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "modes.h"
#include "macrologger.h"

void print_error(const int err_code)
{
    switch (err_code)
    {
        case ERR_INVALID_MAIN_PARAMETERS:
            fprintf(stderr, "Invalid main parameters.\n");
            break;
        case ERR_INVALID_NUM_MAIN_PARAMETERS:
            fprintf(stderr, "Invalid number of main parameters.\n");
            break;
        case ERR_INVALID_ACTION:
            fprintf(stderr, "Invalid action.\n");
            break;
        case ERR_WRONG_MODE:
            fprintf(stderr, "Wrong mode in function.\n");
            break;
        case ERR_OPEN_MATRIX1_FILE:
            fprintf(stderr, "Error opening the matrix1 file.\n");
            break;
        case ERR_OPEN_MATRIX2_FILE:
            fprintf(stderr, "Error opening the matrix2 file.\n");
            break;
        case ERR_OPEN_RESULTS_FILE:
            fprintf(stderr, "Error opening the results file.\n");
            break;
        case ERR_READ_SIZES:
            fprintf(stderr, "Error reading sizes.\n");
            break;
        case ERR_READ_FILE:
            fprintf(stderr, "Error reading file.\n");
            break;
        case ERR_WRONG_ELEMENT_PARAMETERS:
            fprintf(stderr, "Wrong parameters of element.\n");
            break;
        case ERR_NONSQUARE:
            fprintf(stderr, "Non-square matrix.\n");
            break;
        case ERR_NULL_POINTER:
            fprintf(stderr, "Null pointer in function.\n");
            break;
        case ERR_WRONG_MATRIX_SIZES:
            fprintf(stderr, "Invalid matrix sizes.\n");
            break;
        case ERR_ZERO_DEMENSIONS:
            fprintf(stderr, "One of the dementions of matrix is zero.\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            fprintf(stderr, "Memory allocation error.\n");
            break;
        case ERR_FPRINTF:
            fprintf(stderr, "Error executing fprintf.\n");
            break;
        case ERR_FCLOSE:
            fprintf(stderr, "Error executing fclose.\n");
            break;
        default:
            break;
    }
}

int check_main_parameters(int argc, char **argv, int *const mode)
{
    LOG_INFO("%s", "check_main_parameters was started");

    if (argv == NULL)
    {
        LOG_ERROR("%s", "ERR_INVALID_MAIN_PARAMETERS");
        return ERR_INVALID_MAIN_PARAMETERS;
    }

    if (argc != 4 && argc != 5)
    {
        LOG_ERROR("%s", "ERR_INVALID_NUM_MAIN_PARAMETERS");
        return ERR_INVALID_NUM_MAIN_PARAMETERS;
    }

    int cmp_a = strcmp(argv[1], "a");
    int cmp_m = strcmp(argv[1], "m");
    int cmp_o = strcmp(argv[1], "o");

    LOG_DEBUG("cmp_a = %d", cmp_a);
    LOG_DEBUG("cmp_m = %d", cmp_m);
    LOG_DEBUG("cmp_o = %d", cmp_o);

    if (cmp_a && cmp_m && cmp_o)
    {
        LOG_ERROR("%s", "ERR_INVALID_ACTION");
        return ERR_INVALID_ACTION;
    }

    if (!cmp_o && argc != 4)
    {
        LOG_ERROR("%s", "ERR_INVALID_NUM_MAIN_PARAMETERS");
        return ERR_INVALID_NUM_MAIN_PARAMETERS;
    }

    if ((!cmp_a || !cmp_m) && argc != 5)
    {
        LOG_ERROR("%s", "ERR_INVALID_NUM_MAIN_PARAMETERS");
        return ERR_INVALID_NUM_MAIN_PARAMETERS;
    }

    if (!cmp_a)
    {
        LOG_INFO("%s", "program mode is a");
        *mode = A_MODE;
    }
    else if (!cmp_m)
    {
        LOG_INFO("%s", "program mode is m");
        *mode = M_MODE;
    }
    else
    {
        LOG_INFO("%s", "program mode is o");
        *mode = O_MODE;
    }

    LOG_INFO("%s", "check_main_parameters was done successfully!");

    return OK;
}
