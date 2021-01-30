#include <stdlib.h>

#include "list.h"

void reverse(node_t *head)
{
    for (node_t *cur = head; cur; cur = cur->next)
    {
        for (int i = 0; i < cur->word_len / 2; i++)
        {
            char tmp = cur->word[i];
            cur->word[i] = cur->word[cur->word_len - 1 - i];
            cur->word[cur->word_len - 1 - i] = tmp;
        }
    }
}

void push(node_t **head, node_t *element)
{
    if (!head)
        return;

    element->next = NULL;

    if (!*head)
        *head = element;
    else
    {
        node_t *cur = *head;
        for (; cur && cur->next; cur = cur->next);
        cur->next = element;
    }
}

void free_list(node_t *head)
{
    for (node_t *cur = head; cur;)
    {
        node_t *next = cur->next;
        free(cur);
        cur = next;
    }
}
