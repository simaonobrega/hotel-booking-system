// input_manager module provides functions that allow the evaluation of the different user inputs.

#ifndef HOTEL_BOOKING_SYSTEM_INPUT_MANAGER_H
#define HOTEL_BOOKING_SYSTEM_INPUT_MANAGER_H

#include "stdbool.h"

// Receive from the user an input, within the function, and check if it is
// an integer or not. Keep looping until an integer is introduced.
int input_integer();

// Clean the input buffer, to ensure that any characters left by functions like
// scanf or fgets are eliminated before calling the next input operation.
void clear_input_buffer();

// Receive a string from the user and check if "y" or "n" was introduced.
// Keep looping until "y" or "n" is verified.
void input_yes_no(char* user_city_confirmation);

#endif //HOTEL_BOOKING_SYSTEM_INPUT_MANAGER_H