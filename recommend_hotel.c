#include "recommend_hotel.h"
#include "hotel_manager.h"
#include "input_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// filter the hotel_list by location and/or price
void recommend_hotel(list_t *hotel_list) {

    // --------------- LOCATION DEFENITION ---------------
    bool is_location_filter_needed = false;
    char user_city_confirmation[MAX_LENGTH];
    printf("Do you want to filter by location (y/n)?:");

    // Prompt the user for a "y" or "n" answer to the filter by location question
    input_yes_no(user_city_confirmation);

    char user_city_input[MAX_LENGTH];
    bool is_city_available = false;

    // If the user wants to filter by location, the desired location is requested.
    // Verification of the input is performed on each entry.
    if (strcmp(user_city_confirmation, "y") == 0) {
        is_location_filter_needed = true;
        do {
            printf("Introduce the location:");
            scanf("%s", user_city_input);

            // If there is at least one node available with the city, the cycle exists successfully.
            node_t *retrieved_node = retrieve_node_with_field(hotel_list->head, user_city_input, hotel_city_comparer);
            if (retrieved_node != NULL) {
                is_city_available = true;
            } else {
                printf("Location not available.\n");
            }
        } while (!is_city_available);
        clear_input_buffer();
    }

    // --------------- PRICE DEFENITION ---------------
    bool is_price_filter_needed = false;
    char user_price_confirmation[MAX_LENGTH];
    printf("\nDo you want to define a maximum price/night (y/n)?:");

    // Prompt the user for a "y" or "n" answer to the filter by location question
    input_yes_no(user_price_confirmation);

    int max_price;
    if (strcmp(user_price_confirmation, "y") == 0) {
        is_price_filter_needed = true;
        printf("Introduce the price:");
        max_price = input_integer();
    }

    // --------------- FILTERING ---------------
    if (is_location_filter_needed || is_price_filter_needed) {
        list_t *filtered_hotel_list = (list_t *) malloc(sizeof(list_t));
        filtered_hotel_list->head = NULL;

        // Filters by city
        if (is_location_filter_needed) {
            filtered_hotel_list = filter_list(hotel_list->head, user_city_input, hotel_city_comparer);
        }

        // Filters by price
        if (is_price_filter_needed && is_location_filter_needed) {
            filtered_hotel_list = filter_list(filtered_hotel_list->head, &max_price, hotel_price_comparer);
        } else if (is_price_filter_needed){
            filtered_hotel_list = filter_list(hotel_list->head, &max_price, hotel_price_comparer);
        }

        printf("\n\nAvailable hotels based on your criteria:");
        display_hotel_list(filtered_hotel_list);
        free_memory_list(filtered_hotel_list);
    }
}