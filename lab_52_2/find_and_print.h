#ifndef __FIND_AND_PRINT_H__

#define __FIND_AND_PRINT_H__

#include <stdbool.h>
#include "product.h"

int find_and_print(FILE *file, const char *str, const int size);

bool check_name(const char *name, const char *str);

void print_product(product_t product);

#endif