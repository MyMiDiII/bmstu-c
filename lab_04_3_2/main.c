#include <stdio.h>

#include "read_str.h"
#include "split.h"
#include "print_words.h"

#define OK 0
#define LONG_STRING 1
#define EMPTY_STRINGS 2
#define NO_WORDS 3
#define LONG_WORD 4
#define NO_UNIQUE_WORDS 5

#define MAX_NUM_WORDS 128
#define STR_MAX_LEN 256

int main(void)
{
    char str1[STR_MAX_LEN + 1];
    char str2[STR_MAX_LEN + 1];
    char words1[MAX_NUM_WORDS][WORD_MAX_LEN + 1];
    char words2[MAX_NUM_WORDS][WORD_MAX_LEN + 1];
    const char symbols[] = " ,;:-.!?";

    int len1 = read_str(str1, STR_MAX_LEN + 1);
    int len2 = read_str(str2, STR_MAX_LEN + 1);
    
    if (0 == len1 || 0 == len2)
    {
        return EMPTY_STRINGS;
    }

    if (len1 > STR_MAX_LEN || len2 > STR_MAX_LEN)
    {
        return LONG_STRING;
    }
    
    int num1 = split(str1, words1, symbols);
    int num2 = split(str2, words2, symbols);

    if (0 == num1 && 0 == num2)
    {
        return NO_WORDS;
    }

    if (num1 < 0 || num2 < 0)
    {
        return LONG_WORD;
    }

    int was_print = 0;
    print_words(words1, num1, words2, num2, &was_print);
    print_words(words2, num2, words1, num1, &was_print);

    if (was_print == 0)
    {
        return NO_UNIQUE_WORDS;
    }

    puts("");

    return OK;
}

