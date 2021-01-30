#include <stdio.h>
#include <dlfcn.h>

#include "dyn_func_tmp.h"
#include "array.h"
#include "errors.h"

#define IS_OK if (!exit_code) {

#define END_IS_OK }

#define LOAD_LIB(variable_name, name, error) \
IS_OK \
variable_name= dlopen(name, RTLD_NOW); \
exit_code = variable_name ? OK : error; \
END_IS_OK 

#define LOAD_FUNC(variable_name, type, lib, name) \
type variable_name; \
IS_OK \
variable_name = (type) dlsym(lib, name); \
exit_code = variable_name ? OK : ERR_LIB; \
END_IS_OK


int main(int argc, char **argv)
{
    void *err_lib, *mysort_lib, *io_lib;
    FILE *input_file;
    FILE *output_file;
    int exit_code = OK;
    size_t num;
    array_t array, filtered_array;

    LOAD_LIB(err_lib, "./libs/dynamic/liberrors.so", ERR_ERR_LIB);
    LOAD_LIB(mysort_lib, "./libs/dynamic/libmysort.so", ERR_SORT_LIB);
    LOAD_LIB(io_lib, "./libs/dynamic/libfileio.so", ERR_IO_LIB);

    LOAD_FUNC(check_args, fn_check_main_parametrs_t, err_lib, "check_main_parametrs");
    LOAD_FUNC(check_file, fn_check_open_file_t, err_lib, "check_open_file");
    LOAD_FUNC(count, fn_count_num_t, io_lib, "count_num");
    LOAD_FUNC(create_arr, fn_create_array_t, io_lib, "create_array");
    LOAD_FUNC(key, fn_key_t, mysort_lib, "key");
    LOAD_FUNC(mysort, fn_mysort_t, mysort_lib, "mysort");
    LOAD_FUNC(compare_int, fn_compare_int_t, mysort_lib, "compare_int");
    LOAD_FUNC(write_to_file, fn_write_to_file_t, io_lib, "write_to_file");
    LOAD_FUNC(free_all, fn_close_and_free_t, err_lib, "close_and_free");
    LOAD_FUNC(err_print, fn_print_error_t, err_lib, "print_error");

    IS_OK
    exit_code = check_args(argc, argv);
    END_IS_OK

    IS_OK
    input_file = fopen(*(argv + 1), "r");
    exit_code = check_file(input_file, ERR_OPEN_INPUT_FILE);
    END_IS_OK

    IS_OK
    output_file = fopen(*(argv + 2), "w");
    exit_code = check_file(output_file, ERR_OPEN_OUTPUT_FILE);
    END_IS_OK

    IS_OK
    exit_code = count(input_file, &num);
    END_IS_OK

    IS_OK
    exit_code = create_arr(input_file, num, &array);
    END_IS_OK

    IS_OK
    if (argc == 4)
    {
        exit_code = key(array.arr, array.end, &filtered_array.arr, &filtered_array.end);

        IS_OK
        mysort(filtered_array.arr, filtered_array.end - filtered_array.arr,
               sizeof(int), compare_int);
        exit_code = write_to_file(output_file, &filtered_array);
        END_IS_OK
    }
    else
    {
        mysort(array.arr, array.end - array.arr, sizeof(int), compare_int);
        exit_code = write_to_file(output_file, &array);
    }
    END_IS_OK

    if (ERR_LIB != exit_code)    
    {
        free_all(input_file, output_file, &array, &filtered_array, argc, &exit_code);
        err_print(exit_code);
    }

    if (ERR_ERR_LIB != exit_code)
        dlclose(err_lib);

    if (ERR_SORT_LIB != exit_code)
        dlclose(mysort_lib);

    if (ERR_IO_LIB != exit_code)
        dlclose(io_lib);

    return exit_code;
}
