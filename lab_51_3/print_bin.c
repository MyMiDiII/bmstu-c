#include <stdio.h>

#include "errors.h"
#include "print_bin.h"

int print_bin_file(FILE *file)
{
    size_t size;
    int current_num;
    int exit_code = OK;

    exit_code = file_size(file, &size);

    if (!exit_code)
    {
        for (size_t i = 0; i < size / sizeof(int); i++)
        {
            fread(&current_num, sizeof(int), 1, file);
            
            printf("%d ", current_num);
        }
    }

    return exit_code;
}

int file_size(FILE *file, size_t *size)
{
    fseek(file, 0L, SEEK_END);
    *size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    if (*size <= 0)
    {
        return EMPTY_FILE;
    }
    else if (*size % 4 != 0)
    {
        return WRONG_SIZE;
    }

    return OK;
}