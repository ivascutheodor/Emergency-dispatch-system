#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "check_units_availability.h"
#include "add_incident.h"
#include "dispatch.h"
#include "undo_last_dispatch.h"


void free_undo_stack(undo_node **undo_stack)
{
    if (undo_stack == NULL || *undo_stack == NULL) {
        return;
    }

    undo_node *current = *undo_stack;
    undo_node *next_node;

    while (current != NULL) {
        next_node = current->next;
        
        if (current->intervention != NULL) {
            free(current->intervention);
        }
        
        free(current);
        current = next_node;
    }

    *undo_stack = NULL;
}


void add_undo_node(undo_node **undo_stack, incidents *incident, units *unit)
{
	undo_node *new_node = malloc(sizeof(undo_node));
	new_node->intervention = malloc(sizeof(interventions));
	new_node->intervention->incident = incident;
	new_node->intervention->unit = unit;
	new_node->intervention->next = NULL;
	new_node->intervention->prev = NULL;
	new_node->next = *undo_stack;
	*undo_stack = new_node;
}

void pop_undo_stack(undo_node **undo_stack)
{
	if (!*undo_stack) {
		return;
	}
	undo_node *temp = *undo_stack;
	(*undo_stack) = (*undo_stack)->next;
	free(temp->intervention);
	free(temp);
	temp = NULL;
}

void undo_last_dispatch(systems **system, undo_node **undo_stack, FILE *f_out)
{
	// curatare stiva de dispatch uri finalizate
	while (*undo_stack &&
	       strcmp((*undo_stack)->intervention->incident->status,
		      "solved") == 0) {
		pop_undo_stack(undo_stack);
	}

	if (!(*undo_stack)) {
		fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
		return;
	}

	incidents *incident_to_restore = (*undo_stack)->intervention->incident;
	units *unit_to_restore = (*undo_stack)->intervention->unit;

	strcpy(incident_to_restore->status, "queued");
	unit_to_restore->availability = 1;

	// stergem interventia din lista circulara a sistemului
	interventions *curr = (*system)->intervention->next;
	while (curr != (*system)->intervention) {
		if (curr->incident == incident_to_restore) {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			free(curr);
			break;
		}
		curr = curr->next;
	}

	// incidentul respectiv este pus inapoi in coada potrivita
	intervention_queue_node *new_inc_node =
		malloc(sizeof(intervention_queue_node));
	new_inc_node->data = incident_to_restore;

	intervention_queue_node **target_queue;
	if (!strcmp(incident_to_restore->priority, "high")) {
		target_queue = &((*system)->q_high);
	} else if (!strcmp(incident_to_restore->priority, "medium")) {
		target_queue = &((*system)->q_medium);
	} else {
		target_queue = &((*system)->q_low);
	}

	// adaugare la inceput
	new_inc_node->next = *target_queue;
	*target_queue = new_inc_node;

	// unitatea este pusa la final inapoi in lista de unitati disponibile
	unit_queue_node *new_unit_node = malloc(sizeof(unit_queue_node));
	new_unit_node->data = unit_to_restore;
	new_unit_node->next = NULL;

	// adaugare la final
	if (!(*system)->q_units_available) {
		(*system)->q_units_available = new_unit_node;
	} else {
		unit_queue_node *temp = (*system)->q_units_available;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new_unit_node;
	}

	// actualizare contor si stiva
	(*system)->cnt_available_units++;
	pop_undo_stack(undo_stack);
}