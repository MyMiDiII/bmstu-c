#ifndef __PRODUCTS_H__

#define __PRODUCTS_H__

#include <stdio.h>
#include "array.h"

#define MAX_LEN 15
#define MAX_STR_LEN 25

#define ERR_NUMBER -1
#define ERR_NAME_READ -2
#define ERR_PRICE_READ -3
#define ERR_PRICE -4
#define ERR_GET -5
#define ERR_NO_LESS -6

typedef struct
{
    char name[MAX_STR_LEN + 2];
    int price;
} product_t;

typedef struct
{
    product_t *arr;
    int len;
    int capacity;
} array_t;

int read_products(FILE *file, array_t *const products);

int print_less_max_price(const array_t *const products, const double max_price);

#endif
