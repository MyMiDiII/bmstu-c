#ifndef __SORT_BIN_H__

#define __SORT_BIN_H__

int sort_bin_file(FILE *file);

int get_number_by_pos(FILE *file, const int pos);

void put_number_by_pos(FILE *file, const int pos, const int num);

#endif