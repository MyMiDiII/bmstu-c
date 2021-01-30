#include <stdio.h>

#include "insert.h"
#include "sort_bin.h"

void insert_product(FILE *file, product_t product, const int size)
{
    size_t place = size;

    for (size_t i = 0; i < size && place == size; i += sizeof(product_t))
    {
        product_t current = get_struct_by_pos(file, i);

        if (current.price < product.price)
        {
            place = i;
        } 
        else if (current.price == product.price && 
            current.number <= product.number)
        {
            place = i;
        }
    }

    for (size_t i = place; i < size; i += sizeof(product_t))
    {
        product_t current = get_struct_by_pos(file, i);
        
        put_struct_by_pos(file, i, product);
        product = current;
    }

    put_struct_by_pos(file, size, product);
}