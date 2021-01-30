#ifndef __FILEIO_H__

#define __FILEIO_H__

#include <stdbool.h>
#include "players.h"

int parse_args(const int argc, char **argv, char **in,
char **first_out, char **second_out);

int read(const char *const file, players_array_t *const players, bool *const mem_flag);

int write(const char *const file, node_t *head);

#endif
