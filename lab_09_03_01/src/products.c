#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "products.h"
#include "macrologger.h"
#include "err_defines.h"

int read_products(FILE *file, array_t *const products)
{
    LOG_INFO("%s", "read_products");

    if (!products)
        ERROR("ERR_POINTER", ERR_POINTER);

    LOG_INFO("%s", "read_products");
    int number;

    if (fscanf(file, "%d\n", &number) != 1)
        ERROR("ERR_NUMBER", ERR_NUMBER);

    LOG_DEBUG("number = %d", number);
    if (number <= 0)
        ERROR("ERR_NUMBER", ERR_NUMBER);

    products->arr = malloc(sizeof(product_t) * number);

    if (!products->arr)
        ERROR("ERR_MEMORY", ERR_MEMORY);

    products->len = 0;
    products->capacity = number;

    for (int i = 0; i < number; i++)
    {
        LOG_DEBUG("i = %d", i);
        product_t current;
        char *p = NULL;

        if (read_name(&p, file))
            FREEP_ERROR("ERR_NAME_READ", ERR_NAME_READ);

        current.name = p;

        if (fscanf(file, "%d\n", &current.price) != 1)
            FREEPN_ERROR("ERR_PRICE_READ", ERR_PRICE_READ);

        LOG_DEBUG("price = %d", current.price);
        if (current.price < 0)
            FREEPN_ERROR("ERR_PRICE", ERR_PRICE);

        if (append(products, &current))
            FREEP_ERROR("ERR_APPEND", ERR_APPEND);
    }

    LOG_INFO("%s", "read_products OK");
    return OK;
}

int print_less_max_price(const array_t *const products, const double max_price)
{
    LOG_INFO("%s", "print_less_max_price");

    for (int i = 0; i < products->len; i++)
    {
        product_t *current;

        if (get(products, i, &current))
            ERROR("ERR_GET", ERR_GET);

        if (current->price < max_price)
        {
            printf("%s\n", current->name);
            printf("%d\n", current->price);
        }
    }

    LOG_INFO("%s", "print_less_max_price OK");
    return OK;
}

int read_name(char **name, FILE *file)
{
    LOG_INFO("%s", "read_name");

    if (!name || !file)
        ERROR("ERR_POINTER", ERR_POINTER);

    *name = malloc(sizeof(char));

    if (!name)
        ERROR("ERR_MEMORY", ERR_MEMORY);

    int len = 0;
    int capacity = 1;

    char cur_ch;
    while ((cur_ch = getc(file)) != '\n' && cur_ch != EOF)
    {
        LOG_DEBUG("len = %d", len);
        LOG_DEBUG("capacity = %d", capacity);
        LOG_DEBUG("cur_ch = %c", cur_ch);

        if (len >= capacity - 1)
        {
            char *tmp = realloc(*name, capacity * 2 * sizeof(char));

            if (!tmp)
            {
                free(*name);
                ERROR("ERR_MEMORY", ERR_MEMORY);
            }

            *name = tmp;
            capacity *= 2;
        }

        (*name)[len++] = cur_ch;
    }

    (*name)[len] = '\0';

    LOG_INFO("%s", "read_name OK");
    return OK;
}
