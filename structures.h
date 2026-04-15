#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct units {
	int id;
	char type;
	int availability;
	struct units *next;
} units;

typedef struct incidents {
	int id;
	char priority[7];
	char *description;
	char status[11];
	struct incidents *next;
	struct incidents *prev;
} incidents;

typedef struct intervention_queue_node {
	incidents *data;
	struct intervention_queue_node *next;
} intervention_queue_node;

typedef struct unit_queue_node {
	units *data;
	struct unit_queue_node *next;
} unit_queue_node;

typedef struct interventions {
	incidents *incident;
	units *unit;
	struct interventions *next;
	struct interventions *prev;
} interventions;

typedef struct systems {
	units *unit;
	incidents *incident;
	interventions *intervention;
	intervention_queue_node *q_high;
	intervention_queue_node *q_medium;
	intervention_queue_node *q_low;
	unit_queue_node *q_units_available;
	int cnt_available_units;
} systems;

#endif