/*
 * - export_data.h: interface for the generic export_data module, which is used to export data from a linked list
 *   to a CSV file.
*/

#ifndef HOTEL_BOOKING_SYSTEM_EXPORT_DATA_H
#define HOTEL_BOOKING_SYSTEM_EXPORT_DATA_H

#include "list.h"
#include "stdio.h"

// Defines the function template for the custom conversion functions used to
// export data to a CSV file.
typedef void (*to_csv_func)(void *data, char *buffer, size_t buffer_size);

// Export data from a linked list to a csv file using a custom function
bool export_data(char *file_name, list_t *list, to_csv_func to_csv);

#endif //HOTEL_BOOKING_SYSTEM_EXPORT_DATA_H