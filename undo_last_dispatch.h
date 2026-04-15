#ifndef UNDO_LAST_DISPATCH_H
#define UNDO_LAST_DISPATCH_H

#include <stdio.h>
#include "structures.h"

typedef struct undo_node {
    interventions *intervention;
    struct undo_node *next;
} undo_node;

void add_undo_node(undo_node **undo_stack, incidents *incident, units *unit);
void pop_undo_stack(undo_node **undo_stack);
void undo_last_dispatch(systems **system, undo_node **undo_stack, FILE *f_out);
void free_undo_stack(undo_node **undo_stack);

#endif