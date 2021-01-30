#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "products.h"

#define OK 0
#define ERR_ARG -1
#define ERR_READ -2
#define ERR_CLOSE -3
#define ERR_PRINT -4

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    
    if (argc != 3)
        return ERR_ARG;

    char *end_prt;
    double max_price = strtod(argv[2], &end_prt);

    if (max_price < 0 || end_prt == argv[2])
        return ERR_ARG;

    FILE *in_file = fopen(argv[1], "r");

    if (!in_file)
        return ERR_ARG;

    product_t arr[MAX_LEN];
    array_t products = { .arr = arr, .len = 0, .capacity = MAX_LEN };

    if (read_products(in_file, &products))
        return ERR_READ;

    if (fclose(in_file) == EOF)
        return ERR_CLOSE;

    if (print_less_max_price(&products, max_price))
        return ERR_PRINT;

    return OK;
}
