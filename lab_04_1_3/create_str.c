#include <stdio.h>
#include <string.h>

#include "create_str.h"

void unique_copy(char *const where, const char *what, int *const len)
{
    for (int i = 0; what[i] != '\0'; i++)
    {
        int j;
        for (j = 0; j != i && what[i] != what[j]; j++);

        if (i == j)
        {
            where[(*len)++] = what[i];
        }
    }
    where[(*len)++] = ' ';
}

int create_str(char (*words)[WORD_MAX_LEN + 1], const int len, char *const new_str)
{
    int len_new_srt = 0;

    for (int i = len - 2; i >= 0 ; i--)
    {
        if (strcmp(words[i], words[len - 1]))
        {
            unique_copy(new_str, words[i], &len_new_srt);
        }
    }

    if (len_new_srt != 0)
    {
        new_str[--len_new_srt] = '\0';
    }
    else
    {
        new_str[len_new_srt] = '\0';
    }

    return len_new_srt;
}

