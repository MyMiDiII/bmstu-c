/*
    Выбранный целочисленный тип: int
    Алгоритм сортировки: выбором
    Направление упорядочивания: неубывание
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "fill.h"
#include "print_bin.h"
#include "sort_bin.h"

int main(int argc, char **argv)
{
    FILE *input_file;
    int exit_code = OK;
    char *end_ptr;

    if (argc < 2)
    {
        exit_code = INVALID_NUM_MAIN_PARAMETRS;
    }

    if (!strcmp(argv[1], "c"))
    {
        if (argc != 4)
        {
            exit_code = INVALID_NUM_MAIN_PARAMETRS;
        }

        int num = strtol(argv[2], &end_ptr, 10);

        if (*end_ptr || num <= 0)
        {
            exit_code = THIRD_NOT_NATURAL;
        }
        else
        {
            input_file = fopen(argv[3], "wb");

            if (!input_file)
            {
                exit_code = OPEN_ERROR;
            }
            else
            {
                fill_random(input_file, num);
                fclose(input_file);
            }
        }
    }
    else if (argc != 3)
    {
        exit_code = INVALID_NUM_MAIN_PARAMETRS;
    }
    else if (!strcmp(argv[1], "p"))
    {
        input_file = fopen(argv[2], "rb");

        if (!input_file)
        {
            exit_code = NO_FILE;
        }
        else
        {
            exit_code = print_bin_file(input_file);
            fclose(input_file);
        }
    }
    else if (!strcmp(argv[1], "s"))
    {
        input_file = fopen(argv[2], "r+b");

        if (!input_file)
        {
            exit_code = NO_FILE;
        }
        else
        {
            exit_code = sort_bin_file(input_file);
            fclose(input_file);
        }
    }
    else
    {
        exit_code = WRONG_MODE;
    }

    if (exit_code)
    {
        print_error(exit_code);
    }

    return exit_code;
}