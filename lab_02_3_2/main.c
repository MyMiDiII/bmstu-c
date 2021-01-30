//Нахождение чисел Армстронга и их копирование в новый массив.

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define OK 0
#define WRONG_LEN 1
#define WRONG_NUM 2
#define NO_ARMSTRONG 3
#define NEGATIVE_POW -1
#define OVERFLOW_POW -2
#define BASE 10
#define MAX_LEN 10

void print_error(int error)
{
    if (error == WRONG_LEN)
    {
        printf("Invalid number of array elements.\n");
    }
    else if (error == WRONG_NUM)
    {
        printf("Wrong number of valid array elements.\n");
    }
    else if (error == NO_ARMSTRONG)
    {
        printf("There is no Armstrong elements.\n");
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

void print_array(const int *arr, const int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

long long nonnegative_pow(long long base, int exponent)
{
    long long result = 1;
        
    if (base != 1 && base > 0 && exponent > 0)
    {
        while (exponent)
        {
            if (exponent % 2 == 0)
            {
                exponent /= 2;
                if (overflow_product(base, base))
                {
                    return OVERFLOW_POW;
                }
                base *= base;
            }
            else
            {
                exponent--;
                if (overflow_product(result, base))
                {
                    return OVERFLOW_POW;
                }
                result *= base;
            }
        }
    }
    else if (base == 0)
    {
        result = 0;
    }
    else if (base != 1)
    {
        return NEGATIVE_POW;
    }

    return result;
}

bool is_armstrong(int number)
{
    if (number > 0)
    {
        int copy_number = number;
        int num_digits = 0;

        while (copy_number > 0)
        {
            num_digits++;
            copy_number /= BASE;
        }

        copy_number = number;
        long long sum_pow = 0;

        while (copy_number > 0)
        {
            sum_pow += nonnegative_pow(copy_number % BASE, num_digits);

            if (sum_pow > number)
                break;
            
            copy_number /= BASE;
        }

        if (sum_pow == number)
            return true;
    }
    
    return false;
}

int find_armstrong(const int *arr, const int len_arr, int *const arm, int *const len_arm)
{
    *len_arm = 0;

    for (int i = 0; i < len_arr; i++)
    {
        if (*len_arm < MAX_LEN && is_armstrong(arr[i]))
        {
            arm[*len_arm] = arr[i];
            (*len_arm)++;
        }
    }

    if (*len_arm == 0)
    {
        return NO_ARMSTRONG;
    }
    
    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);

    int array[MAX_LEN];
    int len_array;
    int armstrong[MAX_LEN];
    int len_armstrong;
    int exit_code;

    exit_code = input_array(array, &len_array);

    if (exit_code == OK)
    {
        exit_code = find_armstrong(array, len_array, armstrong, &len_armstrong);
    }

    if (exit_code == OK)
    {
        printf("Armstrong numbers: ");
        print_array(armstrong, len_armstrong);
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

