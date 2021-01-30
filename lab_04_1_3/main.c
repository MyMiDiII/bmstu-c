#include <stdio.h>
#include <string.h>

#include "read_str_h.h"
#include "split_str_h.h"
#include "create_str.h"

#define OK 0
#define EMPTY_STRING 1
#define LONG_STRING 2 
#define NO_WORDS 3
#define LONG_WORD 4
#define EMPTY_RESULT 5 

#define STR_MAX_LEN 256
#define MAX_NUM_WORDS 128

int main(void)
{
    char str[STR_MAX_LEN + 2];
    char words[MAX_NUM_WORDS][WORD_MAX_LEN + 1];
    char symbols[] = " ,;:-.!?";

    int len = read_str_h(str, STR_MAX_LEN + 2);

    if (0 == len)
    {
        return EMPTY_STRING;
    }

    if (len > STR_MAX_LEN)
    {
        return LONG_STRING;
    }

    int number = split_str_h(str, words, symbols);

    if (0 == number)
    {
        return NO_WORDS;
    }

    if (number < 0)
    {
        return LONG_WORD;
    }

    char new_str[STR_MAX_LEN + 1];
    int len_new = create_str(words, number, new_str);

    if (0 == len_new)
    {
        return EMPTY_RESULT;
    }

    printf("Result: %s\n", new_str);

    return OK;
}

