#ifndef __SORT_BIN_H__

#define __SORT_BIN_H__

#include "product.h"

void copy_bin_file(FILE *in, FILE *out, const int size);

void sort_bin_file(FILE *file, const int size);

product_t get_struct_by_pos(FILE *file, const int pos);

void put_struct_by_pos(FILE *file, const int pos, product_t product);

#endif