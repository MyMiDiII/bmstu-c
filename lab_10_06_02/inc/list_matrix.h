#ifndef __LIST_MATRIX_H__

#define __LIST_MATRIX_H__

#include <stddef.h>

typedef struct element
{
    size_t row;
    size_t column;
    int value; 
} element_t;

typedef struct list_matrix list_matrix_t;

struct list_matrix
{
    element_t data;
    list_matrix_t *next;
};

void element_init(const size_t row, const size_t column, const int value,
element_t *const element);

int node_init(const element_t *const data, list_matrix_t **node);

int create_node(const size_t row, const size_t column,
const int value, list_matrix_t **node);

void append(list_matrix_t **head, list_matrix_t *elem);

int add(list_matrix_t *matrix1, list_matrix_t *matrix2, list_matrix_t **result);

int multiply(list_matrix_t *matrix1, list_matrix_t *matrix2, list_matrix_t **result);

int delete_row_with_max(list_matrix_t **matrix);

int print_list_matrix(list_matrix_t *matrix);

void free_matrix(list_matrix_t *matrix);

#endif
