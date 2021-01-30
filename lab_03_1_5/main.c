#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define NONINTEGER_SIZE 1
#define SIZE_OUT 2
#define NONINTEGER_ELEMENT 3
#define ALL_LESS_TEN 4
#define INSERT_ERROR 5

#define MAX_ROW 10
#define MAX_COL 10
#define MAX_LEN MAX_ROW * MAX_COL
#define BASE 10
#define SHIFT 3

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

void print_matrix(const int (*mat)[MAX_COL], const int row, const int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
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
    else if (error == ALL_LESS_TEN)
    {
        printf("All sums of digits less than ten.\n");
    }
}

int digit_sum(int number)
{
    int sum = 0;

    number = abs(number);

    while (number)
    {
        sum += number % BASE;
        number /= BASE;
    }

    return sum;
}

int create_arrays(const int (*mat)[MAX_COL], const int row, const int col,
int *const num, int *const ind, int *const len)
{
    *len = 0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (digit_sum(mat[i][j]) > 10)
            {
                num[*len] = mat[i][j];
                ind[*len] = i * col + j;
                (*len)++;
            }
        }
    }

    if (*len == 0)
    {
        return ALL_LESS_TEN;
    }

    return OK;
}

void shift_array(int *const arr, const int len)
{
    for (int i = 0; i < SHIFT; i++)
    {
        int t = arr[0];

        for (int j = 0; j < len - 1; j++)
        {
            arr[j] = arr[j + 1];
        }

        arr[len - 1] = t;
    }
}

int insert_into_matrix(int (*mat)[MAX_COL], const int row, const int col,
const int *const num, const int *const ind, const int len)
{
    if (len > row * col)
    {
        return INSERT_ERROR;
    }

    for (int k = 0; k < len; k++)
    {
        if (ind[k] < 0)
        {
            return INSERT_ERROR;
        }

        int i = ind[k] / col;
        int j = ind[k] % col;

        if (j >= col || i >= row)
        {
            return INSERT_ERROR;
        }

        mat[i][j] = num[k];
    }

    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);

    int matrix[MAX_ROW][MAX_COL];
    int row, col;
    int numbers[MAX_LEN];
    int indexes[MAX_LEN];
    int len;

    int exit_code = input_matrix(matrix, &row, &col);

    if (exit_code == OK)
    {
        exit_code = create_arrays((const int (*)[MAX_COL]) matrix, row, col,
        numbers, indexes, &len);
    }

    if (exit_code == OK)
    {
        shift_array(numbers, len);
        insert_into_matrix(matrix, row, col, numbers, indexes, len);

        printf("Chanched matrix:\n");
        print_matrix((const int (*)[MAX_COL]) matrix, row, col);
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

