#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "list_matrix.h"
#include "macrologger.h"
#include "err_defines.h"
#include "errors.h"

#define GREATER 1
#define LESS -1
#define EQUAL 0

#define ADD_ELEMENT(element, matrix) (element = matrix->data, matrix = matrix->next)

void element_init(const size_t row, const size_t column, const int value,
element_t *const element)
{
    LOG_INFO("%s", "element_init");

    if (!element)
        return;

    element->row = row;
    element->column = column;
    element->value = value;

    LOG_INFO("%s", "element_init OK");
}  

int node_init(const element_t *const data, list_matrix_t **node)
{
    LOG_INFO("%s", "node_init");

    if (!node || !data)
        ERROR("ERR_NULL_POINTER", ERR_NULL_POINTER);

    *node = malloc(sizeof(list_matrix_t));

    if (!*node)
        ERROR("ERR_MEMORY", ERR_MEMORY);

    (*node)->data.row = data->row;
    (*node)->data.column = data->column;
    (*node)->data.value = data->value;
    (*node)->next = NULL;

    LOG_INFO("%s", "node_init OK");
    return OK;
}

int create_node(const size_t row, const size_t column,
                const int value, list_matrix_t **node)
{
    element_t element; 
    element_init(row, column, value, &element);
    return node_init(&element, node);
}

int compare_matrix_elements(const element_t *const el1, const element_t *const el2)
{
    if (el1->row == el2->row && el1->column == el2->column)
        return EQUAL;
    else if (el1->row > el2->row || (el1->row == el2->row && el1->column > el2->column))
        return GREATER;
    else
        return LESS;
}

void insert(list_matrix_t **head, list_matrix_t *elem, list_matrix_t *before)
{
    LOG_INFO("%s", "insert");

    if (!head || !elem)
        return;

    if (!*head && before)
        return;

    list_matrix_t tmp = { .next = *head };
    list_matrix_t *cur = &tmp;
    
    for (; cur && cur->next != before; cur = cur->next);

    if (!cur)
        return;

    LOG_DEBUG("cur = %p", (void *) cur);
    elem->next = cur->next;
    cur->next = elem;
    *head = (before == *head) ? elem : *head;

    LOG_INFO("%s", "insert OK");
}

void append(list_matrix_t **head, list_matrix_t *elem)
{
    insert(head, elem, NULL);
}

int add(list_matrix_t *matrix1, list_matrix_t *matrix2, list_matrix_t **result)
{
    LOG_INFO("%s", "add");

    if (!result)
        ERROR("ERR_NULL_POINTER", ERR_NULL_POINTER);

    int exit_code = OK;
    *result = NULL;

    while (!exit_code && (matrix1 || matrix2))
    {
        element_t element;

        if (!matrix1)
            ADD_ELEMENT(element, matrix2);
        else if (!matrix2)
            ADD_ELEMENT(element, matrix1);
        else if (compare_matrix_elements(&matrix1->data, &matrix2->data) < 0)
            ADD_ELEMENT(element, matrix1);
        else if (compare_matrix_elements(&matrix1->data, &matrix2->data) > 0)
            ADD_ELEMENT(element, matrix2);
        else
        {
            element_init(matrix1->data.row, matrix1->data.column,
            matrix1->data.value + matrix2->data.value, &element);
            matrix1 = matrix1->next;
            matrix2 = matrix2->next;
        }

        list_matrix_t *node;
        exit_code = node_init(&element, &node);
        
        if (exit_code)
        {
            free_matrix(*result);
            *result = NULL;
        }
        else
            append(result, node);
    }

    LOG_INFO("%s", "add end");
    return exit_code;
}

void go_next_row(list_matrix_t **ptr)
{
    if (!ptr || !*ptr)
        return;

    int cur_row = (*ptr)->data.row;

    while (*ptr && (*ptr)->data.row == cur_row)
        *ptr = (*ptr)->next;
} 

size_t length(list_matrix_t *head)
{
    LOG_INFO("%s", "length");

    size_t len = 0;
    list_matrix_t *cur_node;

    for (cur_node = head; cur_node; cur_node = cur_node->next)
        len++;

    LOG_INFO("%s", "length OK");
    return len;
}

size_t find_min_column(list_matrix_t *matrix, const size_t prev_min_column,
                       const bool is_first)
{
    LOG_INFO("%s", "find_min_column");
    size_t min_column = 0;
    bool is_init = false;

    for (list_matrix_t *cur = matrix; cur; cur = cur->next)
    {
        LOG_DEBUG("min_column = %ld", min_column);
        LOG_DEBUG("1 = %d", is_first);
        LOG_DEBUG("2 = %d", cur->data.column < prev_min_column);
        LOG_DEBUG("3 = %d", !is_init);
        LOG_DEBUG("4 = %d", cur->data.column < min_column);

        if ((is_first || cur->data.column > prev_min_column) && 
            (!is_init || cur->data.column < min_column))
        {
            min_column = cur->data.column;
            is_init = true;
        }
    }

    LOG_INFO("%s", "find_min_column OK");
    return min_column;
}

int transpose(list_matrix_t *matrix, list_matrix_t **transposed)
{
    LOG_DEBUG("%s", "transpose");

    *transposed = NULL;
    if (!matrix)
        return OK;
    
    int exit_code = OK;
    size_t len = length(matrix);
    size_t num = 0;
    size_t min_column = 0;

    while (!exit_code && num != len)
    {
        min_column = find_min_column(matrix, min_column, (*transposed) ? false : true);
        LOG_DEBUG("min_column = %ld", min_column);

        for (list_matrix_t *cur = matrix; cur; cur = cur->next)
        {
            if (cur->data.column == min_column)
            {
                list_matrix_t *node;
                exit_code = create_node(cur->data.column, cur->data.row, cur->data.value, &node);
                append(transposed, node);

                num++;
            }
        }
    }

    return exit_code;
}

int print_list_matrix(list_matrix_t *matrix)
{
    if (!matrix)
        return ERR_EMPTY_MATRIX;

    while (matrix)
    {
        printf("%lu %lu %d%s", matrix->data.row, matrix->data.column,
               matrix->data.value, (matrix->next) ? " " : "\n");
        matrix = matrix->next;
    }

    return OK;
}

int add_element(list_matrix_t **result, const size_t row, const size_t column,
int *const sum)
{
    int exit_code = OK;
    if (*sum != 0)
    {
        list_matrix_t *node;
        exit_code = create_node(row, column, *sum, &node);

        append(result, node);
        *sum = 0;
    }
    return exit_code;
}

int multiply(list_matrix_t *matrix1, list_matrix_t *matrix2, list_matrix_t **result)
{
    LOG_INFO("%s", "multiply");

    if (!result)
        ERROR("ERR_NULL_POINTER", ERR_NULL_POINTER);

    int exit_code = OK;
    *result = NULL;

    list_matrix_t *transposed;
    exit_code = transpose(matrix2, &transposed);
    list_matrix_t *ptr1 = matrix1;
    list_matrix_t *ptr2 = transposed;
    list_matrix_t *cur_row_begin = matrix1;
    int sum = 0;

    while (!exit_code && ptr1 && ptr2)
    {
        LOG_INFO("%s", "general while");
        size_t cur_row = ptr1->data.row;
        size_t cur_column = ptr2->data.row;

        while (ptr2 && ptr2->data.row == cur_column &&
               ptr2->data.column < ptr1->data.column)
        {
            LOG_INFO("%s", "finding element");
            ptr2 = ptr2->next;
        }

        if (ptr2 && ptr2->data.row == cur_column &&
            ptr1->data.column == ptr2->data.column)
        {
            LOG_INFO("%s", "element was found");
            sum += ptr1->data.value * ptr2->data.value;
            ptr2 = ptr2->next;
        }
        
        if (ptr2 && ptr2->data.row == cur_column)
        {
            LOG_INFO("%s", "old row");
            ptr1 = ptr1->next;

            if (ptr1 && ptr1->data.row != cur_row)
            {
                exit_code = add_element(result, cur_row, cur_column, &sum);
                ptr1 = cur_row_begin;
                go_next_row(&ptr2);
            }
            else if (!ptr1)
            {
                exit_code = add_element(result, cur_row, cur_column, &sum);
                go_next_row(&ptr2);

                ptr1 = (!ptr2) ? cur_row_begin : ptr1;
            }
        }
        else 
        {
            LOG_INFO("%s", "new row");
            exit_code = add_element(result, cur_row, cur_column, &sum);
            ptr1 = cur_row_begin;
        }

        if (!ptr2)
        {
            LOG_INFO("%s", "ptr2 is ended");
            go_next_row(&ptr1);
            cur_row_begin = ptr1;
            
            ptr2 = (ptr1) ? transposed : ptr2;
        }
    }

    free_matrix(transposed);
    LOG_INFO("%s", "multiply end");
    return exit_code;
}

size_t find_max_row(list_matrix_t *matrix)
{
    int max;
    size_t max_row = 0;
    bool is_init = false;

    for (list_matrix_t *cur = matrix; cur; cur = cur->next)
    {
        if (!is_init || cur->data.value > max)
        {
           max_row = cur->data.row; 
           max = cur->data.value;
           is_init = true;
        }
    }

    return max_row;
}

void delete(list_matrix_t *elem, list_matrix_t **matrix)
{
    if (!elem || !matrix || !*matrix)
        return;

    list_matrix_t *cur = *matrix;
    list_matrix_t *prev = *matrix;

    for (; cur && cur != elem; cur = cur->next)
        prev = cur;

    if (!cur)
        return;

    prev->next = (cur == prev) ? prev->next : cur->next;
    *matrix = (cur == prev) ? cur->next : *matrix;
    free(cur);
}

int delete_row_with_max(list_matrix_t **matrix)
{
    if (!matrix)
        return ERR_NULL_POINTER;

    size_t row = find_max_row(*matrix);

    for (list_matrix_t *cur = *matrix; cur;)
    {
        if (cur->data.row == row)
        {
            list_matrix_t *next = cur->next;
            delete(cur, matrix);
            cur = next;
        }
        else
        {
            if (cur->data.row > row)
                cur->data.row--;
            cur = cur->next;
        }
    }

    return (*matrix) ? OK : ERR_EMPTY_MATRIX;
}

void free_matrix(list_matrix_t *matrix)
{
    for (list_matrix_t *cur = matrix; cur; )
    {
        list_matrix_t *next = cur->next;
        free(cur);
        cur = next;
    }
}
