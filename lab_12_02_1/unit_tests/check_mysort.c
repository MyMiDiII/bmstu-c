#include <check.h>
#include <stdlib.h>

#include "check_mysort.h"
#include "mysort.h"
#include "errors.h"

START_TEST(test_compare_int_greater)
{
    int num_1 = 2;
    void *first = (void *) &num_1;
    int num_2 = 1;
    void *second = (void *) &num_2;

    int result = compare_int(first, second);

    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_compare_int_equal)
{
    int num_1 = 1;
    void *first = (void *) &num_1;
    int num_2 = 1;
    void *second = (void *) &num_2;

    int result = compare_int(first, second);

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_compare_int_less)
{
    int num_1 = 1;
    void *first = (void *) &num_1;
    int num_2 = 2;
    void *second = (void *) &num_2;

    int result = compare_int(first, second);

    ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_mysort_first_null)
{
    mysort(NULL, 1, sizeof(int), &compare_int);
}
END_TEST

START_TEST(test_mysort_number_zero)
{
    int arr[] = {5, 3, 2, 1, 4};
    size_t size = sizeof(int);

    mysort(arr, 0, size, &compare_int);
}
END_TEST

START_TEST(test_mysort_size_zero)
{
    int arr[] = {5, 3, 2, 1, 4};

    mysort(arr, 5, 0, &compare_int);
}
END_TEST

START_TEST(test_mysort_ok)
{
    int arr[] = {85, -100, 0, -67, 0, 0};
    int sorted_arr[] = {-100, -67, 0, 0, 0, 85};
    size_t number = 6;

    mysort(arr, number, sizeof(int), &compare_int);

    ck_assert_mem_eq(arr, sorted_arr, sizeof(int) * number);
}
END_TEST

START_TEST(test_key_begin_null)
{
    int *pb_src = NULL;
    int num;
    int *pe_src = &num;
    
    int exit_code = key(pb_src, pe_src, &pe_src, &pb_src);

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_key_end_null)
{
    int *pe_src = NULL;
    int num;
    int *pb_src = &num;
    
    int exit_code = key(pb_src, pe_src, &pe_src, &pb_src);

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_key_new_begin_null)
{
    int num;
    int *pb_src = &num;
    int *pe_src = pb_src + 1;
    
    int exit_code = key(pb_src, pe_src, NULL, &pb_src);

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_key_new_end_null)
{
    int num;
    int *pb_src = &num;
    int *pe_src = pb_src + 1;
    
    int exit_code = key(pb_src, pe_src, &pb_src, NULL);

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_key_begin_greater_end)
{
    int num;
    int *pb_src = &num;
    int *pe_src = pb_src - 1;
    
    int exit_code = key(pb_src, pe_src, &pb_src, &pe_src);

    ck_assert_int_eq(exit_code, ERR_WRONG_POINTERS);
}
END_TEST

START_TEST(test_key_begin_equal_end)
{
    int num;
    int *pe_src = &num;
    
    int exit_code = key(pe_src, pe_src, &pe_src, &pe_src);

    ck_assert_int_eq(exit_code, ERR_WRONG_POINTERS);
}
END_TEST

START_TEST(test_key_empty_new_array)
{
    int arr[] = {-1, 0};
    int *new_arr;
    int *new_arr_end;
    
    int exit_code = key(arr, arr + 2, &new_arr, &new_arr_end);

    ck_assert_int_eq(exit_code, ERR_EMPTY_FILTER);
}
END_TEST

START_TEST(test_key_average_negative)
{
    int arr[] = {0, -1, 8};
    int *new_arr;
    int *new_arr_end;
    int key_arr[] = {0};
    
    int exit_code = key(arr, arr + 3, &new_arr, &new_arr_end);

    ck_assert_int_eq(exit_code, OK);
    ck_assert_mem_eq(key_arr, new_arr, sizeof(int) * (new_arr_end - new_arr));

    free(new_arr);
}
END_TEST

START_TEST(test_key_last_negative)
{
    int arr[] = {0, 1, -8};
    int *new_arr;
    int *new_arr_end;
    int key_arr[] = {0, 1};
    
    int exit_code = key(arr, arr + 3, &new_arr, &new_arr_end);

    ck_assert_int_eq(exit_code, OK);
    ck_assert_mem_eq(key_arr, new_arr, sizeof(int) * (new_arr_end - new_arr));

    free(new_arr);
}
END_TEST

START_TEST(test_key_no_negative)
{
    int arr[] = {0, 1, 8};
    int *new_arr;
    int *new_arr_end;
    int key_arr[] = {0, 1, 8};
    
    int exit_code = key(arr, arr + 3, &new_arr, &new_arr_end);

    ck_assert_int_eq(exit_code, OK);
    ck_assert_mem_eq(key_arr, new_arr, sizeof(int) * (new_arr_end - new_arr));

    free(new_arr);
}
END_TEST

Suite* mysort_suite(void)
{
    Suite *suite;
    TCase *neg_tests;
    TCase *pos_tests;

    suite = suite_create("mysort");

    neg_tests = tcase_create("negatives");
    tcase_add_test(neg_tests, test_mysort_first_null);
    tcase_add_test(neg_tests, test_mysort_number_zero);
    tcase_add_test(neg_tests, test_mysort_size_zero);

    tcase_add_test(neg_tests, test_key_begin_null);
    tcase_add_test(neg_tests, test_key_end_null);
    tcase_add_test(neg_tests, test_key_new_begin_null);
    tcase_add_test(neg_tests, test_key_new_end_null);
    tcase_add_test(neg_tests, test_key_begin_greater_end);
    tcase_add_test(neg_tests, test_key_begin_equal_end);
    tcase_add_test(neg_tests, test_key_empty_new_array);

    pos_tests = tcase_create("positives");
    tcase_add_test(pos_tests, test_compare_int_greater);
    tcase_add_test(pos_tests, test_compare_int_equal);
    tcase_add_test(pos_tests, test_compare_int_less);

    tcase_add_test(pos_tests, test_mysort_ok);
    tcase_add_test(pos_tests, test_key_average_negative);
    tcase_add_test(pos_tests, test_key_last_negative);
    tcase_add_test(pos_tests, test_key_no_negative);

    suite_add_tcase(suite, neg_tests);
    suite_add_tcase(suite, pos_tests);

    return suite;
}
