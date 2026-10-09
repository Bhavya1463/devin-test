#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

/* Create and return an empty list (NULL). */
ListNode *list_create(void);

/* Insert `value` at the head of the list and return the new head. */
ListNode *list_insert_head(ListNode *head, int value);

/* Append `value` at the tail of the list and return the (unchanged) head. */
ListNode *list_insert_tail(ListNode *head, int value);

/* Delete the first node whose value equals `value` and return the new head. */
ListNode *list_delete_value(ListNode *head, int value);

/* Search for `value` and return the matching node, or NULL if not found. */
ListNode *list_find(ListNode *head, int value);

/* Print the list contents in order, one value per line. */
void list_print(const ListNode *head);

/* Free all nodes in the list. */
void list_destroy(ListNode *head);

/* Return the number of nodes in the list. */
size_t list_length(const ListNode *head);

#endif /* LINKED_LIST_H */
