/*
 * - hotel_manager.h: interface for the hotel_manager module, which provides the functions needed
 *   to manage a list of hotels (auxiliar functions to the generic list described at list.c/.h)
 * - The module makes use of a generic list implementation to manage hotels as a linked list with
 *   the generic type list_t (module by list.c and list.h)
*/

#ifndef HOTEL_LIST_H
#define HOTEL_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

// Hotel structure. *next points to the next hotel on the linked list
typedef struct hotel {
    int id;
    char *name;
    char *location;
    int number_of_rooms_available;
    int price_per_night;
    struct hotel *next;
} hotel_t;

typedef enum {
    RESERVATION_SUCCESS,
    INVALID_HOTEL_ID,
    NO_ROOMS_AVAILABLE
} reservation_status_t;

// add a new hotel to the end of a linked list of hotels
void add_new_hotel_from_list(list_t *hotel_list, char *complete_data);

// This function receives one line of a .csv file and parses its content to the appropriate variables
hotel_t *csv_hotel_line_parser(char *);

// Check if the id being searched matches the ID of the node being evaluated
bool hotel_id_comparer(void *hotel, void *id);

// Check if the hotel price per night is smaller than price
bool hotel_price_comparer(void *hotel, void *price);

// Check if the city being searched matches the city of the node being evaluated
bool hotel_city_comparer(void *hotel, void *city);

// Retrieve a pointer to the hotel node having an ID == hotel_id
hotel_t *get_hotel_node_by_id(list_t *hote_list, int hotel_id);

// Retrieve the reservation status by analysing the list of hotels, its availability and the user's choice
reservation_status_t
reserve_room_verification(list_t *hotel_list, int hotel_id);

// Retrive the hotel name based on its ID
char *get_hotel_name(list_t *hotel_list, int hotel_id);

// displays the list of hotels
void display_hotel_list(list_t *hotel_list);

// Print the information relative to a hotel.
void print_hotel(hotel_t *hotel);

// Formats the content of hotel_t node according to the requirements of the hotel's csv file,
// saving its data in buffer.
void hotel_to_csv(void *data, char *buffer, size_t buffer_size);

// Get the hotel considering the user input and handles the verification of the user input
hotel_t *get_hotel_by_user_input(list_t *hotel_list, const char *prompt);

// This function deletes a hotel from the list using the hotel ID (defined within the function by the user)
void delete_hotel(list_t *hotel_list);

// Edit the hotel price using the hotel ID (defined within the function by the user)
void edit_hotel_price(list_t *hotel_list);

// Add a new hotel to the hotel list.
void add_new_hotel(list_t *hotel_list);

#endif