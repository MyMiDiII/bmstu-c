#include <stdio.h>
#include <string.h>

#include "read_str_h.h"

int read_str_h(char *const str, const int max_len)
{
    char *p = fgets(str, max_len, stdin);
    int len = 0;

    if (p != NULL)
    {
        len = strlen(str);

        if (str[len - 1] == '\n')
        {
            str[len - 1] = '\0';
            len--;
        }
    }

    return len;
}

