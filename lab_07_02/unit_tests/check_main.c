#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "check_errors.h"
#include "check_fileio.h"
#include "check_mysort.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[36m"

int main(void)
{
    Suite *errors, *fileio, *mysort;
    SRunner *runner;

    errors = errors_suite();
    fileio = fileio_suite();
    mysort = mysort_suite();

    runner = srunner_create(errors);
    srunner_add_suite(runner, fileio);
    srunner_add_suite(runner, mysort);

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