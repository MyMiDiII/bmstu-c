#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "array.h"

#include "check_array.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[36m"

int main(void)
{
    Suite *array;
    SRunner *runner;

    array = array_suite();

    runner = srunner_create(array);

    srunner_run_all(runner, CK_VERBOSE);

    int all = srunner_ntests_run(runner);
    int failed = srunner_ntests_failed(runner);
    int passed = all - failed;
    printf("\n%sTOTAL:%s  %d\n", BLUE, RESET, all);
    printf("%sPASSED:%s %d\n", GREEN, RESET, passed);
    printf("%sFAILED:%s %d\n", RED, RESET, failed);

    srunner_free(runner);

    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
