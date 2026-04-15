#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "add_incident.h"
#include "check_units_availability.h"
#include "dispatch.h"
#include "undo_last_dispatch.h"
#include "select_task.h"
#include "solved_incident.h"
#include "show_interventions.h"

void show_incident(systems *system, int id, FILE *f_out);
void show_unit(systems *system, int id, FILE *f_out);

void read_task(systems *system, undo_node **undo_stack, FILE *f_in,
	       FILE *f_out)
{
	char task[100];
	if (fscanf(f_in, "%s", task) != 1)
		return;

	if (!strcmp(task, "ADD_INCIDENT")) {
		read_incident(system, f_in);
	} else if (!strcmp(task, "SHOW_INCIDENT")) {
		int id;
		fscanf(f_in, "%d", &id);
		show_incident(system, id, f_out);
	} else if (!strcmp(task, "CHECK_UNITS_AVAILABILITY")) {
		fprintf(f_out, "Number of available units: %d\n",
			system->cnt_available_units);
	} else if (!strcmp(task, "SHOW_UNIT")) {
		int id;
		fscanf(f_in, "%d", &id);
		show_unit(system, id, f_out);
	} else if (!strcmp(task, "DISPATCH")) {
		dispatch(&system, undo_stack, f_out);
	} else if (!strcmp(task, "UNDO_LAST_DISPATCH")) {
		undo_last_dispatch(&system, undo_stack, f_out);
	} else if (!strcmp(task, "SOLVED_INCIDENT")) {
		int id;
		fscanf(f_in, "%d", &id);
		solved_incident(system, id, f_out);
	} else if (!strcmp(task, "SHOW_INTERVENTIONS")) {
		show_interventions(system, f_out);
	}
}