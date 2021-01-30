//Вставка положительных элементов, записанных наоборот.

#include <stdio.h>

#define OK 0
#define WRONG_LEN 1
#define WRONG_NUM 2
#define SHIFT_ERROR 3
#define REVERSE_ERROR -1
#define BASE 10
#define INPUT_MAX_LEN 10
#define MAX_LEN 20

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
}

int input_array(int *const arr, int *const len)
{
    printf("Enter length of array: ");

    if (scanf("%d", len) == 1 && *len > 0 && *len <= INPUT_MAX_LEN)
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

int shift(int *const arr, int *const len, const int border)
{
    if (border >= 0 && *len + 1 <= MAX_LEN)
    {
        for (int i = *len - 1; i > border; i--)
        {
            arr[i + 1] = arr[i];
        }

        (*len)++;

        return OK;
    }
    
    return SHIFT_ERROR;
}

int reverse_elem(int number)
{
    if (number < 0)
    {
        return REVERSE_ERROR;
    }

    int reversed = 0;

    while (number)
    {
        reversed = reversed * BASE + number % BASE;
        number /= BASE;
    }

    return reversed;
}

void insert_reverse(int *const arr, int *const len)
{
    int i = 0;
    while (i < *len && *len < MAX_LEN)
    {
        if (arr[i] > 0)
        {
            shift(arr, len, i);
            arr[i + 1] = reverse_elem(arr[i]);

            i += 2;
        }
        else
        {
            i++;
        }
    }
}

int main(void)
{
    setbuf(stdout, NULL);

    int array[MAX_LEN];
    int length;
    int exit_code;

    exit_code = input_array(array, &length);

    if (exit_code == OK)
    {
        insert_reverse(array, &length);
        printf("New array: ");
        print_array(array, length);
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

