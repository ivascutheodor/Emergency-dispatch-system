#ifndef CHECK_UNITS_AVAILABILITY_H
#define CHECK_UNITS_AVAILABILITY_H
#include "structures.h"

void unit_push(unit_queue_node **queue, units *unit, int *cnt);
units* unit_pop(unit_queue_node **queue, int *cnt);

#endif