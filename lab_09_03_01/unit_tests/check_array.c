#include <check.h>
#include <stdlib.h>

#include "check_array.h"
#include "array.h"

START_TEST(test_get_null_arr)
{
    product_t *product; 
    int exit_code = get(NULL, 0, &product);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_get_null_element)
{
    array_t arr; 
    int exit_code = get(&arr, 0, NULL);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_get_negative_index)
{
    array_t arr; 
    product_t *product; 
    int exit_code = get(&arr, -1, &product);
    ck_assert_int_eq(exit_code, -1);
}
END_TEST

START_TEST(test_get_too_big_index)
{
    array_t arr = { .len = 5 }; 
    product_t *product; 
    int exit_code = get(&arr, 6, &product);
    ck_assert_int_eq(exit_code, -1);
}
END_TEST

START_TEST(test_get_ok)
{
    product_t product = { .name = "name", .price = 1 }; 
    array_t arr  = { .arr = &product, .len = 1, .capacity = 1 };
    product_t *result;
    int exit_code = get(&arr, 0, &result);
    ck_assert_int_eq(exit_code, 0);
    ck_assert_ptr_eq(result, &product);
}
END_TEST

START_TEST(test_set_null_arr)
{
    product_t product = { .name = "name", .price = 13 }; 
    int exit_code = set(NULL, 0, &product);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_set_null_element)
{
    array_t arr; 
    int exit_code = set(&arr, 0, NULL);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_set_negative_index)
{
    array_t arr; 
    product_t product; 
    int exit_code = set(&arr, -1, &product);
    ck_assert_int_eq(exit_code, -1);
}
END_TEST

START_TEST(test_set_too_big_index)
{
    array_t arr = { .len = 5 }; 
    product_t product; 
    int exit_code = set(&arr, 6, &product);
    ck_assert_int_eq(exit_code, -1);
}
END_TEST

START_TEST(test_set_ok)
{
    product_t product = { .name = "name", .price = 1 };
    product_t array[1];
    array_t arr  = { .arr = array, .len = 1, .capacity = 1 };
    int exit_code = set(&arr, 0, &product);
    ck_assert_int_eq(exit_code, 0);
    ck_assert_mem_eq(product.name, arr.arr[0].name, sizeof(char) * 4);
    ck_assert_int_eq(product.price, arr.arr[0].price);
}
END_TEST

START_TEST(test_append_null_arr)
{
    product_t product = { .name = "name", .price = 13 }; 
    int exit_code = append(NULL, &product);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_append_null_element)
{
    array_t arr; 
    int exit_code = append(&arr, NULL);
    ck_assert_int_eq(exit_code, -3);
}
END_TEST

START_TEST(test_append_not_null_arr_zero_capacity)
{
    product_t product; 
    array_t arr = { .arr = &product, .len = 0, .capacity = 0}; 
    int exit_code = append(&arr, &product);
    ck_assert_int_eq(exit_code, -7);
}
END_TEST

START_TEST(test_append_null_arr_nonzero_capacity)
{
    product_t product; 
    array_t arr = { .arr = NULL, .len = 0, .capacity = 4}; 
    int exit_code = append(&arr, &product);
    ck_assert_int_eq(exit_code, -7);
}
END_TEST

START_TEST(test_append_ok_empty_array)
{
    product_t product = { .name = "name", .price = 1 }; 
    array_t arr = { .arr = NULL, .len = 0, .capacity = 0 };
    int exit_code = append(&arr, &product);
    ck_assert_int_eq(exit_code, 0);
    ck_assert_mem_eq(product.name, arr.arr[0].name, sizeof(char) * 4);
    ck_assert_int_eq(product.price, arr.arr[0].price);
    ck_assert_int_eq(arr.len, 1);
    ck_assert_int_eq(arr.capacity, 1);
    free(arr.arr);
}
END_TEST

START_TEST(test_append_ok_not_empty_array)
{
    product_t product = { .name = "name", .price = 1 }; 
    product_t *array = malloc(sizeof(product_t));
    array[0] = product;
    array_t arr = { .arr = array, .len = 1, .capacity = 1 };
    int exit_code = append(&arr, &product);
    ck_assert_int_eq(exit_code, 0);
    ck_assert_mem_eq(product.name, arr.arr[0].name, sizeof(char) * 4);
    ck_assert_int_eq(product.price, arr.arr[0].price);
    ck_assert_mem_eq(product.name, arr.arr[1].name, sizeof(char) * 4);
    ck_assert_int_eq(product.price, arr.arr[1].price);
    ck_assert_int_eq(arr.len, 2);
    ck_assert_int_eq(arr.capacity, 2);
    free(arr.arr);
}
END_TEST

Suite* array_suite(void)
{
    Suite *suite;
    TCase *neg_tests;
    TCase *pos_tests;

    suite = suite_create("array");

    neg_tests = tcase_create("negatives");
    tcase_add_test(neg_tests, test_get_null_arr);
    tcase_add_test(neg_tests, test_get_null_element);
    tcase_add_test(neg_tests, test_get_negative_index);
    tcase_add_test(neg_tests, test_get_too_big_index);

    tcase_add_test(neg_tests, test_set_null_arr);
    tcase_add_test(neg_tests, test_set_null_element);
    tcase_add_test(neg_tests, test_set_negative_index);
    tcase_add_test(neg_tests, test_set_too_big_index);

    tcase_add_test(neg_tests, test_append_null_arr);
    tcase_add_test(neg_tests, test_append_null_element);
    tcase_add_test(neg_tests, test_append_not_null_arr_zero_capacity);
    tcase_add_test(neg_tests, test_append_null_arr_nonzero_capacity);

    pos_tests = tcase_create("positives");
    tcase_add_test(pos_tests, test_get_ok);
    tcase_add_test(pos_tests, test_set_ok);
    tcase_add_test(pos_tests, test_append_ok_empty_array);
    tcase_add_test(pos_tests, test_append_ok_not_empty_array);

    suite_add_tcase(suite, neg_tests);
    suite_add_tcase(suite, pos_tests);

    return suite;
}
