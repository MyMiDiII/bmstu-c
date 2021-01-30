#include <stdio.h>

#include "average.h"

#define OK 0
#define INVALID_NUM_MAIN_PARAMETRS -1
#define NO_FILE -2

int main(int argc, char **argv)
{
    FILE *input_file;
    double average;
    int num;
    int exit_code = OK;

    if (argc != 2)
    {
        fprintf(stderr, "Invalid number of main parametrs.\n");
        exit_code = INVALID_NUM_MAIN_PARAMETRS;
    }
    
    if (!exit_code)
    {
        input_file = fopen(argv[1], "r");
        
        if (!input_file)
        {
            fprintf(stderr, "There is no file.\n");
            exit_code = NO_FILE;
        }
    }

    if (!exit_code)
    {
        exit_code = find_min_max_average(input_file, &average);

        if (exit_code)
        {
            fprintf(stderr, "There is no numbers in file.\n");
        }
    }

    if (!exit_code)
    {
        rewind(input_file);
        count_greater_average(input_file, average, &num);

        printf("The number of numbers greater than average min and max: %d\n", num);
    }

    if (!exit_code || exit_code == NO_NUMBERS)
    {
        fclose(input_file);
    }

    return exit_code;
}
