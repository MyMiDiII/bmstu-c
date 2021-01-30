#ifndef __CREATE_STR_H__

#define __CREATE_STR_H__

#ifndef WORD_MAX_LEN

#define WORD_MAX_LEN 16

#endif

void unique_copy(char *const where, const char *what, int *const len);

int create_str(char (*words)[WORD_MAX_LEN + 1], const int len, char *const new_str);

#endif

