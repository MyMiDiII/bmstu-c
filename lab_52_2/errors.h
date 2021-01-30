#ifndef __ERRORS_H__

#define __ERRORS_H__

#define OK 0
#define WRONG_PARAMETRS 53
#define NO_FILE -1
#define EMPTY_FILE -2
#define OPEN_ERROR -3
#define WRONG_SIZE -4
#define NO_PRODUCTS -5
#define READ_ERROR -6

void print_error(const int error);

#endif