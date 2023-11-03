#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation_manager.h"
#include "input_manager.h"
#include "hotel_manager.h"
#include <time.h>

// - Adds a new reservation by the user. The ID of the reservation is increased sequentially, therefore, the id of the
//   end node of the reservation_list is always retrived during the reservation process.
void add_new_reservation(list_t *reservation_list, char *hotel_name, int hotel_id) {

    reservation_t *new_reservation = (reservation_t *) malloc(sizeof(reservation_t));

    if (new_reservation == NULL) {
        printf("Memory allocation failed. The new reservation has not been added.");
        return;
    }

    time_t current_time = time(NULL);

    new_reservation->next = NULL;
    new_reservation->hotel_name = strdup(hotel_name);
    new_reservation->hotel_id = hotel_id;
    new_reservation->reservation_date = current_time;

    if (reservation_list->head == NULL) {
        // The list is empty, so this is the first reservation with an ID of 1.
        new_reservation->id = 1;
    } else {
        // Retrieve the last reservation's ID and increment it for the new reservation.
        node_t *last_node = retrieve_end_node(reservation_list->head);
        new_reservation->id = ((reservation_t *) last_node->data)->id + 1;
    }

    insert_end_of_list((void **) &(reservation_list->head), new_reservation);
}

// Add a new reservation when reading the .csv file to the computer's memory (using linked list)
void add_new_reservation_from_file(list_t *reservation_list, char *reservation_data) {
    reservation_t *new_reservation = csv_reservation_line_parser(reservation_data);
    if (new_reservation != NULL) {
        insert_end_of_list((void **) &(reservation_list->head), (void *) new_reservation);
    }
}

// This function receives one line of a .csv file and parses the whole content considering the "," delimiter.
reservation_t *csv_reservation_line_parser(char *data) {

    reservation_t *reservation = malloc(sizeof(reservation_t));

    if (reservation != NULL) {
        char *delimiter = strtok(data, ",");
        reservation->id = atoi(delimiter);
        delimiter = strtok(NULL, ",");
        reservation->hotel_name = strdup(delimiter);
        delimiter = strtok(NULL, ",");
        reservation->hotel_id = atoi(delimiter);
        delimiter = strtok(NULL, ",");

        // Parse the date string into individual components
        int year, month, day;
        sscanf(delimiter, "%d-%d-%d", &year, &month, &day);

        // Create a struct tm to convert the parsed date components to time_t type.
        // tm_year represents the number of years since 1900.
        // tm_month has a range between 0 to 11.
        struct tm date_tm = {0};
        date_tm.tm_year = year - 1900;
        date_tm.tm_mon = month - 1;
        date_tm.tm_mday = day;

        // Convert struct tm to time_t
        reservation->reservation_date = mktime(&date_tm);

    }
    return reservation;
}

// Display the complete reservation list
void display_reservation_list(list_t *reservation_list) {
    node_t *current = reservation_list->head;
    printf("\n\n\n------------------------------- RESERVATIONS -------------------------------\n");
    printf("%-10s | %-35s | %-10s | %-15s\n", "Reser. Id", "Hotel name", "Hotel ID", "Booking date");
    while (current != NULL) {
        reservation_t *reservation = (reservation_t *) current->data;
        struct tm *booking_time = localtime(&(reservation->reservation_date));
        char booking_time_str[11];
        strftime(booking_time_str, sizeof(booking_time_str), "%Y-%m-%d", booking_time);
        printf("%-10d | %-35s | %-10d | %-15s\n", reservation->id, reservation->hotel_name, reservation->hotel_id,
               booking_time_str);
        current = current->next;
    }
    printf("----------------------------------------------------------------------------\n");
}

// - Cancel a reservation using the reservation ID.
// - It updates the numbers of rooms available and updates the reservation linked list by deleting the respective node.
void cancel_reservation(list_t *hotel_list, list_t *reservation_list) {
    if (reservation_list->head != NULL) {
        int user_choice;
        reservation_t *reservation;
        display_reservation_list(reservation_list);
        printf("Choose the reservation ID you want to cancel (0 - main menu):");

        while (1) {
            user_choice = input_integer();
            if (user_choice == 0) {
                printf("You will be directed to the main menu.");
                return;
            }

            reservation = get_reservation_node_by_id(reservation_list, user_choice);

            if (reservation != NULL) {
                break;
            }

            printf("Reservation ID not valid. Choose a new ID (0 - main menu):");
        }

        // - Hotel node having the hotel_id associated with the reservation is retrieved so the number of rooms can be
        //   increased according to the cancellation.
        // - The increase of the hotel availability is only performed if the hotel has not been deleted from the list.
        int hotel_id = reservation->hotel_id;
        hotel_t *hotel = get_hotel_node_by_id(hotel_list, hotel_id);
        delete_node((void **)&(reservation_list->head), reservation);
        if (hotel != NULL) {
            ++hotel->number_of_rooms_available;
        }
        printf("Your reservation has been successfully deleted.");

    } else {
        printf("No bookings available.");
    }
}

// Function to check if the id being searched matches
// the ID of the node being evaluated.
bool reservation_id_comparer(void *hotel, void *id) {
    reservation_t *current_hotel = (reservation_t *) hotel;
    int *searched_id = (int *) id;
    return (current_hotel->id == *searched_id);
}

// Retrieves the hotel node with the ID=hotel_id
reservation_t *get_reservation_node_by_id(list_t *reservation_list, int hotel_id) {
    node_t *node_with_field = retrieve_node_with_field(reservation_list->head, &hotel_id, reservation_id_comparer);
    if (node_with_field != NULL) {
        return (reservation_t *) node_with_field->data;
    }
    return NULL;
}

// Helper function, of the module export data, that writes the received data in the correct csv format.
// Result saved in the buffer pointer.
void reservations_to_csv(void *data, char *buffer, size_t buffer_size) {
    reservation_t *reservation = (reservation_t *) data;
    char date_buffer[20];

    // Convert time_t to tm structure
    struct tm *date = localtime(&reservation->reservation_date);

    strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", date);

    snprintf(buffer, buffer_size, "%d,%s,%d,%s", reservation->id, reservation->hotel_name, reservation->hotel_id,
             date_buffer);
}