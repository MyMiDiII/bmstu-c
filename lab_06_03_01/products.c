#include <stdio.h>
#include <string.h>
#include "array.h"
#include "products.h"

int read_products(FILE *file, array_t *const products)
{
    int number;

    if (fscanf(file, "%d\n", &number) != 1)
        return ERR_NUMBER;

    if (number <= 0 || number > MAX_LEN)
        return ERR_NUMBER;

    for (int i = 0; i < number; i++)
    {
        product_t current;
        char *p = fgets(current.name, MAX_STR_LEN + 2, file);

        if (!p)
            return ERR_NAME_READ;

        if (fscanf(file, "%d\n", &current.price) != 1)
            return ERR_PRICE_READ;

        if (current.price < 0)
            return ERR_PRICE;

        if (append(products, &current))
            return ERR_APPEND;
    }

    return OK;
}

int print_less_max_price(const array_t *const products, const double max_price)
{
    for (int i = 0; i < products->len; i++)
    {
        product_t *current;

        if (get(products, i, &current))
            return ERR_GET;

        if (current->price < max_price)
        {
            printf("%s", current->name);
            printf("%d\n", current->price);
        }
    }

    return OK;
}
