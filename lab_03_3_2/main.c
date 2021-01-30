#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OK 0
#define NONINTEGER_SIZE 1
#define SIZE_OUT 2
#define NONINTEGER_ELEMENT 3
#define DIGIT_ERROR 4
#define EMPTY_MATRIX 5

#define MAX_ROW 10
#define MAX_COL 10
#define BASE 10

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

int input_digit(int *const digit)
{
    if (scanf("%d", digit) != 1)
    {
        return DIGIT_ERROR;
    }

    if (*digit > 9 || *digit < 0)
    {
        return DIGIT_ERROR;
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
    else if (error == DIGIT_ERROR)
    {
        printf("Digit input error.\n");
    }
    else if (error == EMPTY_MATRIX)
    {
        printf("Empty matrix.\n");
    }
}

bool is_digit_in_number(int number, const int digit)
{
    if (number == 0 && digit == 0)
    {
        return true;
    }

    number = abs(number);

    while (number)
    {
        if (number % BASE == digit)
        {
            return true;
        }
        number /= BASE;
    }

    return false;
}

int delete_columns(int (*mat)[MAX_COL], const int row, int *const col,
const int digit)
{
    int j = 0;

    while (*col != 0 && j < *col)
    {
        bool digit_presence = false;

        for (int i = 0; i < row; i++)
        {
            if (is_digit_in_number(mat[i][j], digit))
            {
                digit_presence = true;
                break;
            }
        }

        if (digit_presence)
        {
            for (int i = 0; i < row; i++)
            {
                for (int k = j; k < *col - 1; k++)
                {
                    mat[i][k] = mat[i][k + 1];
                }
            }

            (*col)--;
        }
        else
        {
            j++;
        }
    }
    
    if (*col == 0)
    {
        return EMPTY_MATRIX;
    }

    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);

    int matrix[MAX_ROW][MAX_COL];
    int row, col;

    int exit_code = input_matrix(matrix, &row, &col);

    int digit;

    if (exit_code == OK)
    {
        printf("Input digit: ");
        exit_code = input_digit(&digit);
    }

    if (exit_code == OK)
    {
        exit_code = delete_columns(matrix, row, &col, digit);
    }

    if (exit_code == OK)
    {
        printf("Matrix without columns containing digit:\n");
        print_matrix((const int (*)[MAX_COL]) matrix, row, col);
    }

    if (exit_code)
    {
        print_error(exit_code);
    }
    return exit_code;
}
