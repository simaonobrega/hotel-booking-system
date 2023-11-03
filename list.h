/*
 * This list module implements a generic simply linked list and its manipulation functions, e.g.: filtering, delete list,
 * delete node, search by field and insert new node.
*/

#ifndef HOTEL_BOOKING_SYSTEM_LIST_H
#define HOTEL_BOOKING_SYSTEM_LIST_H

#include <stdbool.h>
// Generic node of a singly linked list. *next points to the node on the linked list
typedef struct node {
    void *data;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
} list_t;

void insert_end_of_list(void **head, void *data);
node_t *retrieve_node_with_field(node_t *head, void *data, bool (*compare)(void *, void *));

// Retrieve the last node of the linked list pointed by head
node_t *retrieve_end_node(node_t *head);

// Delete a node from a linked list having *head as the first element.
void delete_node(void **head, void *node);

// Free the memory for the nodes of list and the list itself
void free_memory_list(list_t *list);

/* Creates a filtered list from the initial list pointed by head. The generic pointer "data" is compared with the data values
 * in the list's nodes using a comparison function that takes the node having the data, first void* and the data being
 * compared to, second void*.
 *
 * Example: bool hotel_city_comparer(void *hotel, void *city) checks if the data within
 * hotel, more specifically the city parameter, mataches the generic pointer "data".
*/
list_t *filter_list(node_t *head, void *data, bool (*compare)(void *, void *));

#endif //HOTEL_BOOKING_SYSTEM_LIST_H