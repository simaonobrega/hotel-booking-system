#include "edit_hotel_list.h"
#include "recommend_hotel.h"
#include "hotel_manager.h"
#include "input_manager.h"
#include <stdio.h>

// Possibilities for the user given in the edit menu.
typedef enum user_choice {
    DELETE_HOTEL = 1,
    EDIT_HOTEL,
    ADD_HOTEL,
    EXIT_TO_MAIN_MENU
} user_choice_t;

// Function that controls the flow regarding the edit module.
void edit_hotel_list(list_t *hotel_list) {

    // displays the user options for the "Edit hotel list" module
    int user_choice;
        do {
            printf("\n\n\n\n\n");
            display_hotel_list(hotel_list);
            user_choice = edit_list_menu();
            switch (user_choice) {
                case DELETE_HOTEL:
                    delete_hotel(hotel_list);
                    break;
                case EDIT_HOTEL:
                    edit_hotel_price(hotel_list);
                    break;
                case ADD_HOTEL:
                    add_new_hotel(hotel_list);
                    break;
                case EXIT_TO_MAIN_MENU:
                    printf("Exiting to main menu");
                    break;
                default:
                    printf("Option not available.");
                    break;
            }
        } while (user_choice != EXIT_TO_MAIN_MENU);
}

// Print the options available to the user and returns the user choice.
int edit_list_menu(){
    printf("Regarding the hotel list presented above, what would you like to do?\n");
    printf("1 - Delete a hotel\n");
    printf("2 - Edit hotel price\n");
    printf("3 - Add new hotel\n");
    printf("4 - Exit to main menu\n");
    printf("Choose an option:");

    int user_choice = input_integer();

    return user_choice;
}