#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "find_and_print.h"
#include "sort_bin.h"

int find_and_print(FILE *file, const char *str, const int size)
{
    size_t struct_size = sizeof(product_t);
    size_t count = 0;

    for (size_t i = 0; i < size; i += struct_size)
    {
        product_t current;
        memset(&current, 0, sizeof(current));
        current = get_struct_by_pos(file, i);

        if (check_name(current.name, str))
        {
            print_product(current);
            count++;
        }
    }

    if (!count)
    {
        return NO_PRODUCTS;
    }

    return OK;
}

bool check_name(const char *name, const char *str)
{
    int name_len = strlen(name);
    int str_len = strlen(str);
    
    if (str_len > name_len)
    {
        return false;
    }

    for (int i = 1; i <= str_len; i++)
    {
        if (name[name_len - i] != str[str_len - i])
        {
            return false;
        }
    }

    return true;
}

void print_product(product_t product)
{
    printf("%s\n", product.name);
    printf("%s\n", product.maker);
    printf("%d\n", product.price);
    printf("%d\n", product.number);
}