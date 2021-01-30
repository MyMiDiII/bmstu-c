#include <stdio.h>

#define OK 0
#define NONINTEGER_SIZE 1
#define SIZE_OUT 2
#define NONINTEGER_ELEMENT 3

#define MAX_ROW 10
#define MAX_COL 10
#define MONOTONE 1
#define NOT_MONOTONE 0

int input_matrix(int (*mat)[MAX_COL], int *const row, int *const col)
{
    printf("Input number of rows and columns: ");

    if (scanf("%d%d", row, col) != 2)
    {
        return NONINTEGER_SIZE;
    }

    if (*row <= 0 || *col <= 0 || *row > MAX_ROW || *col > MAX_COL)
    {
        return SIZE_OUT;
    }

    printf("Input elements of matrix:\n");

    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *col; j++)
        {
            if (scanf("%d", &mat[i][j]) != 1)
            {
                return NONINTEGER_ELEMENT;
            }
        }
    }

    return OK;
}

void print_error(const int error)
{
    if (error == NONINTEGER_SIZE)
    {
        printf("Noninteger parameters of matrix.\n");
    }
    else if (error == SIZE_OUT)
    {
        printf("Size of matrix out of range.\n");
    }
    else if (error == NONINTEGER_ELEMENT)
    {
        printf("Noninteger elements of matrix.\n");
    }
}

void print_array(const int *const arr, const int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
}

void create_array(const int (*mat)[MAX_COL], int *const arr,
const int row, const int col)
{
    if (col == 1)
    {
        for (int i = 0; i < row; i++)
        {
            arr[i] = NOT_MONOTONE;
        }
    }
    else
    {
        for (int i = 0; i < row; i++)
        {
            long long delta = (long long int) mat[i][1] - mat[i][0];

            int j;
            for (j = 2; j < col; j++)
            {
                long long cur_delta = (long long int) mat[i][j] - mat[i][j - 1];

                if (delta == 0 && cur_delta != 0)
                {
                    delta = cur_delta;
                }
                else if ((delta > 0 && cur_delta < 0) || (delta < 0 && cur_delta > 0))
                {
                    arr[i] = NOT_MONOTONE;
                    break;
                }
            }

            if (j == col)
            {
                arr[i] = MONOTONE;
            }
        }
    }
}

int main(void)
{
    setbuf(stdout, NULL);

    int matrix[MAX_ROW][MAX_COL];
    int array[MAX_ROW];
    int row, col;

    int exit_code = input_matrix(matrix, &row, &col);

    if (exit_code == OK)
    {
        create_array((const int (*)[MAX_COL]) matrix, array, row, col);

        printf("The created array: ");
        print_array(array, row);
        printf("\n");
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

