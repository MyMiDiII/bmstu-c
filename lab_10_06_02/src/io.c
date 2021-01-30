#include <stdio.h>
#include <string.h>

#include "io.h"
#include "errors.h"
#include "macrologger.h"

#define COMMAND_STRING_LEN 5
#define COMMAND_LEN 3

int read_command(command_t *const command)
{
    char string[COMMAND_STRING_LEN];
    char ch;
    short int len = 0;

    while (len < COMMAND_STRING_LEN &&(ch = getchar()) != '\n' && ch != EOF)
        string[len++] = ch;

    LOG_DEBUG("len = %d", len);
    if (len < COMMAND_LEN || len > COMMAND_LEN)
        return ERR_WRONG_COMMAND;

    string[len] = '\0';

    if (!strcmp(string, "out"))
        *command = OUT;
    else if (!strcmp(string, "add"))
        *command = ADD;
    else if (!strcmp(string, "mul"))
        *command = MUL;
    else if (!strcmp(string, "lin"))
        *command = LIN;
    else
        return ERR_WRONG_COMMAND;

    return OK;
}

int read_matrix(list_matrix_t **matrix)
{
    *matrix = NULL;
    int rows, columns;

    if (scanf("%d", &rows) != 1 || rows <= 0)
        return ERR_READ_MATRIX;

    if (scanf("%d", &columns) != 1 || columns <= 0)
        return ERR_READ_MATRIX;

    int exit_code = OK;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int cur_element;

            if (scanf("%d", &cur_element) != 1)
            {
                free_matrix(*matrix);
                *matrix = NULL;
                return ERR_READ_MATRIX;
            }
            else if (cur_element)
            {
                list_matrix_t *node;
                exit_code = create_node(i, j, cur_element, &node);

                append(matrix, node);
            }

            if (exit_code)
            {
                free_matrix(*matrix);
                *matrix = NULL;
                return ERR_MEMORY;
            }
        }
    }

    return OK;
}
