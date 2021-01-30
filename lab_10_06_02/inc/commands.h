#ifndef __COMMANDS_H__

#define __COMMANDS_H__

#define OUT 0
#define ADD 1
#define MUL 2
#define LIN 3

typedef unsigned int command_t;

int do_out(void);

int do_add_or_mul(const command_t command);

int do_lin(void);

#endif
