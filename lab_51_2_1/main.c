#include <stdio.h>

#include "get_num_max.h"

int main(void)
{
    int num_max;
    int exit_code;

    exit_code = get_num_max(stdin, &num_max);

    if (!exit_code)
    {
        printf("%d\n", num_max);
    }

    return exit_code;
}

