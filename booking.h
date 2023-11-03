#include <stdbool.h>
#include "hotel_manager.h"
#include "reservation_manager.h"

#ifndef RESERVATION_H
#define RESERVATION_H

/* booking() is a high-level function that coordinates the booking process. It makes uses of several
 * helper functions to display the list of hotels, prompt the user, check room availability and
 * create a new reservation.
 */
void booking(list_t *hotel_list, list_t *reservation_list);

#endif