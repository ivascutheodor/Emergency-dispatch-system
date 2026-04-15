#ifndef ADD_INCIDENT_H
#define ADD_INCIDENT_H

#include <stdio.h>
#include "structures.h"

incidents* init_incident_sentinel();
systems* init_system();
void add_unit(systems *system, int id, char type);
void read_units(systems *system, int *cnt_units, FILE *f_in); 
void add_incident(intervention_queue_node **queue, incidents *incident);
void read_incident(systems *system, FILE *f_in); 
void free_system(systems *system);

#endif