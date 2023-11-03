#include "list.h"
#include "stdlib.h"

/* Function to add a new node to a list having head as the first element.
 * This function works with any type of list, eliminating redudancy when
 * working with different data types.
 */
void insert_end_of_list(void **head, void *data) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node_t *current = (node_t *) *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

/* Check if data can be found in the nodes of the linked list.
 * It receives a function compare, making it generic to any field being searched.
 * Retrieves the first node having the data
 */
node_t *retrieve_node_with_field(node_t *head, void *data, bool (*compare)(void *, void *)) {
    node_t *current = head;
    while (current != NULL) {
        if (compare(current->data, data)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Retrieve the last node of the linked list.
node_t *retrieve_end_node(node_t *head) {
    if (head != NULL) {
        node_t *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        return current;
    } else {
        return NULL;
    }
}

// Delete a node from a linked list having *head as the first element.
void delete_node(void **head, void *node) {
    if (*head == NULL) {
        return;
    }

    node_t *current = (node_t *) *head;

    // If there is only one node in the list
    if (current->data == node) {
        *head = current->next;
        free(current);
        return;
    }

    // Search for the node before the one to be deleted
    while (current->next->data != node) {
        current = current->next;
    }

    // Connect the nodes around the node_to_be_deleted and delete it
    node_t *node_to_delete = current->next;
    current->next = node_to_delete->next;
    free(node_to_delete);
}

// Free the memory for the nodes of list and the list itself
void free_memory_list(list_t *list) {
    if (list == NULL) {
        return;
    } else {
        node_t *current = list->head;
        while (current != NULL) {
            node_t *aux = current;
            current = current->next;
            free(aux);
        }
    }
    free(list);
}

// Creates a filtered list from the initial list pointed by head. The generic pointer "data" is compared with the data values
// in the list's nodes using a comparison function that takes the node having the data, first void* and the data being
// compared to, second void*. list.h for an example
list_t *filter_list(node_t *head, void *data, bool (*compare)(void *, void *)) {
    list_t *filtered_list = (list_t *) malloc(sizeof(list_t));
    filtered_list->head = NULL;

    // The function iterates through the whole list and inserts the node matching the criteria in the filtered_list.
    node_t *current = head;
    while (current != NULL) {
        if (compare(current->data, data)) {
            insert_end_of_list((void **) &(filtered_list->head), current->data);
        }
        current = current->next;
    }
    return filtered_list;
}