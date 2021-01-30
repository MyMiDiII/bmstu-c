#ifndef __ERRORS_H__

#define __ERRORS_H__

#define OK 0
#define INVALID_NUM_MAIN_PARAMETRS -1
#define THIRD_NOT_NATURAL -2
#define NO_FILE -3
#define WRONG_MODE -4
#define EMPTY_FILE -5
#define OPEN_ERROR -6
#define WRONG_SIZE -7

void print_error(const int error);

#endif