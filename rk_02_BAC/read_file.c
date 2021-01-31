#include <stdio.h>

#include "read_file.h"
#include "get_len.h"

#define MAX_WORD_LEN 10

void read_file(FILE *f, char *const string, const int max_len)
{
    int len = 0;
    char word[MAX_WORD_LEN + 1];
    int word_len = 0;

    while (fgets(word, sizeof(word), f))
    {
        word_len = get_len(word, MAX_WORD_LEN + 2);
        word_len -= 2;

        for (int i = word_len; len < max_len - 1 && i >= 0; i--)
        {
            string[len] = word[i];
            len++;
        }

        string[len] = ' ';
        len++;
        word_len = 0;
    }

    string[len - 1] = '\0';
}

