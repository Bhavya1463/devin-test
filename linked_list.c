#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------ */
ListNode *list_create(void)
{
    return NULL;
}

/* ------------------------------------------------------------------ */
ListNode *list_insert_head(ListNode *head, int value)
{
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL) {
        return head;
    }

    node->value = value;
    node->next = head;
    return node;
}

/* ------------------------------------------------------------------ */
ListNode *list_insert_tail(ListNode *head, int value)
{
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL) {
        return head;
    }

    node->value = value;
    node->next = NULL;

    if (head == NULL) {
        return node;
    }

    ListNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;

    return head;
}

/* ------------------------------------------------------------------ */
ListNode *list_delete_value(ListNode *head, int value)
{
    if (head == NULL) {
        return NULL;
    }

    if (head->value == value) {
        ListNode *next = head->next;
        free(head);
        return next;
    }

    ListNode *current = head;
    while (current->next != NULL && current->next->value != value) {
        current = current->next;
    }

    if (current->next != NULL) {
        ListNode *target = current->next;
        current->next = target->next;
        free(target);
    }

    return head;
}

/* ------------------------------------------------------------------ */
ListNode *list_find(ListNode *head, int value)
{
    ListNode *current = head;
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* ------------------------------------------------------------------ */
void list_print(const ListNode *head)
{
    const ListNode *current = head;
    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

/* ------------------------------------------------------------------ */
void list_destroy(ListNode *head)
{
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current);
        current = next;
    }
}

/* ------------------------------------------------------------------ */
size_t list_length(const ListNode *head)
{
    size_t length = 0;
    const ListNode *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}
