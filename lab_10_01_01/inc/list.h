#ifndef __LIST_H__

#define __LIST_H__

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

void *pop_back(node_t **head);

void insert(node_t **head, node_t *elem, node_t *before);

node_t *reverse(node_t *head);

void front_back_split(node_t *head, node_t **back);

node_t *sorted_merge(node_t **head_a, node_t **head_b,
int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

int length(node_t *head);

void free_list(node_t **head);

#endif
