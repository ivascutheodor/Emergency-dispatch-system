#ifndef DISPATCH_H
#define DISPATCH_H

#include <stdio.h>
#include "structures.h"
#include "undo_last_dispatch.h"

interventions* init_intervention_sentinel();
void pop_and_update(intervention_queue_node **emergency, unit_queue_node **q_units_available, interventions *intervention, int *cnt_available_units);
void dispatch(systems **system, undo_node **undo_stack, FILE *f_out);

#endif