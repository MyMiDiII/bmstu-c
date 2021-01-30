#ifndef __AVERAGE_H__

#define __AVERAGE_H__

#ifndef NO_NUMBERS

#define NO_NUMBERS -3

#endif

int find_min_max_average(FILE *file, double *const average);

void count_greater_average(FILE *file, const double average, int *const num);

#endif