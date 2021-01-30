#ifndef __SPLIT_STR_H_H__

#define __SPLIT_STR_H_H__

#ifndef WORD_MAX_LEN

#define WORD_MAX_LEN 16

#endif

int split_str_h(char *const str, char (*words)[WORD_MAX_LEN + 1],
const char *symbols);

#endif

