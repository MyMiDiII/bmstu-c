#include "get_len.h"

int get_len(char *const word, const int max_len)
{
    int len = 0;

    while (len < max_len && word[len] != '\0')
    {
        len++;
    }

    return len;
}

