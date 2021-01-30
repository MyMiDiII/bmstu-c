#include "comparators.h"
#include "players.h"

int compare_int(const void *first, const void *second)
{
    int num_1 = *(int *) first;
    int num_2 = *(int *) second;
    
    if (num_1 > num_2)
        return GREATER;
    else if (num_1 < num_2)
        return LESS;

    return EQUAL;
}

int compare_players(void const *first, void const *second)
{
    player_t *player_1 = (player_t *) first;
    player_t *player_2 = (player_t *) second;
    
    if (player_1->rating < player_2->rating)
        return GREATER;
    else if (player_1->rating > player_2->rating)
        return LESS;

    return EQUAL;
}
