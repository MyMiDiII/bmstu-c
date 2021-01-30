#include <stdio.h>

#include "errors.h"
#include "product.h"
#include "read_str.h"

int file_size(FILE *file, size_t *size)
{
    fseek(file, 0L, SEEK_END);
    *size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    if (*size <= 0)
    {
        return EMPTY_FILE;
    }
    else if (*size % sizeof(product_t) != 0)
    {
        return WRONG_SIZE;
    }

    return OK;
}

int read_product(product_t *product)
{
    printf("Enter name of product: ");
    int name_len = read_str(product->name, sizeof(product->name));

    if (name_len > sizeof(product->name) - 1 || name_len <= 0)
    {
        return READ_ERROR;
    }

    printf("Enter maker of product: ");
    int make_len = read_str(product->maker, sizeof(product->maker));

    if (make_len > sizeof(product->maker) - 1 || make_len <= 0)
    {
        return READ_ERROR;
    }

    printf("Enter price of one product: ");

    if (scanf("%u", &product->price) != 1)
    {
        return READ_ERROR;
    }

    printf("Enter number of products: ");

    if (scanf("%u", &product->number) != 1)
    {
        return READ_ERROR;
    }

    return OK;
}