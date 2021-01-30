#include <stdio.h>

#include "sort_bin.h"
#include "errors.h"

void copy_bin_file(FILE *in, FILE *out, const int size)
{
    size_t struct_size = sizeof(product_t);

    for (size_t i = 0; i < size; i += struct_size)
    {
        product_t current = get_struct_by_pos(in, i);
        put_struct_by_pos(out, i, current);
    }
}

void sort_bin_file(FILE *file, const int size)
{
    size_t struct_size = sizeof(product_t);
    for (size_t i = 0; i < size / struct_size - 1; i++)
    {
        int max_pos = i * struct_size;
        product_t max = get_struct_by_pos(file, max_pos);
        product_t current = max;

        for (size_t j = i + 1; j < size / struct_size; j++)
        {
            int current_pos = j * struct_size;
            product_t current_product = get_struct_by_pos(file, current_pos);

            if (max.price < current_product.price)
            {
                max_pos = current_pos;
                max = current_product;
            }
            else if (max.price == current_product.price &&
                max.number < current_product.number)
            {
                max_pos = current_pos;
                max = current_product; 
            }
        }

        put_struct_by_pos(file, max_pos, current);
        put_struct_by_pos(file, i * struct_size, max);
    }
}

product_t get_struct_by_pos(FILE *file, const int pos)
{
    product_t product;

    fseek(file, pos, SEEK_SET);
    fread(&product, sizeof(product), 1, file);

    return product;
}

void put_struct_by_pos(FILE *file, const int pos, product_t product)
{
    fseek(file, pos, SEEK_SET);
    fwrite(&product, sizeof(product), 1, file);
}