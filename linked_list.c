#include "linked_list.h"
#include <stdlib.h>

struct list_node {
    uint64_t value;
    struct list_node *next;
};

struct linked_list {
    struct list_node *head;
    struct list_node *tail;
};

// Create a new node with the given value
static struct list_node *new_node(uint64_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (!node) return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

// Insert at the tail of the list
void insert_at_tail(struct linked_list *list, uint64_t value) {
    struct list_node *node = new_node(value);
    if (!node) return;

    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
}

// Remove and return value from the head of the list
uint64_t remove_from_head(struct linked_list *list) {
    if (!list->head) return 0; // Empty list

    struct list_node *temp = list->head;
    uint64_t value = temp->value;

    list->head = list->head->next;
    if (!list->head) list->tail = NULL; // If the list is now empty

    free(temp);
    return value;
}

// Free the entire linked list
void free_list(struct linked_list *list) {
    struct list_node *current = list->head;
    while (current) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
    list->head = list->tail = NULL;
}
