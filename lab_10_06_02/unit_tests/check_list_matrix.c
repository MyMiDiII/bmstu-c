#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "check_list_matrix.h"
#include "list_matrix.h"
#include "matrixes_init.h"
#include "errors.h"

int values1[4] = {1, 1, 0, 1};
int values2[4] = {2, 0, 2, 2};
int row[3] = {1, -1, 1};
int columns[6] = {0, 0, -1, -1, 0, 0};
int first[9] = {10, 0, 8, 0, 1, -10, -100, 0, 0};
int middle[9] = {0, 1, -10, 10, 0, 8, -100, 0, 0};
int last[9] = {0, 1, -10, -100, 0, 0, 10, 0, 8};
int full1[6] = {6, -8, 2, -1, 1, 7};
int full2[6] = {-3, 7, 1, 3, -8, -10};

int first_less1[4] = {1, 0, 1, 1};
int first_great1[4] = {2, 2, 2, 2};

int first_great2[4] = {1, 1, 1, 1};
int first_less2[4] = {2, 2, 0, 2};

int last_less1[4] = {2, 2, 0, 2};
int last_great1[4] = {1, 1, 1, 1};

int last_great2[4] = {2, 2, 2, 2};
int last_less2[4] = {1, 0, 1, 1};

int matr1[4] = {1, 0, 3, -2};
int matr2[9] = {1, 0, 1, 0, 0, 0, 0, 0, 5};

#define CHECK_ELEMENT(element, vrow, vcolumn, vvalue) \
{ \
    ck_assert_int_eq(element.row, vrow); \
    ck_assert_int_eq(element.column, vcolumn); \
    ck_assert_int_eq(element.value, vvalue); \
}

START_TEST(test_add_empty_matrixes)
{
    ck_assert_int_eq(OK, 0);
    list_matrix_t *matrix1 = NULL;
    list_matrix_t *matrix2 = NULL;
    list_matrix_t *result = NULL;
    add(matrix1, matrix2, &result);
    ck_assert_ptr_null(result);
    ck_assert_ptr_null(matrix1);
    ck_assert_ptr_null(matrix2);
}
END_TEST

START_TEST(test_add_empty_matrix1)
{
    list_matrix_t *matrix1 = NULL;
    element_t element = { .row = 1, .column = 2, .value = 3 };
    list_matrix_t data = { .data = element, .next = NULL };
    list_matrix_t *matrix2 = &data;
    list_matrix_t *result;
    add(matrix1, matrix2, &result);
    ck_assert_ptr_null(matrix1);
    ck_assert_ptr_eq(matrix2, &data);
    CHECK_ELEMENT(result->data, 1, 2, 3);
    ck_assert_ptr_null(result->next);
    free(result);
}
END_TEST

START_TEST(test_add_empty_matrix2)
{
    list_matrix_t *matrix2 = NULL;
    element_t element = { .row = 1, .column = 2, .value = 3 };
    list_matrix_t data = { .data = element, .next = NULL };
    list_matrix_t *matrix1 = &data;
    list_matrix_t *result;
    add(matrix1, matrix2, &result);
    ck_assert_ptr_null(matrix2);
    ck_assert_ptr_eq(matrix1, &data);
    CHECK_ELEMENT(result->data, 1, 2, 3);
    ck_assert_ptr_null(result->next);
    free(result);
}
END_TEST

START_TEST(test_add_general)
{
    list_matrix_t *matrix1 = create_matrix(values1, 2, 2);
    list_matrix_t *matrix2 = create_matrix(values2, 2, 2);
    list_matrix_t *result;
    add(matrix1, matrix2, &result);
    CHECK_ELEMENT(result->data, 0, 0, 3);
    CHECK_ELEMENT(result->next->data, 0, 1, 1);
    CHECK_ELEMENT(result->next->next->data, 1, 0, 2);
    CHECK_ELEMENT(result->next->next->next->data, 1, 1, 3);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
}
END_TEST

START_TEST(test_multiply_null_result)
{
    list_matrix_t *matrix1 = create_matrix(row, 1, 3);
    list_matrix_t *matrix2 = create_matrix(columns, 3, 2);
    int code = multiply(matrix1, matrix2, NULL);
    ck_assert_int_eq(code, ERR_NULL_POINTER);
    free_matrix(matrix1);
    free_matrix(matrix2);
}
END_TEST

START_TEST(test_multiply_null_first)
{
    list_matrix_t *matrix1 = NULL;
    list_matrix_t *matrix2 = create_matrix(columns, 3, 2);
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    ck_assert_ptr_null(result);
    free_matrix(matrix2);
}
END_TEST

START_TEST(test_multiply_null_second)
{
    list_matrix_t *matrix1 = create_matrix(columns, 3, 2);
    list_matrix_t *matrix2 = NULL;
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    ck_assert_ptr_null(result);
    free_matrix(matrix1);
}
END_TEST

START_TEST(test_multiply_row_and_column)
{
    list_matrix_t *matrix1 = create_matrix(row, 3, 2);
    element_t element = { .column = 5, .row = 1, .value = -100 };
    list_matrix_t matrix2 = { .data = element, .next = NULL };
    list_matrix_t *result;
    int code = multiply(matrix1, &matrix2, &result);
    ck_assert_int_eq(code, OK);
    CHECK_ELEMENT(result->data, 0, 5, 100);
    free_matrix(matrix1);
    free_matrix(result);
}
END_TEST

START_TEST(test_multiply_full_matrixes)
{
    list_matrix_t *matrix1 = create_matrix(full1, 2, 3);
    list_matrix_t *matrix2 = create_matrix(full2, 3, 2);
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    CHECK_ELEMENT(result->data, 0, 0, -42);
    CHECK_ELEMENT(result->next->data, 0, 1, -2);
    CHECK_ELEMENT(result->next->next->data, 1, 0, -52);
    CHECK_ELEMENT(result->next->next->next->data, 1, 1, -74);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
}
END_TEST

START_TEST(test_multiply_first_less)
{
    list_matrix_t *matrix1 = create_matrix(first_less1, 2, 2);
    list_matrix_t *matrix2 = create_matrix(first_great1, 2, 2);
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    CHECK_ELEMENT(result->data, 0, 0, 2);
    CHECK_ELEMENT(result->next->data, 0, 1, 2);
    CHECK_ELEMENT(result->next->next->data, 1, 0, 4);
    CHECK_ELEMENT(result->next->next->next->data, 1, 1, 4);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
}
END_TEST

START_TEST(test_multiply_first_great)
{
    list_matrix_t *matrix1 = create_matrix(first_great2, 2, 2);
    list_matrix_t *matrix2 = create_matrix(first_less2, 2, 2);
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    CHECK_ELEMENT(result->data, 0, 0, 2);
    CHECK_ELEMENT(result->next->data, 0, 1, 4);
    CHECK_ELEMENT(result->next->next->data, 1, 0, 2);
    CHECK_ELEMENT(result->next->next->next->data, 1, 1, 4);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
}
END_TEST

START_TEST(test_multiply_last_less)
{
    list_matrix_t *matrix1 = create_matrix(last_less1, 2, 2);
    list_matrix_t *matrix2 = create_matrix(last_great1, 2, 2);
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    CHECK_ELEMENT(result->data, 0, 0, 4);
    CHECK_ELEMENT(result->next->data, 0, 1, 4);
    CHECK_ELEMENT(result->next->next->data, 1, 0, 2);
    CHECK_ELEMENT(result->next->next->next->data, 1, 1, 2);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
}
END_TEST

START_TEST(test_multiply_last_great)
{
    list_matrix_t *matrix1 = create_matrix(last_great2, 2, 2);
    list_matrix_t *matrix2 = create_matrix(last_less2, 2, 2);
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    CHECK_ELEMENT(result->data, 0, 0, 4);
    CHECK_ELEMENT(result->next->data, 0, 1, 2);
    CHECK_ELEMENT(result->next->next->data, 1, 0, 4);
    CHECK_ELEMENT(result->next->next->next->data, 1, 1, 2);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
}
END_TEST

START_TEST(test_multiply_general)
{
    list_matrix_t *matrix1 = create_matrix(matr1, 2, 2);
    list_matrix_t *matrix2 = create_matrix(matr2, 3, 3);
    list_matrix_t *result;
    int code = multiply(matrix1, matrix2, &result);
    ck_assert_int_eq(code, OK);
    CHECK_ELEMENT(result->data, 0, 0, 1);
    CHECK_ELEMENT(result->next->data, 0, 2, 1);
    CHECK_ELEMENT(result->next->next->data, 1, 0, 3);
    CHECK_ELEMENT(result->next->next->next->data, 1, 2, 3);
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
}
END_TEST

START_TEST(test_delete_row_empty_matrix)
{
    list_matrix_t *matrix = NULL;
    int code = delete_row_with_max(&matrix);
    ck_assert_ptr_null(matrix);
    ck_assert_int_eq(ERR_EMPTY_MATRIX, code);
}
END_TEST

START_TEST(test_delete_row_one_row)
{
    list_matrix_t *matrix = create_matrix(row, 1, 3);
    int code = delete_row_with_max(&matrix);
    ck_assert_ptr_null(matrix);
    ck_assert_int_eq(ERR_EMPTY_MATRIX, code);
    free_matrix(matrix);
}
END_TEST

START_TEST(test_delete_row_first_row)
{
    list_matrix_t *matrix = create_matrix(first, 3, 3);
    int code = delete_row_with_max(&matrix);
    CHECK_ELEMENT(matrix->data, 0, 1, 1);
    CHECK_ELEMENT(matrix->next->data, 0, 2, -10);
    CHECK_ELEMENT(matrix->next->next->data, 1, 0, -100);
    ck_assert_int_eq(OK, code);
    free_matrix(matrix);
}
END_TEST

START_TEST(test_delete_row_middle_row)
{
    list_matrix_t *matrix = create_matrix(middle, 3, 3);
    int code = delete_row_with_max(&matrix);
    CHECK_ELEMENT(matrix->data, 0, 1, 1);
    CHECK_ELEMENT(matrix->next->data, 0, 2, -10);
    CHECK_ELEMENT(matrix->next->next->data, 1, 0, -100);
    ck_assert_int_eq(OK, code);
    free_matrix(matrix);
}
END_TEST

START_TEST(test_delete_row_last_row)
{
    list_matrix_t *matrix = create_matrix(last, 3, 3);
    int code = delete_row_with_max(&matrix);
    CHECK_ELEMENT(matrix->data, 0, 1, 1);
    CHECK_ELEMENT(matrix->next->data, 0, 2, -10);
    CHECK_ELEMENT(matrix->next->next->data, 1, 0, -100);
    ck_assert_int_eq(OK, code);
    free_matrix(matrix);
}
END_TEST

Suite* list_matrix_suite(void)
{
    Suite *suite;
    TCase *add_tests;
    TCase *multiply_tests;
    TCase *delete_row_tests;

    suite = suite_create("list_matrix");

    add_tests = tcase_create("add");
    tcase_add_test(add_tests, test_add_empty_matrixes);
    tcase_add_test(add_tests, test_add_empty_matrix1);
    tcase_add_test(add_tests, test_add_empty_matrix2);
    tcase_add_test(add_tests, test_add_general);

    multiply_tests = tcase_create("multiply");
    tcase_add_test(multiply_tests, test_multiply_null_result);
    tcase_add_test(multiply_tests, test_multiply_null_first);
    tcase_add_test(multiply_tests, test_multiply_null_second);
    tcase_add_test(multiply_tests, test_multiply_row_and_column);
    tcase_add_test(multiply_tests, test_multiply_full_matrixes);
    tcase_add_test(multiply_tests, test_multiply_first_less);
    tcase_add_test(multiply_tests, test_multiply_first_great);
    tcase_add_test(multiply_tests, test_multiply_last_less);
    tcase_add_test(multiply_tests, test_multiply_last_great);
    tcase_add_test(multiply_tests, test_multiply_general);

    delete_row_tests = tcase_create("delete_row");
    tcase_add_test(delete_row_tests, test_delete_row_empty_matrix);
    tcase_add_test(delete_row_tests, test_delete_row_one_row);
    tcase_add_test(delete_row_tests, test_delete_row_first_row);
    tcase_add_test(delete_row_tests, test_delete_row_last_row);
    tcase_add_test(delete_row_tests, test_delete_row_middle_row);

    suite_add_tcase(suite, add_tests);
    suite_add_tcase(suite, multiply_tests);
    suite_add_tcase(suite, delete_row_tests);

    return suite;
}
