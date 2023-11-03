/*  Disciplina: Laboratório de programação (2023-2º semestre)
    E-fólio A: Enunciado C
    Nome: Simão Nóbrega
    Nr: 2202890
*/

/* This program manages the reservation system of hotels (actividade formativa 2 - C). The main file is responsible for:
 * 1 - Creating an initializing an empty hotel list.
 * 2 - Defining the location of the hotel list and reservation list.
 * 3 - Opening the files. The associated function, csv_reader, will also save the data to a singly linked list.
 * 4 - Displaying the main menu.
 * 5 - Managing the application.
 */

#include <stdio.h>
#include <stdbool.h>
#include "hotel_manager.h"
#include "edit_hotel_list.h"
#include "booking.h"
#include "reservation_manager.h"
#include "list.h"
#include "recommend_hotel.h"
#include "stdlib.h"
#include "main_menu.h"
#include "csv_reader.h"
#include "export_data.h"

// Possibilities for the user given in the main menu
typedef enum user_choice {
    BOOKING = 1,
    EDIT_HOTEL_LIST,
    RECOMMENDATION,
    CANCEL_RESERVATION,
    CREATE_CSV_FILE,
    CLOSE,
} user_choice_t;

int main() {

    // Memory allocation and initialization for the hotel and reservation lists
    list_t *hotel_list = malloc(sizeof(list_t));
    if (hotel_list == NULL) {
        printf("Failed to allocate memory for hotel_list. The program will be closed\n");
        exit(EXIT_FAILURE);
    } else {
        hotel_list->head=NULL;
    }

    list_t *reservation_list = malloc(sizeof(list_t));
    if (reservation_list == NULL) {
        printf("Failed to allocate memory for reservation_list. The program will be closed\n");
        free(hotel_list);
        exit(EXIT_FAILURE);
    } else {
        reservation_list->head = NULL;
    }

    //Tries to open the hotel and reservation files.
    //If the file is available, its data is saved to memory.
    bool is_hotel_file_read = csv_reader("hotels.csv", parse_hotel_line, hotel_list);
    bool is_reservation_file_read = csv_reader("reservations.csv", parse_reservation_line, reservation_list);

    // displays the main menu and controls the program flow
    int user_choice;
    if (is_hotel_file_read && is_reservation_file_read) {
        do {
            printf("\n\n\n\n\n\n");
            user_choice = main_menu();
            switch (user_choice) {
                case BOOKING:
                    booking(hotel_list, reservation_list);
                    break;
                case EDIT_HOTEL_LIST:
                    edit_hotel_list(hotel_list);
                    break;
                case RECOMMENDATION:
                    recommend_hotel(hotel_list);
                    break;
                case CANCEL_RESERVATION:
                    cancel_reservation(hotel_list, reservation_list);
                    break;
                case CREATE_CSV_FILE:
                    export_data("hotels.csv", hotel_list, hotel_to_csv);
                    export_data("reservations.csv", reservation_list, reservations_to_csv);
                    break;
                case CLOSE:
                    free_memory_list(reservation_list);
                    free_memory_list(hotel_list);
                    printf("Program closed.");
                    break;
                default:
                    printf("Invalid option.");
                    break;
            }
        } while (user_choice != CLOSE);
    } else {
        printf("One of the files was not properly read. Please check them and try again.");
    }
    return 0;
}