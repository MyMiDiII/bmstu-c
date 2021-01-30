#include <stdio.h>

#include "errors.h"

void print_error(const int error)
{
    if (INVALID_NUM_MAIN_PARAMETRS == error)
    {
        fprintf(stderr, "Invalid number of main parametrs.\n");
    }
    else if (THIRD_NOT_NATURAL == error)
    {
        fprintf(stderr, "The third parametr in mode 'c' should be natural number.\n");
    }
    else if (NO_FILE == error)
    {
        fprintf(stderr, "There is no file.\n");
    }
    else if (WRONG_MODE == error)
    {
        fprintf(stderr, "Wrong mode.\n");
    }
    else if (EMPTY_FILE == error)
    {
        fprintf(stderr, "Empty file.\n");
    }
    else if (OPEN_ERROR == error)
    {
        fprintf(stderr, "Couldn't open file.\n");
    }
    else if (WRONG_SIZE == error)
    {
        fprintf(stderr, "Incorrect size of file.\n");
    }
}