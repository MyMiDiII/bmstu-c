#include "array.h"

int get(const array_t *const arr, const int index, product_t **element)
{
    if (index < 0 || index > arr->len - 1)
        return ERR_INDEX;

    *element = arr->arr + index;
    return OK;
}

int set(array_t *const arr, const int index, const product_t *const element)
{
    if (index < 0 || index > arr->len - 1)
        return ERR_INDEX;

    arr->arr[index] = *element;
    return OK;
}

int append(array_t *const arr, const product_t *const element)
{
    if (arr->len >= arr->capacity)
        return ERR_APPEND;

    arr->len++;

    if (set(arr, arr->len - 1, element))
    {
        arr->len--;

        return ERR_APPEND;
    }

    return OK;
}
