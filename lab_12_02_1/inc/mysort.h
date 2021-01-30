#ifndef __MYSORT_H__

#define __MYSORT_H__

#include <stdio.h>

void swap(void *first, void *second, size_t size);

int compare_int(const void *const first, const void *const second);

void mysort(void *first, size_t number, size_t size,
            int (*comparator)(const void *, const void *));

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif