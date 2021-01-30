#include <stdio.h>

#define OK 0
#define MAX_LEN 1000
#define MAX_COLUMN 10
#define BASE 10

void input_array(int *arr, int *len)
{
    int i = 0;
    while(i < MAX_LEN && scanf("%d", &arr[i]) == 1)
    {
        i++;
    }
    *len = i;
}

void create_B(const int *const a, const int len, int (*B)[MAX_COLUMN])
{
    for (int i = 0; i < len; i++)
    {
        int num = a[i];
        int j = MAX_COLUMN - 1;
        while (j >= 0)
        {
            B[i][j] = num % BASE;
            num /= BASE;
            j++;
        }
    }
}

int find_row_with_max(int (*B)[MAX_COLUMN], const int len)
{
    int row;
    for (int j = 0; j < MAX_COLUMN; j++)
    {
        int max = B[0][j];
        for (int i = 1; i < len; i++)
        {
            if (B[i][j] > max)
            {
                max = B[i][j];
                row = i;
            }
        }
        if (max != 0)
        {
            return row;
        }
    }
    return 0;
}

void print_matrix_market(int (*B)[MAX_COLUMN], const int len, const int row)
{
    printf("%% max row number = %d\n", row + 1);

    int num_not_zero = 0;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < MAX_COLUMN; j++)
        {
            if (B[i][j] != 0)
            {
                num_not_zero++;
            }
        }
    }

    printf("%d %d %d\n", row, MAX_COLUMN, num_not_zero);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (B[i][j] != 0)
            {
                printf("%d %d %d\n", i + 1, j + 1, B[i][j]);
            }
        }
    }
}

int main(void)
{
    int A[MAX_LEN];
    int len;
    int B[MAX_LEN][MAX_COLUMN];

    input_array(A, &len);
    create_B(A, len, B);
    int row = find_row_with_max(B, len);
    print_matrix_market(B, len, row);

    return OK;
}
