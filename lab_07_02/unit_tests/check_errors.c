#include <check.h>

#include "check_errors.h"
#include "errors.h"

START_TEST(test_main_parametrs_wrong_argc)
{
    int argc = 1;
    char *parametrs = "app.exe";
    char **argv = &parametrs; 

    int exit_code = check_main_parametrs(argc, argv); 

    ck_assert_int_eq(exit_code, ERR_INVALID_MAIN_PARAMETERS);
}
END_TEST

START_TEST(test_main_parametrs_null_pointer)
{
    int argc = 4;
    char **argv = NULL; 

    int exit_code = check_main_parametrs(argc, argv); 

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_main_parametrs_wrong_filter)
{
    int argc = 4;
    char *parametrs[] = {"app.exe", "in.txt", "out.txt", "filter"};
    char **argv = (char **) &parametrs; 

    int exit_code = check_main_parametrs(argc, argv); 

    ck_assert_int_eq(exit_code, ERR_INVALID_MAIN_PARAMETERS);
}
END_TEST

START_TEST(test_main_parametrs_ok)
{
    int argc = 4;
    char *parametrs[] = {"app.exe", "in.txt", "out.txt", "f"};
    char **argv = (char **) &parametrs; 

    int exit_code = check_main_parametrs(argc, argv); 

    ck_assert_int_eq(exit_code, OK);
}
END_TEST

START_TEST(test_check_open_file_null_in)
{
    FILE *in = NULL;
    int mode = ERR_OPEN_INPUT_FILE;

    int exit_code = check_open_file(in, mode); 

    ck_assert_int_eq(exit_code, ERR_OPEN_INPUT_FILE);
}
END_TEST

START_TEST(test_check_open_file_null_out)
{
    FILE *out = NULL;
    int mode = ERR_OPEN_OUTPUT_FILE;

    int exit_code = check_open_file(out, mode); 

    ck_assert_int_eq(exit_code, ERR_OPEN_OUTPUT_FILE);
}
END_TEST

START_TEST(test_check_open_file_ok_in)
{
    int mode = ERR_OPEN_INPUT_FILE;
    FILE *in = fopen("unit_tests/in", "r");

    ck_assert_ptr_nonnull(in);

    int exit_code = check_open_file(in, mode); 

    ck_assert_int_eq(exit_code, OK);

    fclose(in);
}
END_TEST

START_TEST(test_check_open_file_ok_out)
{
    int mode = ERR_OPEN_INPUT_FILE;
    FILE *out = fopen("unit_tests/out", "r");

    ck_assert_ptr_nonnull(out);

    int exit_code = check_open_file(out, mode); 

    ck_assert_int_eq(exit_code, OK);

    fclose(out);
}
END_TEST

Suite* errors_suite(void)
{
    Suite *suite;
    TCase *neg_tests;
    TCase *pos_tests;

    suite = suite_create("errors");

    neg_tests = tcase_create("negatives");
    tcase_add_test(neg_tests, test_main_parametrs_wrong_argc);
    tcase_add_test(neg_tests, test_main_parametrs_null_pointer);
    tcase_add_test(neg_tests, test_main_parametrs_wrong_filter);
    tcase_add_test(neg_tests, test_check_open_file_null_in);
    tcase_add_test(neg_tests, test_check_open_file_null_out);

    pos_tests = tcase_create("positives");
    tcase_add_test(pos_tests, test_main_parametrs_ok);
    tcase_add_test(pos_tests, test_check_open_file_ok_in);
    tcase_add_test(pos_tests, test_check_open_file_ok_out);

    suite_add_tcase(suite, neg_tests);
    suite_add_tcase(suite, pos_tests);

    return suite;
}