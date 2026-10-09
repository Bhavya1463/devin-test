#include <stdio.h>
#include "linked_list.h"

/* ------------------------------------------------------------------ */
/*  Minimal test harness                                              */
/* ------------------------------------------------------------------ */

static int tests_run    = 0;
static int tests_passed = 0;

#define TEST(name) static void name(void)
#define RUN(name)  do {                                 \
        tests_run++;                                    \
        printf("  %-50s ", #name);                      \
        name();                                         \
        tests_passed++;                                 \
        printf("[PASS]\n");                             \
    } while (0)

#define ASSERT(cond) do {                               \
        if (!(cond)) {                                  \
            printf("[FAIL]  %s:%d: %s\n",               \
                   __FILE__, __LINE__, #cond);          \
            return;                                     \
        }                                               \
    } while (0)

/* ------------------------------------------------------------------ */
/*  Tests: create / length                                            */
/* ------------------------------------------------------------------ */

TEST(test_create_empty_list)
{
    ListNode *list = list_create();
    ASSERT(list == NULL);
    ASSERT(list_length(list) == 0);
}

/* ------------------------------------------------------------------ */
/*  Tests: insert head                                                */
/* ------------------------------------------------------------------ */

TEST(test_insert_head_single_element)
{
    ListNode *list = list_create();
    list = list_insert_head(list, 42);
    ASSERT(list != NULL);
    ASSERT(list->value == 42);
    ASSERT(list_length(list) == 1);
    list_destroy(list);
}

TEST(test_insert_head_multiple_elements)
{
    ListNode *list = list_create();
    list = list_insert_head(list, 3);
    list = list_insert_head(list, 2);
    list = list_insert_head(list, 1);
    ASSERT(list_length(list) == 3);
    ASSERT(list->value == 1);
    ASSERT(list->next->value == 2);
    ASSERT(list->next->next->value == 3);
    list_destroy(list);
}

/* ------------------------------------------------------------------ */
/*  Tests: insert tail                                                */
/* ------------------------------------------------------------------ */

TEST(test_insert_tail_empty_list)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 10);
    ASSERT(list != NULL);
    ASSERT(list->value == 10);
    ASSERT(list_length(list) == 1);
    list_destroy(list);
}

TEST(test_insert_tail_multiple_elements)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 1);
    list = list_insert_tail(list, 2);
    list = list_insert_tail(list, 3);
    ASSERT(list_length(list) == 3);
    ASSERT(list->value == 1);
    ASSERT(list->next->value == 2);
    ASSERT(list->next->next->value == 3);
    list_destroy(list);
}

/* ------------------------------------------------------------------ */
/*  Tests: delete by value                                            */
/* ------------------------------------------------------------------ */

TEST(test_delete_from_empty_list)
{
    ListNode *list = list_create();
    list = list_delete_value(list, 5);
    ASSERT(list == NULL);
    ASSERT(list_length(list) == 0);
}

TEST(test_delete_head_element)
{
    ListNode *list = list_create();
    list = list_insert_head(list, 1);
    list = list_insert_head(list, 2);
    list = list_insert_head(list, 3);
    list = list_delete_value(list, 3);
    ASSERT(list_length(list) == 2);
    ASSERT(list->value == 2);
    ASSERT(list->next->value == 1);
    list_destroy(list);
}

TEST(test_delete_tail_element)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 1);
    list = list_insert_tail(list, 2);
    list = list_insert_tail(list, 3);
    list = list_delete_value(list, 3);
    ASSERT(list_length(list) == 2);
    ASSERT(list->value == 1);
    ASSERT(list->next->value == 2);
    ASSERT(list->next->next == NULL);
    list_destroy(list);
}

TEST(test_delete_middle_element)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 1);
    list = list_insert_tail(list, 2);
    list = list_insert_tail(list, 3);
    list = list_delete_value(list, 2);
    ASSERT(list_length(list) == 2);
    ASSERT(list->value == 1);
    ASSERT(list->next->value == 3);
    ASSERT(list->next->next == NULL);
    list_destroy(list);
}

TEST(test_delete_single_element)
{
    ListNode *list = list_create();
    list = list_insert_head(list, 99);
    list = list_delete_value(list, 99);
    ASSERT(list == NULL);
    ASSERT(list_length(list) == 0);
}

TEST(test_delete_not_found)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 1);
    list = list_insert_tail(list, 2);
    list = list_delete_value(list, 99);
    ASSERT(list_length(list) == 2);
    ASSERT(list->value == 1);
    ASSERT(list->next->value == 2);
    list_destroy(list);
}

TEST(test_delete_first_duplicate_only)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 7);
    list = list_insert_tail(list, 7);
    list = list_insert_tail(list, 7);
    list = list_delete_value(list, 7);
    ASSERT(list_length(list) == 2);
    ASSERT(list->value == 7);
    ASSERT(list->next->value == 7);
    list_destroy(list);
}

/* ------------------------------------------------------------------ */
/*  Tests: find / search                                              */
/* ------------------------------------------------------------------ */

TEST(test_find_existing_value)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 10);
    list = list_insert_tail(list, 20);
    ListNode *found = list_find(list, 20);
    ASSERT(found != NULL);
    ASSERT(found->value == 20);
    list_destroy(list);
}

TEST(test_find_not_found)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 10);
    list = list_insert_tail(list, 20);
    ListNode *found = list_find(list, 30);
    ASSERT(found == NULL);
    list_destroy(list);
}

TEST(test_find_in_empty_list)
{
    ListNode *list = list_create();
    ListNode *found = list_find(list, 1);
    ASSERT(found == NULL);
}

/* ------------------------------------------------------------------ */
/*  Tests: destroy / free                                             */
/* ------------------------------------------------------------------ */

TEST(test_destroy_empty_list)
{
    ListNode *list = list_create();
    list_destroy(list);
    ASSERT(1);  /* No crash. */
}

TEST(test_destroy_populated_list)
{
    ListNode *list = list_create();
    list = list_insert_tail(list, 1);
    list = list_insert_tail(list, 2);
    list = list_insert_tail(list, 3);
    list_destroy(list);
    ASSERT(1);  /* No crash. */
}

/* ------------------------------------------------------------------ */
/*  Runner                                                            */
/* ------------------------------------------------------------------ */

int main(void)
{
    printf("Running linked-list tests...\n");

    RUN(test_create_empty_list);

    RUN(test_insert_head_single_element);
    RUN(test_insert_head_multiple_elements);

    RUN(test_insert_tail_empty_list);
    RUN(test_insert_tail_multiple_elements);

    RUN(test_delete_from_empty_list);
    RUN(test_delete_head_element);
    RUN(test_delete_tail_element);
    RUN(test_delete_middle_element);
    RUN(test_delete_single_element);
    RUN(test_delete_not_found);
    RUN(test_delete_first_duplicate_only);

    RUN(test_find_existing_value);
    RUN(test_find_not_found);
    RUN(test_find_in_empty_list);

    RUN(test_destroy_empty_list);
    RUN(test_destroy_populated_list);

    printf("\n%d / %d tests passed.\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
