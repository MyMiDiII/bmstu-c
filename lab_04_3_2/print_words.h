#ifndef __PRINT_WORDS_H__

#define __PRINT_WORDS_H__

#include <stdbool.h>

#ifndef WORD_MAX_LEN 

#define WORD_MAX_LEN 16

#endif

bool is_matching(const char *str1, const char *str2);

int print_words(char (*words1)[WORD_MAX_LEN + 1], const int len1,
char (*words2)[WORD_MAX_LEN + 1], const int len2, int *const was_print);

#endif

