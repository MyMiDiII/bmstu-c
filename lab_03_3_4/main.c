#include <stdio.h>

#define OK 0
#define NONINTEGER_SIZE 1
#define SIZE_OUT 2
#define NONINTEGER_ELEMENT 3
#define NONSQUARE_MATRIX 4

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
    else if (error == NONSQUARE_MATRIX)
    {
        printf("Nonsquare matrix.\n");
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

void swap(int *const f, int *const s)
{
    int t = *f;
    *f = *s;
    *s = t;
}

void swap_pyramids(int (*mat)[MAX_COL], const int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <= size / 2; j++)
        {
            if (i >= j && i + j <= size - 1)
            {
                swap(&mat[i][j], &mat[i][size - 1 - j]);
            }
        }
    }
}

int main(void)
{
    setbuf(stdout, NULL);

    int matrix[MAX_ROW][MAX_COL];
    int row, col;

    int exit_code = input_matrix(matrix, &row, &col);

    if (exit_code == OK)
    {
        if (row == col)
        {
            swap_pyramids(matrix, row);

            print_matrix((const int (*)[MAX_COL]) matrix, row, col);
        }
        else
        {
            exit_code = NONSQUARE_MATRIX;
        }
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}

