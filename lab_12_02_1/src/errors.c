#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"
#include "macrologger.h"
#include "array.h"

void print_error(const int err_code)
{
    switch (err_code)
    {
        case ERR_INVALID_MAIN_PARAMETERS:
            fprintf(stderr, "Invalid main parameters.\n");
            break;
        case ERR_OPEN_INPUT_FILE:
            fprintf(stderr, "Error opening the input file.\n");
            break;
        case ERR_EMPTY_FILE:
            fprintf(stderr, "Input file is empty.\n");
            break;
        case ERR_OPEN_OUTPUT_FILE:
            fprintf(stderr, "Error opening the output file.\n");
            break;
        case ERR_READ_FILE:
            fprintf(stderr, "Error reading file.\n");
            break;
        case ERR_CREATE_ARRAY:
            fprintf(stderr, "Error creating array.\n");
            break;
        case ERR_EMPTY_FILTER:
            fprintf(stderr, "There are not elements after filtering.\n");
            break;
        case ERR_FSEEK:
            fprintf(stderr, "Error executing fseek.\n");
            break;
        case ERR_FPRINTF:
            fprintf(stderr, "Error executing fprintf.\n");
            break;
        case ERR_NULL_POINTER:
            fprintf(stderr, "There are null pointer in functions argument.\n");
            break;
        case ERR_WRONG_POINTERS:
            fprintf(stderr, "There are wrong pointers in funcrions argument.\n");
            break;
        case ERR_FCLOSE:
            fprintf(stderr, "Error executing fclose.\n");
            break;
        case ERR_CREATE_FILTERED_ARRAY:
            fprintf(stderr, "Error creating array by filter.\n");
            break;
        default:
            break;
    }
}

int check_main_parametrs(int argc, char **argv)
{
    if (argv == NULL)
    {
        LOG_ERROR("%s", "ERR_NULL_POINTER");
        return ERR_NULL_POINTER;
    }

    if ((argc != 3 && argc != 4) || (argc == 4 && strcmp(*(argv + 3), "f")))
    {
        LOG_ERROR("%s", "ERR_INVALID_MAIN_PARAMETERS");
        return ERR_INVALID_MAIN_PARAMETERS;
    }

    return OK;
}

int check_open_file(FILE *file, const int mode)
{
    if (!file)
    {
        if (ERR_OPEN_INPUT_FILE == mode)
            LOG_ERROR("%s", "ERR_OPEN_INPUT_FILE");
        else
            LOG_ERROR("%s", "ERR_OPEN_OUTPUT_FILE");
        
        return mode;
    }

    return OK;
}

void close_and_free(FILE *input_file, FILE *output_file,
                    array_t *array, array_t *filtered_array,
                    const int argc, int *const exit_code)
{
    if (*exit_code < ERR_OPEN_INPUT_FILE || !*exit_code)
        if (fclose(input_file))
            *exit_code = ERR_FCLOSE;

    if (*exit_code < ERR_OPEN_OUTPUT_FILE || !*exit_code)
        if (fclose(output_file))
            *exit_code = ERR_FCLOSE;

    if (*exit_code < ERR_CREATE_ARRAY || !*exit_code)
        free(array->arr);

    if (argc == 4 && (*exit_code < ERR_CREATE_FILTERED_ARRAY || !*exit_code))
        free(filtered_array->arr);
}