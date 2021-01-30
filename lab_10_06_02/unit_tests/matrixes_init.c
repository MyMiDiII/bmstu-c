#include <stdlib.h>

#include "matrixes_init.h"
#include "list_matrix.h"

list_matrix_t *create_matrix(const int *const values, const int rows, const int columns)
{
    list_matrix_t *result = NULL;
    list_matrix_t *end = NULL;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (values[i * columns + j])
            {
                list_matrix_t *node = malloc(sizeof(list_matrix_t));
                node->data.row = i;
                node->data.column = j;
                node->data.value = values[i * columns + j];
                node->next = NULL;
                end ? (end->next = node) : (result = node);
                end = node;
            }

    return result;
}
