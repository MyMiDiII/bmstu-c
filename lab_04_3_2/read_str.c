#include <stdio.h>

#include "read_str.h"

int read_str(char *const str, const int max_len)
{
    int ch, len = 0;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (len < max_len - 1)
        {
            str[len] = ch;
        }
        len++;
    }
    
    if (len < max_len)
    {
        str[len] = '\0';
    }

    return len;
}

