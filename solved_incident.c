#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "add_incident.h"
#include "dispatch.h"
#include "undo_last_dispatch.h"

void add_queue_units_available(units *unit, systems *system)
{
	unit_queue_node *new_node = malloc(sizeof(unit_queue_node));
	new_node->data = unit;
	new_node->next = NULL;

	if (!system->q_units_available) {
		system->q_units_available = new_node;
	} else {
		unit_queue_node *tmp = system->q_units_available;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = new_node;
	}
}

void solved_incident(systems *system, int id, FILE *f_out)
{
	interventions *sentinel = system->intervention;
	interventions *curr = sentinel->next;

	while (curr != sentinel) {
		if (curr->incident->id == id) {
			if (strcmp(curr->incident->status, "solved") == 0) {
				fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
				return;
			}
			strcpy(curr->incident->status, "solved");
			curr->unit->availability = 1;
			add_queue_units_available(curr->unit, system);
			system->cnt_available_units++;
			return;
		}
		curr = curr->next;
	}

	//daca ID ul nu exista deloc in lista de operatii
	fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
}