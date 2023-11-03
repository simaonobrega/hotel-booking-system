#include "input_manager.h"
#include <limits.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LENGTH 100


// Receive from the user an input and check if the input
// an integer or not. Keep looping until an integer is introduced.
int input_integer() {
    char user_input[MAX_LENGTH];
    bool is_input_valid = false;
    long int user_choice;

    do {
        fgets(user_input, sizeof(user_input), stdin);

        char *endptr;
        user_choice = strtol(user_input, &endptr, 10);

        // Check if the input is an integer value
        if (endptr == user_input || *endptr != '\n' || user_choice < INT_MIN || user_choice > INT_MAX) {
            printf("Invalid input. Try again:");
        } else {
            is_input_valid = true;
        }
    } while (!is_input_valid);
    return user_choice;
}

// Receive a string from the user and check if "y" or "n" was introduced.
// Keep looping until "y" or "n" is verified.
void input_yes_no(char *user_city_confirmation) {

    char user_input[MAX_LENGTH];
    bool is_input_valid = false;
    do {
        fgets(user_input, sizeof(user_input), stdin);

        user_input[strcspn(user_input, "\n")] = 0;

        bool is_yes_selected = strcmp(user_input, "y") == 0;
        bool is_no_selected = strcmp(user_input, "n") == 0;

        if (is_yes_selected || is_no_selected) {
            is_input_valid = true;

        } else {
            printf("Invalid input. Try again:");
        }
    } while (!is_input_valid);
    strcpy(user_city_confirmation, user_input);
}

// Clean the input buffer, to ensure that any characters left by functions like
// scanf or fgets are eliminated before calling the next input operation.
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}