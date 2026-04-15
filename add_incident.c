#include "add_incident.h"
#include "check_units_availability.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void add_unit(systems *system, int id, char type)
{
	units *temp = malloc(sizeof(units));
	temp->id = id;
	temp->availability = 1;
	temp->type = type;
	temp->next = NULL;
	if (!system->unit) {
		system->unit = temp;
	} else {
		units *aux = system->unit;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = temp;
	}
	unit_push(&system->q_units_available, temp,
		  &system->cnt_available_units);
}

void read_units(systems *system, int *cnt_units, FILE *f_in)
{
	if (fscanf(f_in, "%d", cnt_units) != 1) {
		return;
	}
	int id;
	char type;
	for (int i = 0; i < *cnt_units; i++) {
		if (fscanf(f_in, "%d %c", &id, &type) == 2) {
			add_unit(system, id, type);
		}
	}
}

void free_units(units *head)
{
	units *aux;
	while (head) {
		aux = head;
		head = head->next;
		free(aux);
		aux = NULL;
	}
}

void free_incidents(incidents *sentinel)
{
	if (!sentinel) {
		return;
	}
	incidents *curent = sentinel->next;
	incidents *aux;
	while (curent != sentinel) {
		aux = curent;
		curent = curent->next;
		free(aux->description);
		aux->description = NULL;
		free(aux);
		aux = NULL;
	}
	free(sentinel->description);
	sentinel->description = NULL;
	free(sentinel);
	sentinel = NULL;
}

void free_queue(intervention_queue_node *head)
{
	intervention_queue_node *aux;
	while (head) {
		aux = head;
		head = head->next;
		free(aux);
		aux = NULL;
	}
}

void free_unit_queue(unit_queue_node *head)
{
	unit_queue_node *tmp;
	while (head) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void free_system(systems *system)
{
	if (!system) {
		return;
	}

	free_queue(system->q_high);
	free_queue(system->q_medium);
	free_queue(system->q_low);
	free_unit_queue(system->q_units_available);

	// eliberam lista circulara de interventii
	if (system->intervention) {
		interventions *curr = system->intervention->next;
		while (curr != system->intervention) {
			interventions *temp = curr;
			curr = curr->next;
			free(temp); // stergem nodul de legatura
		}
		free(system->intervention); // stergem si sentinela
	}

	free_units(system->unit);
	free_incidents(system->incident);

	free(system);
}

incidents *init_incident_sentinel(void)
{
	incidents *sentinel = malloc(sizeof(incidents));
	sentinel->id = 0;
	strcpy(sentinel->priority, "low");
	sentinel->description = malloc(strlen("test incident") + 1);
	strcpy(sentinel->description, "test incident");
	strcpy(sentinel->status, "solved");
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
	return sentinel;
}

systems *init_system(void)
{
	systems *system = malloc(sizeof(systems));
	system->unit = NULL;
	system->incident = init_incident_sentinel();
	system->q_high = NULL;
	system->q_medium = NULL;
	system->q_low = NULL;

	system->q_units_available = NULL;
	system->cnt_available_units = 0;
	system->intervention = NULL;
	return system;
}

void add_incident(intervention_queue_node **queue, incidents *incident)
{
	intervention_queue_node *node = malloc(sizeof(intervention_queue_node));
	node->data = incident;
	node->next = NULL;
	if (!*queue) {
		*queue = node;
	} else {
		intervention_queue_node *temp = *queue;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = node;
	}
}

void read_incident(systems *system, FILE *f_in)
{
	incidents *incident = malloc(sizeof(incidents));
	if (fscanf(f_in, "%d %s", &incident->id, incident->priority) != 2) {
		free(incident);
		return;
	}
	char buffer[256];
	fscanf(f_in, " \"%[^\"]\"", buffer);
	fgetc(f_in);
	int len = strlen(buffer);
	incident->description = malloc((len + 1) * sizeof(char));
	strcpy(incident->description, buffer);
	strcpy(incident->status, "queued");
	incidents *sentinel = system->incident;
	incidents *temp = sentinel->prev;

	temp->next = incident;
	incident->prev = temp;
	incident->next = sentinel;
	sentinel->prev = incident;

	if (!strcmp(incident->priority, "low")) {
		add_incident(&system->q_low, incident);
	} else if (!strcmp(incident->priority, "medium")) {
		add_incident(&system->q_medium, incident);
	} else if (!strcmp(incident->priority, "high")) {
		add_incident(&system->q_high, incident);
	}
}