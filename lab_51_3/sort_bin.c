#include <stdio.h>

#include "sort_bin.h"
#include "print_bin.h"
#include "errors.h"

int sort_bin_file(FILE *file)
{
    size_t size;
    int exit_code = OK;

    exit_code = file_size(file, &size);

    if (!exit_code)
    {
        size_t int_size = sizeof(int);
        for (size_t i = 0; i < size / int_size - 1; i++)
        {
            int min_pos = i * int_size;
            int min = get_number_by_pos(file, min_pos);
            int current = min;

            for (size_t j = i + 1; j < size / int_size; j++)
            {
                int current_pos = j * int_size;

                if (min > get_number_by_pos(file, current_pos))
                {
                    min_pos = current_pos;
                    min = get_number_by_pos(file, min_pos);
                }
            }

            put_number_by_pos(file, min_pos, current);
            put_number_by_pos(file, i * int_size, min);
        }
    }

    return exit_code;
}

int get_number_by_pos(FILE *file, const int pos)
{
    int num;

    fseek(file, pos, SEEK_SET);
    fread(&num, sizeof(int), 1, file);

    return num;
}

void put_number_by_pos(FILE *file, const int pos, const int num)
{
    fseek(file, pos, SEEK_SET);
    fwrite(&num, sizeof(int), 1, file);
}