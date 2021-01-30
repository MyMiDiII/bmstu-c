#include <check.h>
#include <stdlib.h>

#include "check_fileio.h"
#include "fileio.h"
#include "errors.h"
#include "array.h"

START_TEST(test_count_num_null_file)
{
    FILE *file = NULL;
    size_t num;

    int exit_code = count_num(file, &num); 

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_count_num_null_num)
{
    FILE *file = fopen("func_tests/pos_01/pos_01_in.txt", "r");
    ck_assert_ptr_nonnull(file);

    size_t *num = NULL;

    int exit_code = count_num(file, num); 

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);

    fclose(file);
}
END_TEST

START_TEST(test_count_num_nonint_in_file)
{
    FILE *file = fopen("func_tests/neg_06/neg_06_in.txt", "r");
    ck_assert_ptr_nonnull(file);

    size_t num;

    int exit_code = count_num(file, &num); 

    ck_assert_int_eq(exit_code, ERR_READ_FILE);

    fclose(file);
}
END_TEST

START_TEST(test_count_num_empty_file)
{
    FILE *file = fopen("func_tests/neg_01/neg_01_in.txt", "r");
    ck_assert_ptr_nonnull(file);
    
    size_t num;

    int exit_code = count_num(file, &num); 

    ck_assert_int_eq(exit_code, ERR_EMPTY_FILE);
    fclose(file);
}
END_TEST

START_TEST(test_count_num_ok)
{
    FILE *file = fopen("func_tests/pos_01/pos_01_in.txt", "r");
    ck_assert_ptr_nonnull(file);
    size_t num;

    int exit_code = count_num(file, &num); 

    ck_assert_int_eq(exit_code, OK);
    ck_assert_uint_eq(num, 5);

    fclose(file);
}
END_TEST

START_TEST(test_create_array_null_file)
{
    FILE *file = NULL;
    size_t num = 2;
    array_t array;

    int exit_code = create_array(file, num, &array); 

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_create_array_null_num)
{
    FILE *file = fopen("func_tests/pos_01/pos_01_in.txt", "r");
    ck_assert_ptr_nonnull(file);

    size_t num = 0;
    array_t array;

    int exit_code = create_array(file, num, &array); 

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);

    fclose(file);
}
END_TEST

START_TEST(test_create_array_null_array)
{
    FILE *file = fopen("func_tests/pos_01/pos_01_in.txt", "r");
    ck_assert_ptr_nonnull(file);

    size_t num = 0;
    array_t *array = NULL;

    int exit_code = create_array(file, num, array); 

    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);

    fclose(file);
}
END_TEST

START_TEST(test_create_array_nonint_in_file)
{
    FILE *file = fopen("func_tests/neg_06/neg_06_in.txt", "r");
    ck_assert_ptr_nonnull(file);

    size_t num = 5;
    array_t array;

    int exit_code = create_array(file, num, &array); 

    ck_assert_int_eq(exit_code, ERR_READ_FILE);

    fclose(file);
}
END_TEST

START_TEST(test_create_array_wrong_num)
{
    FILE *file = fopen("func_tests/neg_01/neg_01_in.txt", "r");
    ck_assert_ptr_nonnull(file);
    
    size_t num = 1;
    array_t array;

    int exit_code = create_array(file, num, &array); 

    ck_assert_int_eq(exit_code, ERR_READ_FILE);
    fclose(file);
}
END_TEST

START_TEST(test_create_array_ok)
{
    FILE *file = fopen("func_tests/pos_01/pos_01_in.txt", "r");
    ck_assert_ptr_nonnull(file);
    int right[] = {5, 3, 2, 4, 1};
    array_t array, right_arr = { .arr = right, .end = right + 5};

    int exit_code = create_array(file, 5, &array); 

    ck_assert_int_eq(exit_code, OK);
    ck_assert_mem_eq(array.arr, right_arr.arr, sizeof(int) *
                     (array.end - array.arr));

    free(array.arr);
    fclose(file);
}
END_TEST

Suite* fileio_suite(void)
{
    Suite *suite;
    TCase *neg_tests;
    TCase *pos_tests;

    suite = suite_create("fileio");

    neg_tests = tcase_create("negatives");
    tcase_add_test(neg_tests, test_count_num_null_file);
    tcase_add_test(neg_tests, test_count_num_null_num);
    tcase_add_test(neg_tests, test_count_num_nonint_in_file);
    tcase_add_test(neg_tests, test_count_num_empty_file);

    tcase_add_test(neg_tests, test_create_array_null_file);
    tcase_add_test(neg_tests, test_create_array_null_num);
    tcase_add_test(neg_tests, test_create_array_null_array);
    tcase_add_test(neg_tests, test_create_array_nonint_in_file);
    tcase_add_test(neg_tests, test_create_array_wrong_num);

    pos_tests = tcase_create("positives");
    tcase_add_test(pos_tests, test_count_num_ok);
    tcase_add_test(pos_tests, test_create_array_ok);

    suite_add_tcase(suite, neg_tests);
    suite_add_tcase(suite, pos_tests);

    return suite;
}
