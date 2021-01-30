//Сортировка выбором

#include <stdio.h>

#define OK 0
#define WRONG_LEN 1
#define WRONG_NUM 2
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

void selection_sort(int *const arr, const int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int num_min = i;

        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[num_min])
            {
                num_min = j;
            }
        }

        int t = arr[i];
        arr[i] = arr[num_min];
        arr[num_min] = t;
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
        selection_sort(array, length);

        printf("Sorted array: ");
        print_array(array, length);
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

