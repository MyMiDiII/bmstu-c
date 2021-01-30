#include <stdio.h>

#define OK 0
#define MAX_LEN 1000

void input_array(unsigned int *arr, unsigned int *len)
{
    int i = 0;
    while(i < MAX_LEN && scanf("%u", &arr[i]) == 1)
    {
        i++;
    }
    *len = i;
}

unsigned long long find_sum(unsigned int *const arr, const unsigned int len)
{
    unsigned long long sum = 0;
    for (int i = 0; i < len; i++)
    {
        unsigned int num = 0;
        for(int j = 0; j < i; j++)
        {
            if (arr[j] == arr[i])
            {
                num++;
            }
        }
        if (num == 0)
        {
            sum += arr[i];
        }
    }

    return sum;
}

int main(void)
{
    unsigned int A[MAX_LEN];
    unsigned int len;

    input_array(A, &len);
    unsigned long long sum = find_sum(A, len);
    printf("%llu\n", sum);

    return OK;
}

