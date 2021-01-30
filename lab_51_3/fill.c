#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "fill.h"

#define LEFT_BORDER -1000
#define RIGHT_BORDER 1000

void fill_random(FILE *file, const int num)
{
    srand(time(NULL));

    for (int i = 0; i < num; i++)
    {
        int number = LEFT_BORDER + rand() % (RIGHT_BORDER - LEFT_BORDER + 1);
        fwrite(&number, sizeof(int), 1, file);
    }
}