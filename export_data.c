#include "export_data.h"
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

#define MAX_LENGTH 500

// Exports data from a linked list to a CSV file using a converter function, to_csv.
// If the operation succeeds, it returns true, false otherwise.
bool export_data(char *file_name, list_t *list, to_csv_func to_csv) {
    FILE *file = fopen(file_name, "w");

    if (file == NULL) {
        printf("File %s could not open.", file_name);
        return false;
    }

    node_t *current = list->head;
    char buffer[MAX_LENGTH];

    // Convert each node's data of a linked list to CSV format.
    while (current != NULL) {
        to_csv(current->data, buffer, sizeof(buffer));
        if (fprintf(file, "%s\n", buffer) < 0) {
            printf("The information could not be written to file %s.", file_name);
            fclose(file);
            return false;
        }
        current = current->next;
    }
    if (fclose(file) != 0) {
        printf("Error closing file %s.", file_name);
        return false;
    }
    printf("Data to file %s was successfuly exported.\n", file_name);
    return true;
}

