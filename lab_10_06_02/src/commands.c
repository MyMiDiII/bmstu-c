#include "commands.h"
#include "io.h"
#include "errors.h"
#include "list_matrix.h"

int do_out(void)
{
    int exit_code = OK;

    list_matrix_t *matrix;
    exit_code = read_matrix(&matrix);

    if (!exit_code)
        exit_code = print_list_matrix(matrix);

    free_matrix(matrix);
    return exit_code;
}

int do_add_or_mul(const command_t command)
{
    int exit_code = OK;

    list_matrix_t *matrix1 = NULL;
    list_matrix_t *matrix2 = NULL;
    list_matrix_t *result = NULL;

    exit_code = read_matrix(&matrix1);

    if (!exit_code)
        exit_code = read_matrix(&matrix2);

    if (!exit_code)
    {
        if (ADD == command)
            exit_code = add(matrix1, matrix2, &result);
        else if (MUL == command)
            exit_code = multiply(matrix1, matrix2, &result);
        else
            exit_code = ERR_WRONG_COMMAND;
    }

    if (!exit_code)
        exit_code = print_list_matrix(result);

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
    return exit_code;
}

int do_lin(void)
{
    int exit_code = OK;

    list_matrix_t *matrix;
    exit_code = read_matrix(&matrix);

    if (!exit_code)
        exit_code = delete_row_with_max(&matrix);

    if (!exit_code)
        exit_code = print_list_matrix(matrix);

    free_matrix(matrix);
    return exit_code;
}
