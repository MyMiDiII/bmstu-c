#include <stdio.h>

#include "print_words.h"

bool is_matching(const char *str1, const char *str2)
{
    int i;
    for (i = 0; *(str1 + i) != '\0' && *(str2 + i) != '\0'; i++)
    {
        if (*(str1 + i) != *(str2 + i))
        {
            return false;
        }
    }

    if (!(*(str1 + i) == '\0' && *(str2 + i) == '\0'))
    {
        return false;
    }

    return true;
}

int print_words(char (*words1)[WORD_MAX_LEN + 1], const int len1,
char (*words2)[WORD_MAX_LEN + 1], const int len2, int *const was_print)
{
    int number = 0;
    for (int i = 0; i < len1; i++)
    {
        int num_of_repetitions = 0;
        for (int j = 0; j < len1; j++)
        {
            if (i != j && is_matching(words1[i], words1[j]))
            {
                num_of_repetitions++;
            }
        }

        for (int j = 0; j < len2; j++)
        {
            if (is_matching(words1[i], words2[j]))
            {
                num_of_repetitions++;
            }
        }

        if (num_of_repetitions == 0)
        {
            if (*was_print == 0)
            {
                puts("Result:");
            }
            printf("%s ", words1[i]);
            *was_print = 1;
            number++;
        }
    }

    return number;
}

