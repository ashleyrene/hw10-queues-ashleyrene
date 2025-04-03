#include "linked_list.h"
#include <stdlib.h>

// Create a new node
struct list_node *new_node(size_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (!node) {
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

// Insert a new value at the head of the linked list
void insert_at_head(struct linked_list *list, size_t value) {
    if (!list) return;
    struct list_node *new = new_node(value);
    new->next = list->head;
    list->head = new;
}

// Insert a new value at the tail of the linked list
void insert_at_tail(struct linked_list *list, size_t value) {
    if (!list) return;
    struct list_node *new = new_node(value);
    if (!list->head) {
        list->head = new;
        return;
    }

    // Traverse to the last node
    struct list_node *current = list->head;
    while (current->next) {
        current = current->next;
    }
    current->next = new;
}


// Remove and return the value at the head of the linked list
size_t remove_from_head(struct linked_list *list) {
    if (!list || !list->head) {
        return (size_t)-1; // Indicate empty list
    }
    struct list_node *temp = list->head;
    size_t value = temp->value;
    list->head = temp->next;
    free(temp);
    return value;
}

// Remove and return the value at the tail of the linked list
size_t remove_from_tail(struct linked_list *list) {
    if (!list || !list->head) {
        return (size_t)-1; // Indicate empty list
    }

    struct list_node *current = list->head;

    // If only one node exists
    if (!current->next) {
        size_t value = current->value;
        free(current);
        list->head = NULL;
        return value;
    }

    // Traverse to the second-last node
    while (current->next->next) {
        current = current->next;
    }

    size_t value = current->next->value;
    free(current->next);
    current->next = NULL;
    return value;
}

// Free all memory allocated for the linked list
void free_list(struct linked_list list) {
    struct list_node *current = list.head;
    while (current) {
        struct list_node *temp = current;
        current = current->next;
        free(temp);
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
