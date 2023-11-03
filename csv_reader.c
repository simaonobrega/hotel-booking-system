#include <stdio.h>
#include <stdbool.h>
#include "hotel_manager.h"
#include "reservation_manager.h"

#define MAX_LENGTH 500

/*  csv_reader() is a generic file reading function that executes the following steps:
 *  1 - Opens a file named file_name.
 *  2 - Reads a file, line by line.
 *  3 - Saves its content to a linked list.
 *  Note: when calling csv_reader, a pointer to a function responsible for parsing
 *        a specific file is passed (parse_hotel_line or parse_reservation_line)
*/
bool csv_reader(char *file_name, void (*function)(list_t *list, char* line),void *list) {

    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        return false;
    } else {
        char line[MAX_LENGTH];
        while(fgets(line,MAX_LENGTH,file)){
            function(list,line);
        }
    }
    fclose(file);
    return true;
}

// Parses a line having information about a hotel
void parse_hotel_line(list_t *list, char *line) {
    add_new_hotel_from_list((list_t *) list, line);
}

// Parses a line having information about a hotel reservation
void parse_reservation_line(list_t *list, char *line) {
    add_new_reservation_from_file((list_t *)list, line);
}