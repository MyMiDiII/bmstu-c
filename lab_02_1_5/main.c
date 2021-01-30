//Обработка массива без использования индексации

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define OK 0
#define WRONG_LEN 1
#define WRONG_NUM 2
#define NOT_FOUND 3
#define OVERFLOW 4
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
    else if (error == NOT_FOUND)
    {
        printf("The value is not found.\n");
    }
    else if (error == OVERFLOW)
    {
        printf("Overflow during addition.\n");
    }
}

bool overflow_sum(long long first_num, long long second_num)
{
    if ((first_num < 0 && second_num > 0) || (first_num > 0 && second_num < 0))
    {
        return false;
    }

    if (llabs(first_num) > LLONG_MAX - llabs(second_num))
    {
        return true;
    }

    return false;
}

int input_array(int *const begin, int **end)
{
    int len;

    printf("Enter length of array: ");

    if (scanf("%d", &len) == 1 && len > 0 && len <= MAX_LEN)
    {
        *end = begin + len;

        printf("Enter elements of array: ");

        for (int *i = begin; i < *end; i++)
        {
            if (scanf("%d", i) != 1)
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

int sum_of_prod(int *const begin, int *const end, long long *res)
{
    *res = 0;
    int *cur_end = end; 

    for (int *i = begin; i < end; i++)
    {
        if (*i < 0)
        {
            int count = 0;

            for (int *j = cur_end - 1; j > begin - 1; j--)
            {
                if (*j > 0)
                {
                    if (overflow_sum(*res, (long long int) *i * *j))
                    {
                        return OVERFLOW;
                    }

                    *res += (long long int) *i * *j;
                    cur_end = j;
                    count++;
                    break;
                }
            }

            if (count == 0)
            {
                break;
            }
        }
    }

    if (*res == 0)
    {
        return NOT_FOUND;
    }

    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);
    
    int array[MAX_LEN];
    int *end = array + MAX_LEN;
    int exit_code;
    long long result;

    exit_code = input_array(array, &end);

    if (exit_code == OK)
    {
        exit_code = sum_of_prod(array, end, &result);

        if (exit_code == OK)
        {
            printf("The result is %lld \n", result);
        }
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}
