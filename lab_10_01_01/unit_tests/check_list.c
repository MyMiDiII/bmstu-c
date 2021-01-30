#include <check.h>
#include <stdlib.h>

#include "check_list.h"
#include "list.h"
#include "comparators.h"

static int array[3] = { 0, 1, 2 };

START_TEST(test_pop_back_null_head_ptr)
{
    node_t **head = NULL;
    void *ptr = pop_back(head);
    ck_assert_ptr_null(ptr);
    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_pop_back_null_head)
{
    node_t *head = NULL;
    node_t **head_ptr = &head;
    void *ptr = pop_back(head_ptr);
    ck_assert_ptr_null(ptr);
    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_pop_back_one_element)
{    
    node_t *list_data = malloc(sizeof(node_t));
    list_data->data = array;
    list_data->next = NULL;
    int *data = pop_back(&list_data);
    ck_assert_ptr_null(list_data);
    ck_assert_int_eq(array[0], *data);
}
END_TEST

START_TEST(test_insert_null_head_ptr)
{
    node_t **head = NULL;
    node_t el;
    node_t *tmp = &el;
    node_t *ptr1 = &el;
    node_t *ptr2 = &el;
    insert(head, ptr1, ptr2);
    ck_assert_ptr_null(head);
    ck_assert_ptr_eq(ptr1, tmp);
    ck_assert_ptr_eq(ptr2, tmp);
}
END_TEST

START_TEST(test_insert_null_elem)
{
    node_t list_data = { .data = array, .next = NULL };
    node_t *head = &list_data;
    node_t *before = &list_data;
    node_t *elem = NULL;
    insert(&head, elem, before);
    ck_assert_ptr_eq(head, &list_data);
    ck_assert_ptr_eq(before, &list_data);
}
END_TEST

START_TEST(test_insert_null_head)
{
    node_t *head = NULL;
    node_t data1 = { .data = array, .next = NULL };
    node_t data2 = { .data = array + 1, .next = NULL };
    node_t *elem = &data1;
    node_t *before = &data2;
    insert(&head, elem, before);
    ck_assert_ptr_eq(elem, &data1);
    ck_assert_ptr_eq(before, &data2);
    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_insert_into_end)
{
    node_t elem = { .data = array + 2, .next = NULL };
    node_t last = { .data = array + 1, .next = NULL };
    node_t first = { .data = array, .next = &last };
    node_t *head = &first;
    insert(&head, &elem, NULL);
    ck_assert_int_eq(*((int *) head->next->next->data), array[2]);
    ck_assert_ptr_eq(head->next->next, &elem);
    ck_assert_ptr_eq(head->next->next->next, NULL);
}
END_TEST

START_TEST(test_insert_into_begin)
{
    node_t elem = { .data = array + 2, .next = NULL };
    node_t last = { .data = array + 1, .next = NULL };
    node_t first = { .data = array, .next = &last };
    node_t *head = &first;
    insert(&head, &elem, &first);
    ck_assert_ptr_eq(head, &elem);
    ck_assert_int_eq(*((int *) head->data), array[2]);
    ck_assert_ptr_eq(elem.next, &first);
}
END_TEST

START_TEST(test_insert_into_middle)
{
    node_t elem = { .data = array + 2, .next = NULL };
    node_t last = { .data = array + 1, .next = NULL };
    node_t first = { .data = array, .next = &last };
    node_t *head = &first;
    insert(&head, &elem, &last);
    ck_assert_int_eq(*((int *) head->next->data), array[2]);
    ck_assert_ptr_eq(head->next, &elem);
    ck_assert_ptr_eq(head->next->next, &last);
}
END_TEST

START_TEST(test_reverse_empty)
{
    node_t *head = NULL;
    node_t *reversed = reverse(head);
    ck_assert_ptr_null(reversed);
}
END_TEST

START_TEST(test_reverse_one_element)
{
    node_t list_data = { .data = array, .next = NULL };
    node_t *head = &list_data;
    node_t *reversed = reverse(head);
    ck_assert_ptr_eq(reversed, &list_data);
    ck_assert_ptr_null(reversed->next);
}
END_TEST

START_TEST(test_reverse_two_elements)
{
    node_t last = { .data = array + 1, .next = NULL };
    node_t first = { .data = array, .next = &last };
    node_t *head = &first;
    node_t *reversed = reverse(head);
    ck_assert_ptr_eq(reversed, &last);
    ck_assert_ptr_eq(reversed->next, &first);
    ck_assert_ptr_null(reversed->next->next);
}
END_TEST

START_TEST(test_reverse_three_elements)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array, .next = &second };
    node_t *head = &first;
    node_t *reversed = reverse(head);
    ck_assert_ptr_eq(reversed, &last);
    ck_assert_ptr_eq(reversed->next, &second);
    ck_assert_ptr_eq(reversed->next->next, &first);
    ck_assert_ptr_eq(reversed->next->next->next, NULL);
}
END_TEST

START_TEST(test_front_back_split_empty)
{
    node_t *head = NULL;
    node_t *back;
    front_back_split(head, &back);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(back);
}
END_TEST

START_TEST(test_front_back_split_empty_back)
{
    node_t list_data = { .data = array, .next = NULL };
    node_t *head = &list_data;
    node_t *back;
    front_back_split(head, &back);
    ck_assert_ptr_eq(head, &list_data);
    ck_assert_ptr_null(head->next);
    ck_assert_ptr_null(back);
}
END_TEST

START_TEST(test_front_back_split_even_num)
{
    node_t last = { .data = array + 1, .next = NULL };
    node_t first = { .data = array, .next = &last };
    node_t *head = &first;
    node_t *back;
    front_back_split(head, &back);
    ck_assert_ptr_eq(head, &first);
    ck_assert_ptr_null(head->next);
    ck_assert_ptr_eq(back, &last);
    ck_assert_ptr_null(back->next);
}
END_TEST

START_TEST(test_front_back_split_odd_num)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array, .next = &second };
    node_t *head = &first;
    node_t *back;
    front_back_split(head, &back);
    ck_assert_ptr_eq(head, &first);
    ck_assert_ptr_eq(head->next, &second);
    ck_assert_ptr_null(head->next->next);
    ck_assert_ptr_eq(back, &last);
    ck_assert_ptr_null(back->next);
}
END_TEST

START_TEST(test_sorted_merge_null_pointers)
{
    node_t *node = NULL;
    ck_assert_ptr_null(sorted_merge(NULL, &node, &compare_int));
    ck_assert_ptr_null(sorted_merge(&node, NULL, &compare_int));
    ck_assert_ptr_null(sorted_merge(&node, &node, NULL));
}
END_TEST

START_TEST(test_sorted_merge_two_empty)
{
    node_t *head_a = NULL;
    node_t *head_b = NULL;
    ck_assert_ptr_null(sorted_merge(&head_a, &head_b, &compare_int));
}
END_TEST

START_TEST(test_sorted_merge_empty_a)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array, .next = &second };
    node_t *head_b = &first;
    node_t *head_a = NULL;
    node_t *result = sorted_merge(&head_a, &head_b, &compare_int);
    ck_assert_ptr_eq(result, &first);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
}
END_TEST

START_TEST(test_sorted_merge_empty_b)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array, .next = &second };
    node_t *head_a = &first;
    node_t *head_b = NULL;
    node_t *result = sorted_merge(&head_a, &head_b, &compare_int);
    ck_assert_ptr_eq(result, &first);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
}
END_TEST

START_TEST(test_sorted_merge_greater_a)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array, .next = NULL };
    node_t *head_a = &second;
    node_t *head_b = &first;
    node_t *result = sorted_merge(&head_a, &head_b, &compare_int);
    ck_assert_ptr_eq(result, &first);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
}
END_TEST

START_TEST(test_sorted_merge_greater_b)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array, .next = NULL };
    node_t *head_b = &second;
    node_t *head_a = &first;
    node_t *result = sorted_merge(&head_a, &head_b, &compare_int);
    ck_assert_ptr_eq(result, &first);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
}
END_TEST

START_TEST(test_sorted_merge_general)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t first = { .data = array, .next = &last };
    node_t second = { .data = array + 1, .next = NULL };
    node_t *head_b = &second;
    node_t *head_a = &first;
    node_t *result = sorted_merge(&head_a, &head_b, &compare_int);
    ck_assert_ptr_eq(result, &first);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
}
END_TEST

START_TEST(test_sort_empty)
{
    node_t *head = NULL;
    node_t *result = sort(head, &compare_int);
    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_sort_one_element)
{
    node_t list_data = { .data = array, .next = NULL };
    node_t *head = &list_data;
    node_t *result = sort(head, &compare_int);
    ck_assert_ptr_eq(result, &list_data);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_ptr_null(result->next);
}
END_TEST

START_TEST(test_sort_sorted)
{
    node_t last = { .data = array + 2, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array, .next = &second };
    node_t *head = &first;
    node_t *result = sort(head, &compare_int);
    ck_assert_ptr_eq(result, &first);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
    ck_assert_ptr_null(result->next->next->next);
}
END_TEST

START_TEST(test_sorted_reversed)
{
    node_t last = { .data = array, .next = NULL };
    node_t second = { .data = array + 1, .next = &last };
    node_t first = { .data = array + 2, .next = &second };
    node_t *head = &first;
    node_t *result = sort(head, &compare_int);
    ck_assert_ptr_eq(result, &last);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
    ck_assert_ptr_null(result->next->next->next);
}
END_TEST

START_TEST(test_sorted_general)
{
    node_t last = { .data = array + 1, .next = NULL };
    node_t second = { .data = array, .next = &last };
    node_t first = { .data = array + 2, .next = &second };
    node_t *head = &first;
    node_t *result = sort(head, &compare_int);
    ck_assert_ptr_eq(result, &second);
    ck_assert_int_eq(0, *(int *)result->data);
    ck_assert_int_eq(1, *(int *)result->next->data);
    ck_assert_int_eq(2, *(int *)result->next->next->data);
    ck_assert_ptr_null(result->next->next->next);
}
END_TEST
Suite* list_suite(void)
{
    Suite *suite;
    TCase *pop_back_tests;
    TCase *insert_tests;
    TCase *reverse_tests;
    TCase *front_back_split_tests;
    TCase *sorted_merge_tests;
    TCase *sort_tests;

    suite = suite_create("list");

    pop_back_tests = tcase_create("pop_back");
    tcase_add_test(pop_back_tests, test_pop_back_null_head_ptr);
    tcase_add_test(pop_back_tests, test_pop_back_null_head);
    tcase_add_test(pop_back_tests, test_pop_back_one_element);

    insert_tests = tcase_create("insert");
    tcase_add_test(insert_tests, test_insert_null_head_ptr);
    tcase_add_test(insert_tests, test_insert_null_elem);
    tcase_add_test(insert_tests, test_insert_null_head);
    tcase_add_test(insert_tests, test_insert_into_end);
    tcase_add_test(insert_tests, test_insert_into_begin);
    tcase_add_test(insert_tests, test_insert_into_middle);

    reverse_tests = tcase_create("reverse");
    tcase_add_test(reverse_tests, test_reverse_empty);
    tcase_add_test(reverse_tests, test_reverse_one_element);
    tcase_add_test(reverse_tests, test_reverse_two_elements);
    tcase_add_test(reverse_tests, test_reverse_three_elements);

    front_back_split_tests = tcase_create("front_back_split");
    tcase_add_test(front_back_split_tests, test_front_back_split_empty);
    tcase_add_test(front_back_split_tests, test_front_back_split_empty_back);
    tcase_add_test(front_back_split_tests, test_front_back_split_even_num);
    tcase_add_test(front_back_split_tests, test_front_back_split_odd_num);

    sorted_merge_tests = tcase_create("sorted_merge");
    tcase_add_test(sorted_merge_tests, test_sorted_merge_null_pointers);
    tcase_add_test(sorted_merge_tests, test_sorted_merge_two_empty);
    tcase_add_test(sorted_merge_tests, test_sorted_merge_empty_a);
    tcase_add_test(sorted_merge_tests, test_sorted_merge_empty_b);
    tcase_add_test(sorted_merge_tests, test_sorted_merge_greater_a);
    tcase_add_test(sorted_merge_tests, test_sorted_merge_greater_b);
    tcase_add_test(sorted_merge_tests, test_sorted_merge_general);

    sort_tests = tcase_create("sort");
    tcase_add_test(sort_tests, test_sort_empty);
    tcase_add_test(sort_tests, test_sort_one_element);
    tcase_add_test(sort_tests, test_sort_sorted);
    tcase_add_test(sort_tests, test_sorted_reversed);
    tcase_add_test(sort_tests, test_sorted_general);

    suite_add_tcase(suite, pop_back_tests);
    suite_add_tcase(suite, insert_tests);
    suite_add_tcase(suite, reverse_tests);
    suite_add_tcase(suite, front_back_split_tests);
    suite_add_tcase(suite, sorted_merge_tests);
    suite_add_tcase(suite, sort_tests);

    return suite;
}
