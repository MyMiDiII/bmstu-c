#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"
#include "errors.h"
#include "macrologger.h"

int count_num(FILE *file, size_t *const num)
{
    LOG_INFO("%s", "count_num was started");

    if (!file || !num)
    {
        LOG_ERROR("%s", "ERR_NULL_POINTER");
        return ERR_NULL_POINTER;
    }

    *num = 0;
    int current;

    while (fscanf(file, "%d",&current) == 1)
    {
        LOG_DEBUG("current is %d", current);
        (*num)++;
        LOG_DEBUG("current num is %lu", *num);
    }

    if (!feof(file))
    {
        LOG_ERROR("%s", "ERR_READ_FILE");
        return ERR_READ_FILE;
    }

    if (*num == 0)
    {
        LOG_ERROR("%s", "ERR_EMPTY_FILE");
        return ERR_EMPTY_FILE;
    }

    if (fseek(file, 0L, SEEK_SET))
    {
        LOG_ERROR("%s", "ERR_FSEEK");
        return ERR_FSEEK;
    }

    LOG_INFO("%s", "count_num was done successfully!");
    return OK;
}

int create_array(FILE *file, const size_t num, array_t *const array)
{
    LOG_INFO("%s", "create_array was started!");

    if (!file || !num || !array)
    {
        LOG_ERROR("%s", "ERR_NULL_POINTER");
        return ERR_NULL_POINTER;
    }

    array->arr = malloc(num * sizeof(int));

    if (!array->arr)
    {
        LOG_ERROR("%s", "ERR_CREATE_ARRAY");
        return ERR_CREATE_ARRAY;
    }

    LOG_INFO("%s", "malloc was done successfully!");

    array->end = array->arr + num;

    int current;
    size_t i;

    for (i = 0; i < num && !feof(file); i++)
    {
        LOG_INFO("i = %lu", i);

        if (fscanf(file, "%d",&current) == 1)
        {
            *(array->arr + i) = current;
            LOG_DEBUG("current = %d, element = %d", current, *(array->arr + i));
        }
        
        else
        {
            free(array->arr);
            LOG_INFO("%s", "FREE!!!");
            LOG_ERROR("%s", "ERR_READ_FILE");
            return ERR_READ_FILE;
        }
    }

    if (i != num || !feof(file))
    {
        free(array->arr);
        LOG_INFO("%s", "FREE!!!");
        LOG_ERROR("%s", "ERR_READ_FILE");
        return ERR_READ_FILE;
    }

    LOG_INFO("%s", "create_array was done successfully!");

    return OK;
}

int write_to_file(FILE *file, const array_t *const array)
{
    LOG_INFO("%s", "write_to_file was started!");

    for (int *element = array->arr; element < array->end; element++)
    {
        LOG_DEBUG("element = %d", *element);

        if (EOF == fprintf(file, "%d%s", *element,
                           (element == array->end - 1) ? "" : " "))
        {
            LOG_ERROR("%s", "ERR_FPRINTF");
            return ERR_FPRINTF;
        }
    }

    LOG_INFO("%s", "write_to_file was done successfully");
    return OK;
}