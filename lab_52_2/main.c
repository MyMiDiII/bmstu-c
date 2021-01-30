#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "product.h"
#include "sort_bin.h"
#include "find_and_print.h"
#include "insert.h"

int main(int argc, char **argv)
{
    FILE *input_file;
    FILE *output_file;
    int exit_code = OK;
    product_t product;
    size_t size;

    if (4 == argc && !strcmp(argv[1], "sb"))
    {
        input_file = fopen(argv[2], "rb");
        output_file = fopen(argv[3], "w+b");

        if (!input_file || !output_file)
        {
            exit_code = OPEN_ERROR;
        }
        else
        {
            exit_code = file_size(input_file, &size);

            if (!exit_code)
            {
                copy_bin_file(input_file, output_file, size);
                sort_bin_file(output_file, size);
            }

            fclose(input_file);
            fclose(output_file);
        }
    }
    else if (4 == argc && !strcmp(argv[1], "fb"))
    {
        input_file = fopen(argv[2], "rb");

        if (!input_file)
        {
            exit_code = NO_FILE;
        }
        else
        {
            exit_code = file_size(input_file, &size);

            if (!exit_code)
            {
                exit_code = find_and_print(input_file, argv[3], size);
            }

            fclose(input_file);
        }
    }
    else if (3 == argc && !strcmp(argv[1], "ab"))
    {
        input_file = fopen(argv[2], "r+b");

        if (!input_file)
        {
            exit_code = NO_FILE;
        }
        else
        {
            exit_code = file_size(input_file, &size);
            
            if (!exit_code)
            {
                memset(&product, 0, sizeof(product));
                exit_code = read_product(&product);
            }

            if (!exit_code)
            {
                insert_product(input_file, product, size);
            }

            fclose(input_file);
        }
    }
    else
    {
        exit_code = WRONG_PARAMETRS;
    }

    if (exit_code)
    {
        print_error(exit_code);
    }

    return exit_code;
}