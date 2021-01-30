#include <stdio.h>

#include "check_test.h"

#define OK 0
#define TESTS_NUMBER 6 
#define MAX_LEN 256

int main(void)
{
    setbuf(stdout, NULL);
    const char test_str[TESTS_NUMBER][MAX_LEN] =
        {
        "1simple example",
        "CHECK UPLETTERS",
        "mAtching ROWS!",
        "",
        "The second str is empty",
        "lack of symbols"
        };

    const char test_sym[TESTS_NUMBER][MAX_LEN] =
        {
        "im1ps",
        "cheCk upletters",
        "mAtcking ROWS!",
        "The first str is empty",
        "",
        "!,:?."
        };

    int num_passed = 0;
    for (int i = 0; i < TESTS_NUMBER; i++)
    {
        num_passed += print_result(test_str[i], test_sym[i], i + 1);
    }
    
    if (num_passed)
    {
        printf("\nTESTS FAILED!\n");
    }
    return OK;
}

