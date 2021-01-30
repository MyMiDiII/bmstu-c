#include <stdlib.h>

#include "mysort.h"
#include "errors.h"
#include "macrologger.h"

#define GREATER 1
#define LESS -1
#define EQUAL 0

void swap(void *first, void *second, size_t size)
{
    char *f = first;
    char *s = second;
    do
    {
        char tmp = *f;
        *f++ = *s;
        *s++ = tmp;
    } while (--size);
}

int compare_int(const void *const first, const void *const second)
{
    int num_1 = *(int *) first;
    int num_2 = *(int *) second;
    
    if (num_1 > num_2)
        return GREATER;
    else if (num_1 < num_2)
        return LESS;

    return EQUAL;
}

void mysort(void *first, size_t number, size_t size,
            int (*comparator)(const void *, const void *))
{
    LOG_INFO("%s", "mysort was started!");

    if (!first || number <= 0 || size <= 0 || !comparator)
        return;

    char *begin = (char *) first;
    size_t last_swap = number - 1;

    while (last_swap)
    {
        LOG_DEBUG("last_swap = %lu", last_swap);

        size_t current_last_swap = 0;

        for (size_t j = 0; j < last_swap; j++)
        {
            int comparison_result = (*comparator)((void *) (begin + j * size),
                                               (void *) (begin + (j + 1) * size));

            LOG_INFO("comparison result is %d", comparison_result);

            if (comparison_result > 0)
            {
                swap((void *) (begin + j * size),
                     (void *) (begin + (j + 1) * size), size);
                current_last_swap = j;

                LOG_INFO("swap(%lu, %lu)", j, j + 1);
                LOG_INFO("current_last_swap = %lu", current_last_swap);
            }
        }

        last_swap = current_last_swap;
    }

    LOG_INFO("%s", "mysort was done successfully!");
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    LOG_INFO("%s", "key was started!");
    if (!pb_src || !pe_src || !pb_dst || !pe_dst)
    {
        LOG_ERROR("%s", "ERR_NULL_POINTER");
        return ERR_NULL_POINTER;
    }

    if (pb_src >= pe_src)
    {
        LOG_ERROR("%s", "ERR_WRONG_POINTER");
        return ERR_WRONG_POINTERS;
    }

    size_t key_array_size = 0;

    for (const int *element = pb_src; element < pe_src && *element >= 0; element++)
    {
        key_array_size++;
        LOG_DEBUG("element = %d, key_array_size = %lu", *element, key_array_size);
    }

    if (!key_array_size)
    {
        LOG_ERROR("%s", "ERR_EMPTY_FILTER");
        return ERR_EMPTY_FILTER;
    }

    *pb_dst = malloc(key_array_size * sizeof(int));

    if (!*pb_dst)
    {
        LOG_ERROR("%s", "ERR_CREATE_ARRAY");
        return ERR_CREATE_FILTERED_ARRAY;
    }

    LOG_INFO("%s", "malloc was done successfully!");

    for (size_t i = 0; i < key_array_size; i++)
    {
        *(*pb_dst + i) = *(pb_src + i);
        LOG_DEBUG("i = %lu, element = %d", i, *(*pb_dst + i));
    }

    *pe_dst = *pb_dst + key_array_size;

    LOG_INFO("%s", "key was done successfully!");

    return OK;
}