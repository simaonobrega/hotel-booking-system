/*
 * - csv_reader.h: interface for the generic csv_reader module, which is used to allocate data from
 *   a csv file in memory, more precisely, in a linked list
 * - parse_hotel_line() and parse_reservation_line() functions are used to deal with the details of
 *   each csv file.
*/

#ifndef CSV_READER_H
#define CSV_READER_H

#include <stdbool.h>

/* csv_reader() is a high-level function that coordinates the reading process. It makes uses of several
 * helper functions to open a file, read its content and save the data to a linked list.
*/
bool csv_reader(char *file_name, void (*function)(list_t* list,char* line),void *list);

// Parses a line having information about a hotel
void parse_hotel_line(list_t *list, char *line);

// Parses a line having information about a hotel reservation
void parse_reservation_line(list_t *list, char *line);

#endif