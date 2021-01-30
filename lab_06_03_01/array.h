#ifndef __ARRAY_H__

#define __ARRAY_H__

#include "products.h"

#define OK 0
#define ERR_INDEX -1
#define ERR_APPEND -2

int get(const array_t *const arr, const int index, product_t **element);

int set(array_t *const arr, const int index, const product_t *const element);

int append(array_t *const arr, const product_t *const element);

#endif
