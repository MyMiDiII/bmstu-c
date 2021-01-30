#include <string.h>

#include "split_str_h.h"

#define TOO_LONG_WORD -1

int split_str_h(char *str, char (*words)[WORD_MAX_LEN + 1], const char *symbols)
{
    int number = 0;
    char *word = strtok(str, symbols);

    while (word != NULL)
    {
        int word_len = strlen(word);

        if (word_len > WORD_MAX_LEN)
        {
            return TOO_LONG_WORD;
        }

        if (word_len != 0)
        {
            strcpy(words[number], word);
            number++;
        }

        word = strtok(NULL, symbols);
    }

    return number;
}

