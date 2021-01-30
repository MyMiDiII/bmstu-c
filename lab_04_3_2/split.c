#include "split.h"

#define TOO_LONG_WORD -1;

bool is_in_symbols(const char symbol, const char *delim)
{
    for (char const *i = delim; *i != '\0'; i++)
    {
        if (symbol == *i)
        {
            return true;
        }
    }

    return false;
}

int split(const char *str, char (*words)[WORD_MAX_LEN + 1], const char *symbols)
{
    int number = 0;
    char word[WORD_MAX_LEN];
    int next = 0;

    for (const char *i = str; *i != '\0'; i++)
    {
        bool is_symbol = is_in_symbols(*i, symbols);
        if (!is_symbol)
        {
            word[next] = *i;
            next++;
        }

        if (next > WORD_MAX_LEN)
        {
            return TOO_LONG_WORD;
        }

        if (next != 0 && ((is_symbol && i != str &&
        !is_in_symbols(*(i - 1), symbols)) || *(i + 1) == '\0'))
        {
            word[next] = '\0';
            next = 0;

            int k = 0;
            for (char *j = word; *j != '\0'; j++)
            {
                words[number][k] = *j;
                k++;
            }
            words[number][k] = '\0';
            number++;
        }
    }

    return number;
}

