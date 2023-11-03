#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel_manager.h"
#include "list.h"
#include "input_manager.h"
#define MAXIMUM_LENGTH 75
// - Add a new hotel to the end of a linked list of hotels. Uses the generic function
//   insert_end_of_list() as an auxiliar to perform the task.
void add_new_hotel_from_list(list_t *hotel_list, char *complete_data) {
    hotel_t *new_hotel = csv_hotel_line_parser(complete_data);
    if (new_hotel != NULL) {
        insert_end_of_list((void **) &(hotel_list->head), (void *) new_hotel);
    }
}

// This function receives one line of a .csv file and parses the whole content considering the "," delimiter.
hotel_t *csv_hotel_line_parser(char *complete_data) {
    hotel_t *hotel = malloc(sizeof(hotel_t));
    if (hotel != NULL) {
        char *delimiter = strtok(complete_data, ",");
        hotel->id = atoi(delimiter);
        delimiter = strtok(NULL, ",");
        hotel->name = strdup(delimiter);
        delimiter = strtok(NULL, ",");
        hotel->location = strdup(delimiter);
        delimiter = strtok(NULL, ",");
        hotel->number_of_rooms_available = atoi(delimiter);
        delimiter = strtok(NULL, ",");
        hotel->price_per_night = atoi(delimiter);
        hotel->next = NULL;
    }
    return hotel;
}

// Function to check if the id being searched matches the ID of the node being evaluated.
bool hotel_id_comparer(void *hotel, void *id) {
    hotel_t *current_hotel = (hotel_t *) hotel;
    int *searched_id = (int *) id;
    return (current_hotel->id == *searched_id);
}

// Check if the city being searched matches the city of the node being evaluated.
bool hotel_city_comparer(void *hotel, void *city) {
    hotel_t *current_hotel = (hotel_t *) hotel;
    return (strcmp(current_hotel->location, (char *) city) == 0);
}

// Check if the hotel price per night is smaller than price.
bool hotel_price_comparer(void *hotel, void *price) {
    hotel_t *current_hotel = (hotel_t *) hotel;
    return (current_hotel->price_per_night <= *(int *) price);
}

// Retrieves the hotel node with the ID=hotel_id
hotel_t *get_hotel_node_by_id(list_t *hotel_list, int hotel_id) {
    node_t *node_with_field = retrieve_node_with_field(hotel_list->head, &hotel_id, hotel_id_comparer);
    if (node_with_field != NULL) {
        return (hotel_t *) node_with_field->data;
    }
    return NULL;
}

// Room booking. It is verified if the ID is valid, hotel_node != Null, and if
// there are enough rooms for the reservation to proceed. Depending on the outcome,
// different conditions are returned to guide the printing process.
reservation_status_t reserve_room_verification(list_t *hotel_list, int hotel_id) {
    hotel_t *hotel_node = get_hotel_node_by_id(hotel_list, hotel_id);
    if (hotel_node == NULL) {
        return INVALID_HOTEL_ID;
    } else if (hotel_node->number_of_rooms_available == 0) {
        return NO_ROOMS_AVAILABLE;
    } else {
        --hotel_node->number_of_rooms_available;
        return RESERVATION_SUCCESS;
    }
}

// Retrive the hotel name based on its ID
char *get_hotel_name(list_t *hotel_list, int hotel_id) {
    hotel_t *hotel_node = get_hotel_node_by_id(hotel_list, hotel_id);
    return hotel_node->name;
}

// Display the whole hotel list
void display_hotel_list(list_t *hotel_list) {
    if (hotel_list->head == NULL) {
        printf("\nNo hotels available.\n");
    } else {
        node_t *current = hotel_list->head;
        printf("\n\n------------------------------------------------- HOTEL LIST -------------------------------------------------\n");
        printf("%-5s %-30s %-30s %-20s %-12s\n", "Id", "Name", "City", "Available rooms", "Price/night");
        while (current != NULL) {
            hotel_t *hotel_data = (hotel_t *) current->data;
            print_hotel(hotel_data);
            current = current->next;
        }
        printf("--------------------------------------------------------------------------------------------------------------\n");
    }
}

// Print the information relative to a hotel.
void print_hotel(hotel_t *hotel) {
    printf("%-5d %-30s %-30s %-20d %-12d\n", hotel->id, hotel->name, hotel->location,
           hotel->number_of_rooms_available, hotel->price_per_night);
}

// Formats the content of hotel_t node according to the requirements of the hotel's csv file.
void hotel_to_csv(void *data, char *buffer, size_t buffer_size) {
    hotel_t *hotel = (hotel_t *) data;
    snprintf(buffer, buffer_size, "%d,%s,%s,%d,%d", hotel->id, hotel->name, hotel->location,
             hotel->number_of_rooms_available, hotel->price_per_night);
}

// Get the hotel considering the user input and handles the verification of the user input
hotel_t *get_hotel_by_user_input(list_t *hotel_list, const char *prompt) {
    if (hotel_list->head == NULL) {
        printf("\nNo hotels available.");
        return NULL;
    }

    int user_choice;
    hotel_t *hotel;

    printf("%s (0 - Edit Hotel Menu):", prompt);

    while (1) {
        user_choice = input_integer();
        if (user_choice == 0) {
            break;
        }

        hotel = get_hotel_node_by_id(hotel_list, user_choice);

        if (hotel != NULL) {
            return hotel;
        }

        printf("Invalid Hotel ID. Choose a new ID:");
    }

    printf("You will be directed to the Edit Hotel Menu.");
    return NULL;
}

// Delete a hotel from the list using the hotel ID selected by the user
void delete_hotel(list_t *hotel_list) {
    hotel_t *hotel = get_hotel_by_user_input(hotel_list, "Choose the hotel ID to be deleted");
    if (hotel != NULL) {
        delete_node((void **) &(hotel_list->head), hotel);
    }
}

// Edit the hotel price using the hotel ID selected by the user
void edit_hotel_price(list_t *hotel_list) {
    hotel_t *hotel = get_hotel_by_user_input(hotel_list, "Choose the hotel ID to edit");
    if (hotel != NULL) {
        printf("Define the new price in Euros:");
        int price = input_integer();
        hotel->price_per_night = price;
    }
}

// - User adds a new hotel to the hotel list.
// - The ID of the reservation is increased sequentially, therefore,
//   the id of the end node of the hotel_list is always retrived
//   during the reservation process.
void add_new_hotel(list_t *hotel_list) {

    hotel_t *new_hotel = (hotel_t *) malloc(sizeof(hotel_t));

    if (new_hotel == NULL) {
        printf("Memory allocation failed. The new reservation has not been added.");
        return;
    }

    printf("Define the hotel name:");
    char hotel_name[MAXIMUM_LENGTH];
    scanf("%s",hotel_name);
    new_hotel->name = strdup(hotel_name);
    clear_input_buffer();

    printf("Define the location:");
    char hotel_location[MAXIMUM_LENGTH];
    scanf("%s",hotel_location);
    new_hotel->location = strdup(hotel_location);
    clear_input_buffer();

    printf("Define the price per night:");
    int price_per_night = input_integer();
    new_hotel->price_per_night = price_per_night;

    printf("Define the number of rooms available:");
    int rooms_available = input_integer();
    new_hotel->number_of_rooms_available = rooms_available;

    new_hotel->next = NULL;

    if (hotel_list->head == NULL) {
        // The list is empty, so this is the first hotel being added -> ID of 1.
        new_hotel->id = 1;
    } else {
        // Retrieve the last hotel's ID and increment it for the new hotel.
        node_t *last_node = retrieve_end_node(hotel_list->head);
        new_hotel->id = ((hotel_t *) last_node->data)->id + 1;
    }

    insert_end_of_list((void **) &(hotel_list->head), new_hotel);
}