#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "check_units_availability.h"
#include "add_incident.h"
#include "undo_last_dispatch.h"

interventions *init_intervention_sentinel(void)
{
	interventions *intervention = malloc(sizeof(interventions));
	intervention->next = intervention;
	intervention->prev = intervention;
	intervention->incident = NULL;
	intervention->unit = NULL;
	return intervention;
}

void pop_and_update(intervention_queue_node **emergency,
		    unit_queue_node **q_units_available,
		    interventions *intervention, int *cnt_available_units)
{
	interventions *new_interevention = malloc(sizeof(interventions));
	new_interevention->incident = (*emergency)->data;
	new_interevention->unit = (*q_units_available)->data;

	new_interevention->next = intervention;
	new_interevention->prev = intervention->prev;
	intervention->prev->next = new_interevention;
	intervention->prev = new_interevention;

	strcpy(new_interevention->incident->status, "intervened");
	new_interevention->unit->availability = 0;

	intervention_queue_node *aux_inc = *emergency;
	*emergency = (*emergency)->next;
	free(aux_inc);

	unit_queue_node *aux_unit = *q_units_available;
	*q_units_available = (*q_units_available)->next;
	free(aux_unit);

	(*cnt_available_units)--;
}

void dispatch(systems **system, undo_node **undo_stack, FILE *f_out)
{
	if (!*system || (*system)->cnt_available_units == 0) {
		fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
		return;
	}

	if (!(*system)->q_high && !(*system)->q_medium && !(*system)->q_low) {
		fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
		return;
	}

	if ((*system)->q_high) {
		add_undo_node(undo_stack, (*system)->q_high->data,
			      (*system)->q_units_available->data);

		pop_and_update(&(*system)->q_high,
			       &(*system)->q_units_available,
			       (*system)->intervention,
			       &(*system)->cnt_available_units);

	} else if ((*system)->q_medium) {
		add_undo_node(undo_stack, (*system)->q_medium->data,
			      (*system)->q_units_available->data);

		pop_and_update(&(*system)->q_medium,
			       &(*system)->q_units_available,
			       (*system)->intervention,
			       &(*system)->cnt_available_units);

	} else if ((*system)->q_low) {
		add_undo_node(undo_stack, (*system)->q_low->data,
			      (*system)->q_units_available->data);

		pop_and_update(&(*system)->q_low,
			       &(*system)->q_units_available,
			       (*system)->intervention,
			       &(*system)->cnt_available_units);
	}
}