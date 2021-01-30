#include <stdio.h>
#include <string.h>

#include "check_test.h"
#include "my_strspn.h"

#define PASSED 0
#define FAILED 1

int check_test(const char *str, const char *sym)
{
    if (my_strspn(str, sym) == strspn(str, sym))
    {
        return PASSED;
    }

    return FAILED;
}

int print_result(const char *str, const char *sym, const int number)
{
    int result = check_test(str, sym);
    if (result)
    {
        printf("Test №%d failed.\n", number);
    }
    else
    {
        printf("Test №%d passed.\n", number);
    }

    return result;
}

