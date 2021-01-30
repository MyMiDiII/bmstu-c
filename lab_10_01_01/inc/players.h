#ifndef __PLAYERS_H__

#define __PLAYERS_H__

#include <stdio.h>
#include <stdbool.h>
#include "list.h"

#define OK 0

typedef struct player
{
    char *name;
    int rating;
} player_t;

typedef struct players_array
{
    player_t *arr;
    int len;
    int capacity;
} players_array_t;

int set(players_array_t *const arr, const int index, const player_t *const element);

int arr_append(players_array_t *const arr, const player_t *const element);

int free_array(players_array_t *const arr);

int read_players(FILE *file, players_array_t *const players, bool *mem_flag);

int create_players_list(const players_array_t *const players, node_t **head,
bool *const list_mem_flag);

int create_result_lists(node_t **head, node_t **back);

#endif
