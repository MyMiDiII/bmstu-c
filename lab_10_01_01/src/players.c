#include <stdlib.h>
#include <stdbool.h>

#include "players.h"
#include "macrologger.h"
#include "err_defines.h"
#include "errors.h"
#include "list.h"
#include "comparators.h"

int read_number(int *const number, FILE *file)
{
    LOG_INFO("%s", "read_number");

    if (fscanf(file, "%d\n", number) != 1)
        ERROR("ERR_NUMBER", ERR_NUMBER);

    LOG_DEBUG("number = %d", *number);
    if (*number <= 0)
        ERROR("ERR_NUMBER", ERR_NUMBER);

    LOG_INFO("%s", "read_number OK");
    return OK;
}

int read_name(char **name, FILE *file)
{
    LOG_INFO("%s", "read_name");

    if (!name || !file)
        ERROR("ERR_POINTER", ERR_POINTER);

    *name = malloc(sizeof(char));

    if (!name)
        ERROR("ERR_MEMORY", ERR_MEMORY);

    int len = 0;
    int capacity = 1;

    char cur_ch;
    while ((cur_ch = getc(file)) != '\n' && cur_ch != EOF)
    {
        LOG_DEBUG("len = %d", len);
        LOG_DEBUG("capacity = %d", capacity);
        LOG_DEBUG("cur_ch = %c", cur_ch);

        if (len >= capacity - 1)
        {
            char *tmp = realloc(*name, capacity * 2 * sizeof(char));

            if (!tmp)
            {
                free(*name);
                ERROR("ERR_MEMORY", ERR_MEMORY);
            }

            *name = tmp;
            capacity *= 2;
        }

        (*name)[len++] = cur_ch;
    }

    (*name)[len] = '\0';

    LOG_INFO("%s", "read_name OK");
    return OK;
}

int read_players(FILE *file, players_array_t *const players, bool *mem_flag)
{
    LOG_INFO("%s", "read_players");

    if (!players)
        ERROR("ERR_POINTER", ERR_POINTER);

    int number;
    if (read_number(&number, file))
        ERROR("ERR_NUMBER", ERR_NUMBER);

    players->arr = malloc(sizeof(player_t) * number);

    if (!players->arr)
        ERROR("ERR_MEMORY", ERR_MEMORY);

    players->len = 0;
    players->capacity = number;

    for (int i = 0; i < number; i++)
    {
        LOG_DEBUG("i = %d", i);
        player_t current;
        char *p = NULL;

        if (read_name(&p, file))
            FREEP_ERROR("ERR_NAME_READ", ERR_NAME_READ);

        current.name = p;

        if (fscanf(file, "%d\n", &current.rating) != 1)
            FREEPN_ERROR("ERR_RATING_READ", ERR_RATING_READ);

        LOG_DEBUG("rating = %d", current.rating);

        if (arr_append(players, &current))
            FREEP_ERROR("ERR_APPEND", ERR_APPEND);
    }

    *mem_flag = true;
    LOG_INFO("%s", "read_players OK");
    return OK;
}

int set(players_array_t *const arr, const int index, const player_t *const element)
{
    LOG_INFO("%s", "set");

    if (!arr || !element)
        ERROR("ERR_POINTER", ERR_POINTER);

    LOG_DEBUG("index = %d", index);
    LOG_DEBUG("arr->len - 1 = %d", arr->len - 1);

    if (index < 0 || index > arr->len - 1)
        ERROR("ERR_INDEX", ERR_INDEX);

    arr->arr[index] = *element;

    LOG_INFO("%s", "set OK");
    return OK;
}

int arr_append(players_array_t *const arr, const player_t *const element)
{
    LOG_INFO("%s", "arr_append");

    if (!arr || !element)
        ERROR("ERR_POINTER", ERR_POINTER);

    LOG_DEBUG("arr = %p", (void *) arr->arr);
    LOG_DEBUG("capacity = %d", arr->capacity);

    if ((!arr->arr && arr->capacity) || (arr->arr && !arr->capacity))
        ERROR("ERR_ARR_PARAMETERS", ERR_ARR_PARAMETERS);

    LOG_DEBUG("len = %d", arr->len);

    if (arr->len >= arr->capacity)
    {
        int new_capasity = (!arr->arr && !arr->len && !arr->capacity) ? 1 : arr->capacity * 2;
        LOG_DEBUG("new_capasity = %d", new_capasity);
        player_t *tmp = realloc(arr->arr, new_capasity * sizeof(player_t));

        if (!tmp)
            ERROR("ERR_MEMORY", ERR_MEMORY);

        arr->arr = tmp;
        arr->capacity = new_capasity;
    }

    if (set(arr, arr->len++, element))
    {
        arr->len--;
        ERROR("ERR_APPEND", ERR_APPEND);
    }

    LOG_INFO("%s", "arr_append OK");
    return OK;
}

int free_array(players_array_t *const arr)
{
    LOG_INFO("%s", "free_array");

    if (!arr)
        ERROR("ERR_POINTER", ERR_POINTER);

    if (arr->arr)
        for (int i = 0; i < arr->len; i++)
        {
            LOG_DEBUG("i = %d", i);
            free(arr->arr[i].name);
        }

    free(arr->arr);

    LOG_INFO("%s", "free_array OK");
    return OK;
}

int create_players_list(const players_array_t *const players, node_t **head,
                        bool *const list_mem_flag)
{
    LOG_INFO("%s", "create_players_list");

    if (!head)
        ERROR("ERR_POINTER", ERR_POINTER);

    *head = NULL;

    for (int i = 0; i < players->len; i++)
    {
        LOG_DEBUG("i = %d", i);
        node_t *node = malloc(sizeof(node_t));

        if (!node)
            FREELIST_ERROR("ERR_MEMORY", ERR_MEMORY);

        node->data = players->arr + i;
        LOG_DEBUG("node->data = %s", ((player_t *)node->data)->name); 
        insert(head, node, NULL);
    }

    *list_mem_flag = true;
    LOG_INFO("%s", "create_players_list OK");
    return OK;
}

int create_result_lists(node_t **head, node_t **back)
{
    LOG_INFO("%s", "create_result_lists");

    if (!head || !back)
        ERROR("ERR_POINTER", ERR_POINTER);

    int len = length(*head);
    *back = NULL;

    if (!len || 1 == len)
        ERROR("ERR_EMPTY_LIST", ERR_EMPTY_LIST);

    *head = sort(*head, compare_players);
    front_back_split(*head, back);

    if (len % 2)
        pop_back(head);

    *back = reverse(*back);

    LOG_INFO("%s", "create_result_lists OK");
    return OK;
}
