#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "macrologger.h"
#include "err_defines.h"

void *pop_back(node_t **head)
{
    LOG_INFO("%s", "pop_back");

    if (!head || !*head)
        ERROR("ERR_NULL_POINTERS", NULL);

    node_t *cur_node, *prev_node = *head;
    for (cur_node = *head; cur_node->next; cur_node = cur_node->next)
        prev_node = cur_node;

    LOG_DEBUG("cur_node->next = %p", (void *) cur_node->next);
    void *data = cur_node->data;
    prev_node->next = NULL;
    *head = (cur_node == *head) ? NULL : *head;
    free(cur_node);

    LOG_INFO("%s", "pop_back OK");
    return data;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    LOG_INFO("%s", "insert");

    if (!head || !elem)
        return;

    if (!*head && before)
        return;

    node_t tmp = { .data = NULL, .next = *head };
    node_t *cur = &tmp;
    
    for (; cur && cur->next != before; cur = cur->next);

    if (!cur)
        return;

    LOG_DEBUG("cur = %p", (void *) cur);
    elem->next = cur->next;
    cur->next = elem;
    *head = (before == *head) ? elem : *head;

    LOG_INFO("%s", "insert OK");
}

node_t *reverse(node_t *head)
{
    LOG_INFO("%s", "reverse");

    node_t *cur_node = head;
    node_t *prev_node = NULL;

    while (cur_node)
    {
        LOG_DEBUG("cur_node = %p", (void *) cur_node);
        LOG_DEBUG("prev_node = %p", (void *) prev_node);
        node_t *next = cur_node->next;
        cur_node->next = prev_node;
        prev_node = cur_node;
        cur_node = next;
    }

    LOG_INFO("%s", "reverse OK");
    return prev_node;
}

void front_back_split(node_t *head, node_t **back)
{
    LOG_INFO("%s", "front_back_split");
    int len = length(head);
    LOG_DEBUG("%d", len);

    node_t *cur_node = head;
    for (size_t i = 0; cur_node && i < len / 2 + len % 2 - 1; i++)
        cur_node = cur_node->next;

    *back = (cur_node) ? cur_node->next : NULL; 
    (cur_node) ? (cur_node->next = NULL) : NULL;
    LOG_DEBUG("back = %p", (void *) *back);
    LOG_INFO("%s", "front_back_split OK");
}

void move_node(node_t **from, node_t **result, node_t **end)
{
    LOG_INFO("%s", "move_node");

    node_t *cur_node = *from;
    *from = (*from)->next;
    cur_node->next = NULL;
    (*end) ? ((*end)->next = cur_node) : (*result = cur_node);
    *end = cur_node;

    LOG_INFO("%s", "move_node OK");
}

node_t *sorted_merge(node_t **head_a, node_t **head_b,
        int (*comparator)(const void *, const void *))
{
    LOG_INFO("%s", "sorted_merge");

    if (!head_a || !head_b || !comparator)
        return NULL;

    node_t *result = NULL;
    node_t *end = NULL;

    while (*head_a || *head_b)
    {
        if (!*head_a)
            move_node(head_b, &result, &end);
        else if (!*head_b)
            move_node(head_a, &result, &end);
        else if ((*comparator)((*head_a)->data, (*head_b)->data) < 0)
            move_node(head_a, &result, &end);
        else
            move_node(head_b, &result, &end);
    }

    LOG_INFO("%s", "sorted_merge OK");
    return result;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    LOG_INFO("%s", "sort");

    if (!head)
        return NULL;

    if (!head->next)
        return head;

    node_t *back;

    front_back_split(head, &back);

    head = sort(head, comparator);
    back = sort(back, comparator);

    LOG_INFO("%s", "sort end");
    return sorted_merge(&head, &back, comparator);
}

int length(node_t *head)
{
    LOG_INFO("%s", "length");

    int len = 0;
    node_t *cur_node;

    for (cur_node = head; cur_node; cur_node = cur_node->next)
        len++;

    return len;

    LOG_INFO("%s", "length OK");
}

void free_list(node_t **head)
{
    LOG_INFO("%s", "free_list");

    if (!head)
        return;

    for (node_t *cur = *head; cur; )
    {
        LOG_DEBUG("cur = %p", (void *) cur);
        node_t *next = cur->next;
        free(cur);
        cur = next;
    }

    *head = NULL;
    LOG_INFO("%s", "free_list OK");
}
