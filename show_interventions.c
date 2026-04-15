#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

void show_interventions(systems *system, FILE *f_out)
{
	if (!system->intervention ||
	    system->intervention->next == system->intervention) {
		fprintf(f_out, "No intervention has been initiated\n");
		return;
	}

	interventions * tmp = system->intervention->next;
	while (tmp != system->intervention) {
		fprintf(f_out,
			"Incident %d was assigned to unit %d, "
			"and has the following status: \"%s\"\n",
			tmp->incident->id, tmp->unit->id,
			tmp->incident->status);
		tmp = tmp->next;
	}
}