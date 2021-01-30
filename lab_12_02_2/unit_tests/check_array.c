#include <check.h>
#include <stdlib.h>

#include "check_array.h"
#include "array.h"

START_TEST(test_create_fib_array_null)
{
    int *arr = NULL;
    int len = 5;
    create_fib_array(arr, len);
    ck_assert_ptr_null(arr);
    ck_assert_int_eq(len, 5);
}
END_TEST

START_TEST(test_create_fib_array_len_is_zero)
{
    int *arr = malloc(sizeof(int));
    int *tmp = arr;
    int len = 0;
    create_fib_array(arr, len);
    ck_assert_ptr_eq(arr, tmp);
    ck_assert_int_eq(len, 0);
    free(arr);
}
END_TEST

START_TEST(test_create_fib_array_len_is_48)
{
    int len = 48;
    int *arr = malloc(sizeof(int) * len);
    int *tmp = arr;
    create_fib_array(arr, len);
    ck_assert_ptr_eq(arr, tmp);
    free(arr);
}
END_TEST

START_TEST(test_create_fib_array_len_is_one)
{
    int tmp[1] = {0};
    int len = 1;
    int *arr = malloc(sizeof(int) * len);
    create_fib_array(arr, len);
    ck_assert_mem_eq(arr, tmp, len);
    free(arr);
}
END_TEST

START_TEST(test_create_fib_array_len_is_two)
{
    int tmp[2] = {0, 1};
    int len = 2;
    int *arr = malloc(sizeof(int) * len);
    create_fib_array(arr, len);
    ck_assert_mem_eq(arr, tmp, len);
    free(arr);
}
END_TEST

START_TEST(test_create_fib_array_len_is_five)
{
    int tmp[5] = {0, 1, 1, 2, 3};
    int len = 5;
    int *arr = malloc(sizeof(int) * len);
    create_fib_array(arr, len);
    ck_assert_mem_eq(arr, tmp, len);
    free(arr);
}
END_TEST

START_TEST(test_delete_repeated_arr_null)
{
    int len = 5;
    int *arr = NULL;
    int new_len = 5; 
    int new_arr[5] = {1, 2, 3, 4, 5};
    int num = delete_repeated(arr, len, new_arr, new_len);
    ck_assert_int_eq(num, 0);
}
END_TEST

START_TEST(test_delete_repeated_new_arr_null)
{
    int len = 5;
    int *new_arr = NULL;
    int new_len = 5; 
    int arr[5] = {1, 2, 3, 4, 5};
    int num = delete_repeated(arr, len, new_arr, new_len);
    ck_assert_int_eq(num, 0);
}
END_TEST

START_TEST(test_delete_repeated_zero_len)
{
    int len = -1;
    int new_arr[5];
    int new_len = 5; 
    int arr[5] = {1, 2, 3, 4, 5};
    int num = delete_repeated(arr, len, new_arr, new_len);
    ck_assert_int_eq(num, 0);
}
END_TEST

START_TEST(test_delete_repeated_neg_new_len)
{
    int len = 5;
    int arr[5] = {1, 2, 3, 4, 5};
    int new_len = -5; 
    int new_arr[5];
    int num = delete_repeated(arr, len, new_arr, new_len);
    ck_assert_int_eq(num, 0);
}
END_TEST

START_TEST(test_delete_repeated_zero_new_len)
{
    int len = 5;
    int arr[5] = {1, 2, 3, 4, 5};
    int new_len = 0; 
    int new_arr[5];
    int num = delete_repeated(arr, len, new_arr, new_len);
    ck_assert_int_eq(num, 5);
}
END_TEST

START_TEST(test_delete_repeated_need_new_len)
{
    int len = 5;
    int arr[5] = {1, 1, 0, 2, 0};
    int new_len = 3; 
    int new_arr[3];
    int tmp[3] = {1, 0, 2};
    int num = delete_repeated(arr, len, new_arr, new_len);
    ck_assert_int_eq(num, 3);
    ck_assert_mem_eq(new_arr, tmp, 3);
}
END_TEST

Suite* array_suite(void)
{
    Suite *suite;
    TCase *neg_tests;
    TCase *pos_tests;

    suite = suite_create("array");

    neg_tests = tcase_create("negatives");
    tcase_add_test(neg_tests, test_create_fib_array_null);
    tcase_add_test(neg_tests, test_create_fib_array_len_is_zero);
    tcase_add_test(neg_tests, test_create_fib_array_len_is_48);
    tcase_add_test(neg_tests, test_delete_repeated_arr_null);
    tcase_add_test(neg_tests, test_delete_repeated_new_arr_null);
    tcase_add_test(neg_tests, test_delete_repeated_zero_len);
    tcase_add_test(neg_tests, test_delete_repeated_neg_new_len);

    pos_tests = tcase_create("positives");
    tcase_add_test(pos_tests, test_create_fib_array_len_is_one);
    tcase_add_test(pos_tests, test_create_fib_array_len_is_two);
    tcase_add_test(pos_tests, test_create_fib_array_len_is_five);
    tcase_add_test(pos_tests, test_delete_repeated_zero_new_len);
    tcase_add_test(pos_tests, test_delete_repeated_need_new_len);

    suite_add_tcase(suite, neg_tests);
    suite_add_tcase(suite, pos_tests);

    return suite;
}
