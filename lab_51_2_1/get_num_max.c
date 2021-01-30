#include <stdio.h>

#include "get_num_max.h"

#define OK 0
#define NO_NUMBERS -1

int get_num_max(FILE *f, int *const num_max)
{
    long long int max;

    if (fscanf(f, "%lld", &max) == 1)
    {
        int count = 1;
        *num_max = count;

        long long int current_num;

        while (fscanf(f, "%lld", &current_num) == 1)
        {
            count++;
            if (current_num > max)
            {
                max = current_num;
                *num_max = count;
            }
        }

        return OK;
    }

    return NO_NUMBERS;
}

