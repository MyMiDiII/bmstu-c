#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"
#include "err_defines.h"
#include "list.h"
#include "errors.h"
#include "players.h"

#define ARGS_NUM 4

int parse_args(const int argc, char **argv, char **in,
char **first_out, char **second_out)
{
    LOG_INFO("%s", "parse_args");

    if (argc != ARGS_NUM)
        ERROR("ERR_ARGS_NUM", ERR_ARGS_NUM);

    *in = argv[1];
    *first_out = argv[2];
    *second_out = argv[3];

    LOG_INFO("%s", "parse_args OK");
    return OK;
}

int read(const char *const file, players_array_t *const players, bool *const mem_flag)
{
    LOG_INFO("%s", "read");
    FILE *in_file;

    in_file = fopen(file, "r");
    if (!in_file)
        ERROR("ERR_OPEN_FILE", ERR_OPEN_FILE);

    int exit_code = read_players(in_file, players, mem_flag);

    if (fclose(in_file))
        FREEP_ERROR("ERR_CLOSE_FILE", ERR_CLOSE_FILE);

    LOG_INFO("%s", "read end");
    return exit_code;
}

int write(const char *const file, node_t *head)
{
    LOG_INFO("%s", "write");
    FILE *out_file = fopen(file, "w");

    if (!out_file)
        ERROR("ERR_OPEN_FILE", ERR_OPEN_FILE);

    int len = length(head);
    int count = 0;
    count = fprintf(out_file, "%d\n", len);
    for (node_t *cur = head; count >= 0 && cur; cur = cur->next)
    {
        count = fprintf(out_file, "%s\n", ((player_t *)cur->data)->name);
        
        if (count >= 0)
            count = fprintf(out_file, "%d\n", ((player_t *)cur->data)->rating);
    }

    if (fclose(out_file))
        ERROR("ERR_CLOSE_FILE", ERR_CLOSE_FILE);

    if (count < 0)
        ERROR("ERR_WRITE_FILE", ERR_WRITE_FILE);

    LOG_INFO("%s", "write OK");
    return OK;
}
