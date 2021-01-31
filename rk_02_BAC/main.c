#include <stdio.h>

#include "read_file.h"
#include "write_file.h"

#define OK 0
#define WRONG_ARGUMENTS 1
#define NO_IN_FILE 2

#define MAX_LEN 256

int main(int argc, char **argv)
{
    FILE *in;
    FILE *out;
    char string[MAX_LEN + 1];
    int exit_code = OK;

    if (argc != 3)
    {
        exit_code = WRONG_ARGUMENTS;
    }

    if (!exit_code)
    {
        in = fopen(argv[1], "r");
        if (in == NULL)
        {
            exit_code = NO_IN_FILE;
        }
        else
        {
            out = fopen(argv[2], "w");

            read_file(in, string, MAX_LEN + 1);
            write_file(out, string);

            fclose(in);
            fclose(out);
        }
    }

    return exit_code;
}
