#include <stdio.h>

#include "average.h"

#define OK 0

int find_min_max_average(FILE *file, double *const average)
{
    double min, max;
    double current;
    *average = 0;

    if (fscanf(file, "%lf", &current) != 1)
    {
        return NO_NUMBERS;
    }

    min = current;
    max = current;

    while (fscanf(file, "%lf", &current) == 1)
    {
        if (current > max)
        {
            max = current;
        }

        if (current < min)
        {
            min = current;
        }
    }

    *average = (min + max) / 2;

    return OK;
}

void count_greater_average(FILE *file, const double average, int *const num)
{
    *num = 0;
    double current;

    while (fscanf(file, "%lf", &current) == 1)
    {
        if (current > average)
        {
            (*num)++;
        }
    }
}