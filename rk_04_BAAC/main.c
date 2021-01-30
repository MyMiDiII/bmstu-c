#include <stdio.h>

#include "list.h"
#include "fileio.h"

#define OK 0
#define ERR_FILE_IN 1
#define ERR_FILE_OUT 2

int main(int argc, char **argv)
{
    int exit_code = OK;
    FILE *in_file = NULL;
    FILE *out_file = NULL;
    node_t *head = NULL;

    in_file = fopen(argv[1], "r");

    if (!in_file)
        exit_code = ERR_FILE_IN;

    if (!exit_code)
        out_file = fopen(argv[2], "w");

    if (!exit_code && !out_file)
        exit_code = ERR_FILE_OUT;

    if (!exit_code)
    {
        read_list(&head, in_file);
        reverse(head);
        write_list(head, out_file);
    }

    if (exit_code != ERR_FILE_IN)
        fclose(in_file);

    if (exit_code != ERR_FILE_OUT)
        fclose(out_file);

    free_list(head);

    return exit_code;
}
