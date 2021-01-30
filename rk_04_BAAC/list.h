#ifndef __LIST_H__

#define __LIST_H__

#define MAX_WORD_LEN 10

typedef struct node node_t;

struct node
{
    char word[MAX_WORD_LEN + 1];
    int word_len;
    node_t *next;
};

void reverse(node_t *head);

void push(node_t **head, node_t *element);

void free_list(node_t *head);

#endif
