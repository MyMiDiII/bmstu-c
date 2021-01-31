#include <stdio.h>

#include "write_file.h"

void write_file(FILE *f, char *const string)
{
    int i = 0;

    while (string[i] != '\0')
    {
        fprintf(f, "%c", string[i]);
        i++;
    }
}
