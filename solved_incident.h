#ifndef SOLVED_INCIDENT_H
#define SOLVED_INCIDENT_H

#include "structures.h"
#include "undo_last_dispatch.h"
#include <stdio.h>

void add_queue_units_available(units *unit, systems *system);
void solved_incident(systems *system, int id, FILE *f_out);

#endif