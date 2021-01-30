#ifndef __SPLIT_H__

#define __SPLIT_H__

#include <stdbool.h>

#ifndef WORD_MAX_LEN

#define WORD_MAX_LEN 16

#endif

bool is_in_symbols(const char symbol, const char *delim);

int split(const char *str, char (*words)[WORD_MAX_LEN + 1], const char *symbols);

#endif

