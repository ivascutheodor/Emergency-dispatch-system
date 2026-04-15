#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "add_incident.h"
#include "select_task.h"
#include "undo_last_dispatch.h"
#include "dispatch.h"
#include "show_interventions.h"

int main(void)
{
	FILE *f_in = fopen("tema1.in", "r");
	if (!f_in) {
		printf("Deschiderea fisierului de intrare a esuat!\n");
		return 1;
	}

	FILE *f_out = fopen("tema1.out", "w");
	if (!f_out) {
		printf("Deschiderea fisierului de iesire a esuat!\n");
		fclose(f_in);
		return 1;
	}

	systems *system = init_system();
	undo_node *undo_stack = NULL;
	int cnt_units = 0;
	read_units(system, &cnt_units, f_in);

	int nr_tasks = 0;
	fscanf(f_in, "%d", &nr_tasks);
	fgetc(f_in);

	system->intervention = init_intervention_sentinel();
	while (nr_tasks > 0) {
		read_task(system, &undo_stack, f_in, f_out);
		nr_tasks--;
	}

	free_undo_stack(&undo_stack);
	free_system(system);
	fclose(f_in);
	fclose(f_out);

	return 0;
}