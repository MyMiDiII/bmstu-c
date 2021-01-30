#include <check.h>
#include <stdlib.h>

#include "check_products.h"
#include "products.h"

#define STR_LEN 5

START_TEST(test_read_name_null_name)
{
    char str[6] = "name\n";
    int exit_code = read_name(NULL, (FILE *) str);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_read_name_null_file)
{
    char *name;
    int exit_code = read_name(&name, NULL);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_read_name_ok_empty_string)
{
    FILE *file = fopen("unit_tests/empty", "r");
    ck_assert_ptr_nonnull(file);
    char tmp[1] = "";
    char *name;
    int exit_code = read_name(&name, file);
    ck_assert_int_eq(exit_code, 0);
    ck_assert_mem_eq(name, tmp, sizeof(char));
    fclose(file);
    free(name);
}
END_TEST

START_TEST(test_read_name_ok)
{
    FILE *file = fopen("unit_tests/string", "r");
    ck_assert_ptr_nonnull(file);
    char tmp[STR_LEN] = "name";
    char *name;
    int exit_code = read_name(&name, file);
    ck_assert_int_eq(exit_code, 0);
    ck_assert_mem_eq(name, tmp, sizeof(char) * STR_LEN);
    fclose(file);
    free(name);
}
END_TEST

Suite* products_suite(void)
{
    Suite *suite;
    TCase *neg_tests;
    TCase *pos_tests;

    suite = suite_create("products");

    neg_tests = tcase_create("negatives");
    tcase_add_test(neg_tests, test_read_name_null_name);
    tcase_add_test(neg_tests, test_read_name_null_file);

    pos_tests = tcase_create("positives");
    tcase_add_test(pos_tests, test_read_name_ok_empty_string);
    tcase_add_test(pos_tests, test_read_name_ok);

    suite_add_tcase(suite, neg_tests);
    suite_add_tcase(suite, pos_tests);

    return suite;
}
