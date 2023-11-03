/* This file is responsible for managing the booking of a hotel. The following steps
 * are included:
 * 1 - Displays the hotels' list.
 * 2 - Prompt's the user to choose a hotel by its ID.
 * 3 - Checks if it is possible to reserve a room considering the ID selected by the user.
 * 4 - Creates a new reservation and adds it to the reservation_list.
 */

#include "booking.h"
#include <stdio.h>
#include "hotel_manager.h"
#include "input_manager.h"

void booking(list_t *hotel_list, list_t *reservation_list) {

    display_hotel_list(hotel_list);
    bool reservation_complete = false;

    int hotel_id;

    // Loops until the user makes a valid reservation or chooses to return to the main menu (hotel_id == 0)
    do {
        printf("Choose the Id of the hotel you want to book (0 - initial menu):");
        hotel_id = input_integer();
        if (hotel_id == 0) {
            return; // Returns to the main menu
        }
        //Checks if it is possible to reserve a room considering the ID selected by the user
        reservation_status_t reservation_status = reserve_room_verification(hotel_list, hotel_id);

        // If ID is available and there is at least one room, a new reservation is created
        if (reservation_status == RESERVATION_SUCCESS) {
            char *hotel_name = get_hotel_name(hotel_list, hotel_id);

            add_new_reservation(reservation_list, hotel_name, hotel_id);
            printf("Your room was successfully reserved.");
            reservation_complete = true;

        } else if (reservation_status == NO_ROOMS_AVAILABLE) {
            char *hotel_name = get_hotel_name(hotel_list, hotel_id);
            printf("No rooms available in %s. Choose another hotel.\n", hotel_name);

        } else {
            printf("Invalid Hotel ID.\n");
        }
    } while (!reservation_complete);
}