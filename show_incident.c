#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"  
#include "add_incident.h" 
#include "show_incident.h"

void show_incident(systems *system, int id, FILE *f_out){

    if(system->incident == NULL){
        fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
        return;
    }
    incidents *temp = system->incident;
    temp = temp->next;
    while((temp != system->incident) && (temp->id != id)){
        temp = temp->next;
    }
    
    if(temp == system->incident || temp->id != id){
        fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
        return;
    }
    
    fprintf(f_out, "Incident %d has %s priority, the following description: \"%s\" and is %s\n", 
                temp->id, temp->priority, temp->description, temp->status);
}