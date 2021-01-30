#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "fileio.h"

#define OK 0
#define ERR_READ 3
#define ERR_MEMORY 4

int read_element(node_t **tmp, FILE *file, char *const ch)
{
    *tmp = malloc(sizeof(node_t));

    if (!tmp)
        return ERR_MEMORY;

    while ((*ch = getc(file)) != '\n' && *ch != EOF)
    {
        if ((*tmp)->word_len < MAX_WORD_LEN)
            (*tmp)->word[(*tmp)->word_len++] = *ch;

        else
            return ERR_READ;
    }

    (*tmp)->word[(*tmp)->word_len] = '\0';

    return OK;
}

int read_list(node_t **head, FILE *file)
{
    char ch = '\0';

    while (ch != EOF)
    {
        node_t *tmp = NULL;
        read_element(&tmp, file, &ch);
        if (tmp)
            push(head, tmp);
    }

    return OK;
}

void write_list(node_t *head, FILE *file)
{
    for (node_t *cur = head; cur; cur = cur->next)
        fprintf(file, "%s ", cur->word);
}
