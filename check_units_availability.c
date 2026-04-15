#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void unit_push(unit_queue_node **queue, units *unit, int *cnt) {
    unit_queue_node *node = malloc(sizeof(unit_queue_node));
    node->data = unit;
    node->next = NULL;

    if ((*queue) == NULL) {
        (*queue) = node; 
    } else {
        unit_queue_node *temp = (*queue);
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
    (*cnt)++;
}

units* unit_pop(unit_queue_node **queue, int *cnt) {
    if ((*queue) == NULL) {
        return NULL; 
    } else {
        unit_queue_node *temp = (*queue);
        units *extracted_unit = temp->data; 
        (*queue) = (*queue)->next;
        free(temp); 
        (*cnt)--;
        return extracted_unit; 
    }
}