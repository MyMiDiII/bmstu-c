#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "my_snprintf.h"

#define STR_LEN 30
#define ONE_CHAR_STR_LEN 2

START_TEST(test_all_without_specifier)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    int std_num = snprintf(std, STR_LEN, "This is string :3");
    int my_num =  my_snprintf(my, STR_LEN, "This is string :3");
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(test_all_null_size)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    int std_num = snprintf(std, 0, "row");
    int my_num =  my_snprintf(my, 0, "row");
    ck_assert_int_eq(std_num, my_num);
    free(std);
    free(my);
}
END_TEST

START_TEST(test_all_null_size_and_ptr)
{
    char *std = NULL;
    char *my = NULL; 
    int std_num = snprintf(std, 0, "row");
    int my_num =  my_snprintf(my, 0, "row");
    ck_assert_int_eq(std_num, my_num);
}
END_TEST

START_TEST(tests_all_diff_spec)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    short int num = 2;
    int std_num = snprintf(std, STR_LEN, "%hd Christmas %s%c", num, "trees", '!');
    int my_num =  my_snprintf(my, STR_LEN, "%hd Christmas %s%c", num, "trees", '!');
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST


START_TEST(tests_char_one)
{
    char *std = malloc(sizeof(char) * ONE_CHAR_STR_LEN);
    char *my = malloc(sizeof(char) * ONE_CHAR_STR_LEN);
    int std_num = snprintf(std, ONE_CHAR_STR_LEN, "%c", 'r');
    int my_num =  my_snprintf(my, ONE_CHAR_STR_LEN, "%c", 'r');
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(test_char_simple)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    int std_num = snprintf(std, STR_LEN, "This is %c", 'r');
    int my_num =  my_snprintf(my, STR_LEN, "This is %c", 'r');
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(test_char_several)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    int std_num = snprintf(std, STR_LEN, "%c%c char = %c %%c %% c", 'i', 's', 'r');
    int my_num =  my_snprintf(my, STR_LEN, "%c%c char = %c %%c %% c", 'i', 's', 'r');
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_string_one)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    int std_num = snprintf(std, STR_LEN, "%s", "Happy New Year!");
    int my_num =  my_snprintf(my, STR_LEN, "%s", "Happy New Year!");
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_string_empty)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    int std_num = snprintf(std, STR_LEN, "%s", "");
    int my_num =  my_snprintf(my, STR_LEN, "%s", "");
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_string_null)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    char *string = NULL;
    int std_num = snprintf(std, STR_LEN, "Christmas %s%c", string, '!');
    int my_num =  my_snprintf(my, STR_LEN, "Christmas %s%c", string, '!');
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hd_pos)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    short int num = 2020;
    int std_num = snprintf(std, STR_LEN, "%hd year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%hd year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hd_neg)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    short int num = -2021;
    int std_num = snprintf(std, STR_LEN, "%hd year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%hd year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hd_zero)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    short int num = 0;
    int std_num = snprintf(std, STR_LEN, "%hd year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%hd year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hd_max)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    short int num = SHRT_MAX;
    int std_num = snprintf(std, STR_LEN, "%hd year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%hd year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hd_min)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    short int num = SHRT_MIN;
    int std_num = snprintf(std, STR_LEN, "%hd year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%hd year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_lo_pos)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    unsigned long int num = 2020;
    int std_num = snprintf(std, STR_LEN, "%lo year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%lo year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_lo_zero)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    unsigned long int num = 0;
    int std_num = snprintf(std, STR_LEN, "%lo year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%lo year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_lo_max)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    unsigned long int num = ULONG_MAX;
    int std_num = snprintf(std, STR_LEN, "%lo year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%lo year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hex_pos)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    unsigned int num = 2020;
    int std_num = snprintf(std, STR_LEN, "%x year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%x year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hex_zero)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    unsigned int num = 0;
    int std_num = snprintf(std, STR_LEN, "%x year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%x year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

START_TEST(tests_hex_max)
{
    char *std = malloc(sizeof(char) * STR_LEN);
    char *my = malloc(sizeof(char) * STR_LEN);
    unsigned int num = UINT_MAX;
    int std_num = snprintf(std, STR_LEN, "%x year!", num);
    int my_num =  my_snprintf(my, STR_LEN, "%x year!", num);
    ck_assert_int_eq(std_num, my_num);
    ck_assert_mem_eq(std, my, my_num + 1);
    free(std);
    free(my);
}
END_TEST

Suite* my_snprintf_suite(void)
{
    Suite *suite;
    TCase *all;
    TCase *char_specifier;
    TCase *string_specifier;
    TCase *hd_specifier;
    TCase *lo_specifier;
    TCase *hex_specifier;

    suite = suite_create("my_snprintf");

    all = tcase_create("all");
    tcase_add_test(all, test_all_without_specifier);
    tcase_add_test(all, test_all_null_size);
    tcase_add_test(all, test_all_null_size_and_ptr);
    tcase_add_test(all, tests_all_diff_spec);

    char_specifier = tcase_create("char");
    tcase_add_test(char_specifier, tests_char_one);
    tcase_add_test(char_specifier, test_char_simple);
    tcase_add_test(char_specifier, test_char_several);

    string_specifier = tcase_create("string");
    tcase_add_test(string_specifier, tests_string_one);
    tcase_add_test(string_specifier, tests_string_empty);
    tcase_add_test(string_specifier, tests_string_null);

    hd_specifier = tcase_create("hd");
    tcase_add_test(hd_specifier, tests_hd_pos);
    tcase_add_test(hd_specifier, tests_hd_neg);
    tcase_add_test(hd_specifier, tests_hd_zero);
    tcase_add_test(hd_specifier, tests_hd_max);
    tcase_add_test(hd_specifier, tests_hd_min);

    lo_specifier = tcase_create("lo");
    tcase_add_test(lo_specifier, tests_lo_pos);
    tcase_add_test(lo_specifier, tests_lo_zero);
    tcase_add_test(lo_specifier, tests_lo_max);

    hex_specifier = tcase_create("hex");
    tcase_add_test(hex_specifier, tests_hex_pos);
    tcase_add_test(hex_specifier, tests_hex_zero);
    tcase_add_test(hex_specifier, tests_hex_max);

    suite_add_tcase(suite, all);
    suite_add_tcase(suite, char_specifier);
    suite_add_tcase(suite, string_specifier);
    suite_add_tcase(suite, hd_specifier);
    suite_add_tcase(suite, lo_specifier);
    suite_add_tcase(suite, hex_specifier);

    return suite;
}
