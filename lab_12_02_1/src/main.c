#include <stdio.h>

#include "array.h"
#include "errors.h"
#include "fileio.h"
#include "mysort.h"
#include "macrologger.h"

int main(int argc, char **argv)
{
    LOG_INFO("%s", "BEGIN");

    FILE *input_file;
    FILE *output_file;
    int exit_code = OK;
    size_t num;
    array_t array, filtered_array;

    exit_code = check_main_parametrs(argc, argv);

    if (!exit_code)
    {
        input_file = fopen(*(argv + 1), "r");
        exit_code = check_open_file(input_file, ERR_OPEN_INPUT_FILE);
    }

    if (!exit_code)
    {
        LOG_INFO("%s", "The file was opened successfully!");
        output_file = fopen(*(argv + 2), "w");
        exit_code = check_open_file(output_file, ERR_OPEN_OUTPUT_FILE);
    }

    if (!exit_code)
    {
        LOG_INFO("%s", "The file was opened successfully!");
        exit_code = count_num(input_file, &num);
    }

    if (!exit_code)
        exit_code = create_array(input_file, num, &array);

    if (!exit_code && argc == 4)
    {
        exit_code = key(array.arr, array.end, &filtered_array.arr, &filtered_array.end);

        if (!exit_code)
            mysort(filtered_array.arr, filtered_array.end - filtered_array.arr,
                   sizeof(int), &compare_int);

        if (!exit_code)
            exit_code = write_to_file(output_file, &filtered_array);
    }
    else if (!exit_code)
    {
        mysort(array.arr, array.end - array.arr, sizeof(int), &compare_int);
        if (!exit_code)
            exit_code = write_to_file(output_file, &array);
    }

    close_and_free(input_file, output_file, &array, &filtered_array, argc, &exit_code);

    print_error(exit_code);

    return exit_code;
}