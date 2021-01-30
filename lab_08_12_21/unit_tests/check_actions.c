#include <check.h>
#include <stdlib.h>
#include <math.h>

#include "check_actions.h"
#include "actions.h"
#include "errors.h"

#define EPS 1e-7

#define ADD_MATRIXES_INIT \
    double matr1[2][1] = { {1}, {2} }, \
           matr2[2][1] = { {1}, {2} }, \
           res[2][1] = { {2}, {4} }; \
    double *data1[2] = { matr1[0], matr1[1] }, \
           *data2[2] = { matr2[0], matr2[1] }, \
           *res_data[2] = { res[0], res[1] }; \
    matrix_t matrix1 = { .rows = 1, .columns = 2, .data = data1}; \
    matrix_t matrix2 = { .rows = 1, .columns = 2, .data = data2}; \
    matrix_t result, tmp_result = { .rows = 1, .columns = 2, .data = res_data};

#define MULTIPLY_MATRIXES_INIT \
    double matr1[2][1] = { {1}, {2} }, \
           matr2[1][2] = { {1, 2} }, \
           res[1][1] = { {5} }; \
    double *data1[2] = { matr1[0], matr1[1] }, \
           *data2[1] = { matr2[0] }, \
           *res_data[1] = { res[0] }; \
    matrix_t matrix1 = { .rows = 1, .columns = 2, .data = data1}; \
    matrix_t matrix2 = { .rows = 2, .columns = 1, .data = data2}; \
    matrix_t result, tmp_result = { .rows = 1, .columns = 1, .data = res_data};

#define CMP_MATRIX(rows, columns, matr1, matr2) \
    for (size_t i = 0; i < rows; i++) \
        for (size_t j = 0; j < columns; j++) \
            ck_assert(fabs(matr1[i][j] - matr2[i][j]) < EPS);

START_TEST(test_det_zero_rows)
{
    matrix_t matrix = { .rows = 0, .columns = 1 };
    double determinant;
    int exit_code = find_determinant(&matrix, &determinant);
    ck_assert_int_eq(exit_code, ERR_ZERO_DEMENSIONS);
}
END_TEST

START_TEST(test_det_zero_columns)
{
    matrix_t matrix = { .rows = 1, .columns = 0 };
    double determinant;
    int exit_code = find_determinant(&matrix, &determinant);
    ck_assert_int_eq(exit_code, ERR_ZERO_DEMENSIONS);
}
END_TEST

START_TEST(test_det_nonsquare)
{
    double matr[1][2] = { { 3, 4 } };
    double *matr_data[1] = { matr[0] };
    matrix_t matrix = { .rows = 1, .columns = 2, .data = matr_data};
    double determinant;
    int exit_code = find_determinant(&matrix, &determinant);
    ck_assert_int_eq(exit_code, ERR_NONSQUARE);
}
END_TEST

START_TEST(test_det_1x1)
{
    double matr[1][1] = { { 3.1 } };
    double *matr_data[1] = { matr[0] };
    matrix_t matrix = { .rows = 1, .columns = 1, .data = matr_data};
    double determinant, tmp_det = 3.100000;
    int exit_code = find_determinant(&matrix, &determinant);
    ck_assert_int_eq(exit_code, OK);
    ck_assert(fabs(determinant - tmp_det) < EPS);
}
END_TEST

START_TEST(test_det_2x2)
{
    double matr[2][2] = { { 0.05, 0.1 }, { -0.1, 0.05 } };
    double *matr_data[2] = { matr[0], matr[1] };
    matrix_t matrix = { .rows = 2, .columns = 2, .data = matr_data};
    double determinant, tmp_det = 0.012500;
    int exit_code = find_determinant(&matrix, &determinant);
    ck_assert_int_eq(exit_code, OK);
    ck_assert(fabs(determinant - tmp_det) < EPS);
}
END_TEST

START_TEST(test_det_3x3)
{
    double matr[3][3] = { { 1, -2, 3 }, { 0, 7, 4 }, { 5, 3, -3 } };
    double *matr_data[3] = { matr[0], matr[1], matr[2] };
    matrix_t matrix = { .rows = 3, .columns = 3, .data = matr_data};
    double determinant, tmp_det = -178.000000;
    int exit_code = find_determinant(&matrix, &determinant);
    ck_assert_int_eq(exit_code, OK);
    ck_assert(fabs(determinant - tmp_det) < EPS);
}
END_TEST

START_TEST(test_add_first_null)
{
    matrix_t matrix2, result;
    int exit_code = add_matrixes(NULL, &matrix2, &result);
    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_add_second_null)
{
    matrix_t matrix1, result;
    int exit_code = add_matrixes(&matrix1, NULL, &result);
    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_add_third_null)
{
    matrix_t matrix1, matrix2;
    int exit_code = add_matrixes(&matrix1, &matrix2, NULL);
    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_add_incorrect_sizes)
{
    double matr1[1][2] = { { 1, 2 } }, matr2[2][1] = { {1}, {2} };
    double *data1[1] = { matr1[0] };
    double *data2[2] = { matr2[0], matr2[1] };
    matrix_t matrix1 = { .rows = 1, .columns = 2, .data = data1};
    matrix_t matrix2 = { .rows = 2, .columns = 1, .data = data2};
    matrix_t result;
    int exit_code = add_matrixes(&matrix1, &matrix2, &result);
    ck_assert_int_eq(exit_code, ERR_WRONG_MATRIX_SIZES);
}
END_TEST

START_TEST(test_add_ok)
{
    ADD_MATRIXES_INIT;
    int exit_code = add_matrixes(&matrix1, &matrix2, &result);
    ck_assert_int_eq(exit_code, OK);
    ck_assert_int_eq(result.rows, tmp_result.rows);
    ck_assert_int_eq(result.columns, tmp_result.columns);
    CMP_MATRIX(result.rows, result.columns, result.data, tmp_result.data);
    free_data(result.data);
}
END_TEST

START_TEST(test_multiply_first_null)
{
    matrix_t matrix2, result;
    int exit_code = multiply_matrixes(NULL, &matrix2, &result);
    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_multiply_second_null)
{
    matrix_t matrix1, result;
    int exit_code = multiply_matrixes(&matrix1, NULL, &result);
    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_multiply_third_null)
{
    matrix_t matrix1, matrix2;
    int exit_code = multiply_matrixes(&matrix1, &matrix2, NULL);
    ck_assert_int_eq(exit_code, ERR_NULL_POINTER);
}
END_TEST

START_TEST(test_multiply_incorrect_sizes)
{
    double matr1[2][1] = { {1}, {2} }, matr2[2][1] = { {1}, {2} };
    double *data1[2] = { matr1[0], matr1[1] };
    double *data2[2] = { matr2[0], matr2[1] };
    matrix_t matrix1 = { .rows = 1, .columns = 2, .data = data1};
    matrix_t matrix2 = { .rows = 1, .columns = 2, .data = data2};
    matrix_t result;
    int exit_code = multiply_matrixes(&matrix1, &matrix2, &result);
    ck_assert_int_eq(exit_code, ERR_WRONG_MATRIX_SIZES);
}
END_TEST

START_TEST(test_multiply_ok)
{
    MULTIPLY_MATRIXES_INIT;
    int exit_code = multiply_matrixes(&matrix1, &matrix2, &result);
    ck_assert_int_eq(exit_code, OK);
    ck_assert_int_eq(result.rows, tmp_result.rows);
    ck_assert_int_eq(result.columns, tmp_result.columns);
    CMP_MATRIX(result.rows, result.columns, result.data, tmp_result.data);
    free_data(result.data);
}
END_TEST

Suite* actions_suite(void)
{
    Suite *suite;
    TCase *neg_tests;
    TCase *pos_tests;

    suite = suite_create("actions");

    neg_tests = tcase_create("negatives");
    tcase_add_test(neg_tests, test_det_zero_rows);
    tcase_add_test(neg_tests, test_det_zero_columns);
    tcase_add_test(neg_tests, test_det_nonsquare);

    tcase_add_test(neg_tests, test_add_first_null);
    tcase_add_test(neg_tests, test_add_second_null);
    tcase_add_test(neg_tests, test_add_third_null);
    tcase_add_test(neg_tests, test_add_incorrect_sizes);

    tcase_add_test(neg_tests, test_multiply_first_null);
    tcase_add_test(neg_tests, test_multiply_second_null);
    tcase_add_test(neg_tests, test_multiply_third_null);
    tcase_add_test(neg_tests, test_multiply_incorrect_sizes);

    pos_tests = tcase_create("positives");
    tcase_add_test(pos_tests, test_det_1x1);
    tcase_add_test(pos_tests, test_det_2x2);
    tcase_add_test(pos_tests, test_det_3x3);
    tcase_add_test(pos_tests, test_add_ok);
    tcase_add_test(pos_tests, test_multiply_ok);

    suite_add_tcase(suite, neg_tests);
    suite_add_tcase(suite, pos_tests);

    return suite;
}