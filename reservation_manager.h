/*
 * - The reservation_manager module is used to manage the reservations in the hotel booking system. It provides
 *   functions to add new reservations, cancel reservations, parse the data from
 *   a .csv file, retrieve nodes from the list as a funcion of the ID and display the reservation list.
 * - The reservation data is stored in a linked list, where each node contains a reservation's ID, hotel name, hotel ID,
 *   and booking date.
 */

#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <stdbool.h>
#include <time.h>
#include "list.h"


// Hotel structure. *next points to the next hotel on the linked list
typedef struct reservation {
    int id;
    char *hotel_name;
    int hotel_id;
    time_t reservation_date;
    struct reservation *next;
} reservation_t;

// Add a new reservation to the reservation_list by receving data, a line of text, that
// will be parsed by csv_reservation_line_parser.
void add_new_reservation_from_file(list_t *reservation_list, char *data);

// Helper function, of the module export data, that writes the received data in the correct csv format.
// Result is saved in the buffer pointer.
void reservations_to_csv(void *data, char *buffer, size_t buffer_size);

// Adds a new reservation created by the user
void add_new_reservation(list_t *reservation_list, char *hotel_name, int hotel_id);

// Cancel a reservation and update the room availability for the associated hotel
void cancel_reservation(list_t *hotel_list, list_t *reservation_list);

// Retrieves the hotel node with the ID=hotel_id
reservation_t *get_reservation_node_by_id(list_t *reservation_list, int hotel_id);

// Receive one line of a .csv file and parses the whole content considering the "," delimiter.
reservation_t *csv_reservation_line_parser(char *data);

// Display the complete reservation list
void display_reservation_list(list_t *reservation_list);

#endif //RESERVATION_LIST_H