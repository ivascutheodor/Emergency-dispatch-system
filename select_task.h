#ifndef SELECT_TASK_H
#define SELECT_TASK_H

#include <stdio.h>
#include "structures.h"
#include "undo_last_dispatch.h"

void read_task(systems *system, undo_node **undo_stack, FILE *f_in, FILE *f_out);

#endif