#include <stdlib.h>

#include "array.h"
#include "macrologger.h"
#include "err_defines.h"

int get(const array_t *const arr, const int index, product_t **element)
{
    LOG_INFO("%s", "get");

    if (!arr || !element)
        ERROR("ERR_POINTER", ERR_POINTER);

    LOG_DEBUG("index = %d", index);
    LOG_DEBUG("arr->len - 1 = %d", arr->len - 1);

    if (index < 0 || index > arr->len - 1)
        ERROR("ERR_INDEX", ERR_INDEX);

    *element = arr->arr + index;

    LOG_INFO("%s", "get OK");
    return OK;
}

int set(array_t *const arr, const int index, const product_t *const element)
{
    LOG_INFO("%s", "set");

    if (!arr || !element)
        ERROR("ERR_POINTER", ERR_POINTER);

    LOG_DEBUG("index = %d", index);
    LOG_DEBUG("arr->len - 1 = %d", arr->len - 1);

    if (index < 0 || index > arr->len - 1)
        ERROR("ERR_INDEX", ERR_INDEX);

    arr->arr[index] = *element;

    LOG_INFO("%s", "set OK");
    return OK;
}

int append(array_t *const arr, const product_t *const element)
{
    LOG_INFO("%s", "append");

    if (!arr || !element)
        ERROR("ERR_POINTER", ERR_POINTER);

    LOG_DEBUG("arr = %p", (void *) arr->arr);
    LOG_DEBUG("capacity = %d", arr->capacity);

    if ((!arr->arr && arr->capacity) || (arr->arr && !arr->capacity))
        ERROR("ERR_ARR_PARAMETERS", ERR_ARR_PARAMETERS);

    LOG_DEBUG("len = %d", arr->len);

    if (arr->len >= arr->capacity)
    {
        int new_capasity = (!arr->arr && !arr->len && !arr->capacity) ? 1 : arr->capacity * 2;
        LOG_DEBUG("new_capasity = %d", new_capasity);
        product_t *tmp = realloc(arr->arr, new_capasity * sizeof(product_t));

        if (!tmp)
            ERROR("ERR_MEMORY", ERR_MEMORY);

        arr->arr = tmp;
        arr->capacity = new_capasity;
    }

    if (set(arr, arr->len++, element))
    {
        arr->len--;
        ERROR("ERR_APPEND", ERR_APPEND);
    }

    LOG_INFO("%s", "append OK");
    return OK;
}

int free_array(array_t *const arr)
{
    LOG_INFO("%s", "free_array");

    if (!arr)
        ERROR("ERR_POINTER", ERR_POINTER);

    if (arr->arr)
        for (int i = 0; i < arr->len; i++)
        {
            LOG_DEBUG("i = %d", i);
            free(arr->arr[i].name);
        }

    free(arr->arr);

    LOG_INFO("%s", "free_array OK");
    return OK;
}
