#include <stdio.h>
#include <stdbool.h>

#include "list.h"
#include "fileio.h"
#include "errors.h"
#include "list.h"
#include "players.h"
#include "macrologger.h"

int main(int argc, char **argv)
{
    int exit_code = OK;
    char *in_name, *out_name_1, *out_name_2;
    players_array_t players = { .arr = NULL, .len = 0, .capacity = 0 };
    node_t *in_list = NULL, *out_list = NULL;
    bool arr_mem_flag = false;
    bool list_mem_flag = false; 

    exit_code = parse_args(argc, argv, &in_name, &out_name_1, &out_name_2);

    if (!exit_code)
        exit_code = read(in_name, &players, &arr_mem_flag);

    if (!exit_code)
        exit_code = create_players_list(&players, &in_list, &list_mem_flag);

    if (!exit_code)
        exit_code = create_result_lists(&in_list, &out_list); 

    if (!exit_code)
        exit_code = write(out_name_1, in_list);

    if (!exit_code)
        exit_code = write(out_name_2, out_list);

    if (arr_mem_flag)
        free_array(&players);

    if (list_mem_flag)
    {
        free_list(&in_list);
        free_list(&out_list);
    }
    
    return exit_code;
}
