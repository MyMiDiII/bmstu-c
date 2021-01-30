#include <stdio.h>
#include <stdbool.h>

#include "array.h"

void create_fib_array(int *const arr, const int len)
{
    if (!arr || len < 1 || len > 47)
        return;

    arr[0] = 0;

    if (len > 1)
        arr[1] = 1;

    for (int i = 2; i < len; i++)
        arr[i] = arr[i - 2] + arr[i - 1];
}

int delete_repeated(const int *const arr, const int arr_len,
                    int *const new_arr, const int new_arr_len)
{
    if (!arr || arr_len <= 0 || !new_arr || new_arr_len < 0)
        return 0;

    int cur_index = 0;
    for (int i = 0; i < arr_len; i++)
    {
        bool not_in = true;
        for (int j = 0; j < i; j++)
            if (arr[i] == arr[j])
                not_in = false;

        if (not_in)
        {
            if (new_arr_len && cur_index < new_arr_len)
                new_arr[cur_index] = arr[i];
            cur_index++;
        }
    }

    return cur_index;
}
