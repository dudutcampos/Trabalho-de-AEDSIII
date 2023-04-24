#ifndef _BIB_H
#define _BIB_H

#include "event.h"

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void runEvent(Grafo *g, Event *e){ 

    switch (getMyState(e))
    {
    case 'S':
        for (int i = 0; i < g->size; i++){
            if (getNoState(g->no[i]) == 'I'){
                updateNeighbourState(g->no[i]->l, e);
            }
        }
        break;
    case 'I':
        for (int i = 0; i < g->size; i++){
            if (getNoState(g->no[i]) == 'I'){
                if(probability() <= e->probability){
                    setNoState(g->no[i], getNewState(e));
                }   
            }
        }
        break;
    
    default:
        break;
    }

}

void updateNeighbourState(List *l, Event *e){
    Edge *aux = l->begin->prox;
    while (aux != NULL){
        if(getNoState(aux->no) == getMyState(e)){
            if(probability() <= e->probability){
                setNoState(aux->no, getNewState(e));
            }
        }
        aux = aux->prox;
    }
}

double probability(){
    double x = 0;
    while (x == 0){
        x = (double) rand() / (double) RAND_MAX;
    }
    return x;
}

Event* newEvent(char *name, char myS, char newS, int t, int td, double p, int r){
    Event *e = newEmptyEvent();
    setName(e, name);
    setMyState(e, myS);
    setNewState(e, newS);
    setTime(e, t);
    setTimeDelay(e, td);
    setProbability(e, p);
    setRepeat(e, r);
    return e;         
}

Event* newEmptyEvent(){
    Event *e = (Event*)malloc(sizeof(Event));
    e->name = NULL;
    e->time = -1;
    e->timeDelay = -1;
    e->probability = -1;
    e->repeat = -1;
    return e;
}

void freeEvent(Event *e){
    free(e->name);
    free(e);
}

void printEvent(FILE *f, Event *e){
    fprintf(f, "Nome: %s, Time Delay: %d, Probability: %0.2lf.\n", 
                getName(e), getTimeDelay(e), getProbability(e));
}

//get
char* getName(Event *e){
    return e->name;
}

char getMyState(Event *e){
    return e->myState;
}

char getNewState(Event *e){
    return e->newState;
}

int getTime(Event *e){
    return e->time;
}

int getTimeDelay(Event *e){
    return e->timeDelay;
}

double getProbability(Event *e){
    return e->probability;
}

int getRepeat(Event *e){
    return e->repeat;
}

//set
void setName(Event *e, char *name){
    e->name = strdup(name);
}

void setMyState(Event *e, char c){
    e->myState = c;
}

void setNewState(Event *e, char c){
    e->newState = c;
}

void setTime(Event *e, int t){
    e->time = t;
}

void setTimeDelay(Event *e, int td){
    e->timeDelay = td;
}

void setProbability(Event *e, double p){
    e->probability = p;
}

void setRepeat(Event *e, int r){
    e->repeat = r;
}