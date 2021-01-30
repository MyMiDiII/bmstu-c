#ifndef __IO_H__

#define __IO_H__

#include "commands.h"
#include "list_matrix.h"

int read_command(command_t *const command);

int read_matrix(list_matrix_t **matrix);

#endif
