#include <stdio.h>

#define OK 0
#define NONINTEGER_SIZE 1
#define SIZE_OUT 2
#define NONINTEGER_ELEMENT 3

#define MAX_ROW 10
#define MAX_COL 10

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

void create_array_of_min(const int (*mat)[MAX_COL], const int row, const int col,
int *const arr)
{
    for (int i = 0; i < row; i++)
    {
        int cur_min = mat[i][0];

        for (int j = 1; j < col; j++)
        {
            if (mat[i][j] < cur_min)
            {
                cur_min = mat[i][j];
            }
        }

        arr[i] = cur_min;
    }
}

void swap(int *const f, int *const s)
{
    int t = *f;
    *f = *s;
    *s = t;
}

void sort_matrix_by_min(int (*mat)[MAX_COL], const int row, const int col,
int *const arr)
{
    for (int i = 1; i < row; i++)
    {
        for (int k = 0; k < row - i; k++)
        {
            if (arr[k] < arr[k + 1])
            {
                swap(arr + k, arr + k + 1);

                for (int j = 0; j < col; j++)
                {
                    swap(&mat[k][j], &mat[k + 1][j]);
                }
            }
        }
    }
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

int main(void)
{
    setbuf(stdout, NULL);

    int matrix[MAX_ROW][MAX_COL];
    int row, col;
    int mins[MAX_ROW];

    int exit_code = input_matrix(matrix, &row, &col);

    if (exit_code == OK)
    {
        create_array_of_min((const int (*)[MAX_COL]) matrix, row, col, mins);
        sort_matrix_by_min(matrix, row, col, mins);
        printf("Sorted matrix:\n");
        print_matrix((const int (*)[MAX_COL]) matrix, row, col);
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

