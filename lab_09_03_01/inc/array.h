#ifndef __ARRAY_H__

#define __ARRAY_H__

#include "products.h"

#define OK 0
#define ERR_INDEX -1
#define ERR_APPEND -2
#define ERR_POINTER -3
#define ERR_FREE -4

int get(const array_t *const arr, const int index, product_t **element);

int set(array_t *const arr, const int index, const product_t *const element);

int append(array_t *const arr, const product_t *const element);

int free_array(array_t *const arr);

#endif
