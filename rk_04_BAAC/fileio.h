#ifndef __FILEIO_H__

#define __FILEIO_H__

#include <stdio.h>
#include "list.h"

int read_list(node_t **head, FILE *file);

void write_list(node_t *head, FILE *file);

#endif
