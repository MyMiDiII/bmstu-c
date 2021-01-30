#include <stdio.h>

#include "errors.h"

void print_error(const int error)
{
    if (WRONG_PARAMETRS == error)
    {
        fprintf(stderr, "Invalid main parametrs.\n");
    }
    else if (NO_FILE == error)
    {
        fprintf(stderr, "There is no file.\n");
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
    else if (READ_ERROR == error)
    {
        fprintf(stderr, "Invalid entered data.\n");
    }
}