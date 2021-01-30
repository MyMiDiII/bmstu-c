#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "products.h"
#include "macrologger.h"
#include "err_defines.h"

#define OK 0
#define ERR_ARGS -1
#define ERR_PRICE_ARG -2
#define ERR_FILE_ARG -3
#define ERR_READ -4
#define ERR_CLOSE -5
#define ERR_PRINT -6

int main(int argc, char **argv)
{
    LOG_INFO("%s", "BEGIN");
    int exit_code = OK;
    char *end_prt;
    double max_price;
    FILE *in_file;
    array_t products = { .arr = NULL, .len = 0, .capacity = 0 };

    LOG_DEBUG("argc = %d", argc);
    if (argc != 3)
        EXIT_CODE("ERR_ARGS", ERR_ARGS);

    if (!exit_code)
    {
        max_price = strtod(argv[2], &end_prt);

        if (max_price < 0 || end_prt == argv[2])
            EXIT_CODE("ERR_PRICE_ARG", ERR_PRICE_ARG);
    }

    if (!exit_code)
    {
        in_file = fopen(argv[1], "r");

        if (!in_file)
            EXIT_CODE("ERR_FILE_ARG", ERR_FILE_ARG);
    }

    if (!exit_code && read_products(in_file, &products))
        EXIT_CODE("ERR_READ", ERR_READ);

    if (!exit_code && print_less_max_price(&products, max_price))
        EXIT_CODE("ERR_PRINT", ERR_PRINT);
 
    if ((!exit_code || exit_code < ERR_FILE_ARG) && fclose(in_file) == EOF)
        EXIT_CODE("ERR_CLOSE", ERR_CLOSE);

    if ((!exit_code || exit_code < ERR_READ) && free_array(&products))
        EXIT_CODE("ERR_FREE", ERR_FREE);

    LOG_INFO("%s", "END");
    return exit_code;
}
