//Среднее геометрическое положительных элементов массива.

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define OK 0
#define WRONG_LEN 1
#define WRONG_NUM 2
#define NO_POSITIVE 3
#define OVERFLOW 4
#define MAX_LEN 10

void print_error(int error)
{
    if (error == WRONG_NUM)
    {
        printf("Wrong number of valid array elements.\n");
    }
    else if (error == WRONG_LEN)
    {
        printf("Invalid number of array elements.\n");
    }
    else if (error == NO_POSITIVE)
    {
        printf("There is no positive elements.\n");
    }
    else if (error == OVERFLOW)
    {
        printf("Overflow during multiplication.\n");
    }
}

bool overflow_product(long long first_num, int second_num)
{
    if (second_num != 0 && llabs(first_num) > llabs(LLONG_MAX / second_num))
    {
        return true;
    }

    return false;
}

int input_array(int *const arr, int *const len)
{
    printf("Enter length of array: ");

    if (scanf("%d", len) == 1 && *len > 0 && *len <= MAX_LEN)
    {
        printf("Enter elements of array: ");

        for (int i = 0; i < *len; i++)
        {
            if (scanf("%d", &arr[i]) != 1)
            {
                return WRONG_NUM;
            }
        }
    }
    else
    {
        return WRONG_LEN;
    }

    return OK;
}

int find_geometric_mean(const int *arr, const int len, double *geom_mean)
{
    int num_positive = 0;
    long long product = 1;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] > 0)
        {
            if (overflow_product(product, arr[i]))
            {
                return OVERFLOW;
            }
            else
            {
                product *= arr[i];
                num_positive++;
            }
        }
    }

    if (num_positive > 0)
    {
        *geom_mean = pow(product, 1.0 / num_positive);
        return OK;
    }
    else
    {
        return NO_POSITIVE;
    }
}

int main(void)
{
    setbuf(stdout, NULL);

    int array[MAX_LEN];
    int length;
    int exit_code;
    double geometric_mean;

    exit_code = input_array(array, &length);

    if (exit_code == OK)
    {
        exit_code = find_geometric_mean(array, length, &geometric_mean);
    }

    if (exit_code == OK)
    {
        printf("The geometric mean is %lf \n", geometric_mean);
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

