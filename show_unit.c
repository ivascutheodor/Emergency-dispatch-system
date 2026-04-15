#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structures.h"

void show_unit(systems *system, int id, FILE *f_out){
    if(system == NULL){
        fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
        return;
    }
    units *temp = system->unit;
    while((temp != NULL) && temp->id != id){
        temp = temp->next;
    }
    if(temp == NULL){
        fprintf(f_out, "INVALID OPERATION! ERROR 404\n");
        return;
    }
    char cuv[50];
    if(temp->availability == 1){
        strcpy(cuv, "available");
    } else{
        strcpy(cuv, "unavailable");
    }
    fprintf(f_out, "Unit %d is type %c and is %s\n", temp->id, temp->type, cuv);
}