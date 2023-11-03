#include <stdio.h>
#include "main_menu.h"
#include "input_manager.h"

// Print the options available to the user in the main menu and returns the user choice
int main_menu() {

    printf("***********************************************\n");
    printf("|            HOTEL BOOKING SYSTEM             |\n");
    printf("***********************************************\n");

    printf("1 - Book a hotel.\n");
    printf("2 - Edit hotel list.\n");
    printf("3 - Hotel recommendation.\n");
    printf("4 - Cancel a booking.\n");
    printf("5 - Export all information - updates CSV.\n");
    printf("6 - Close.\n");
    printf("***********************************************\n");
    printf("Choose an option:");

    int user_choice = input_integer();

    return user_choice;
}