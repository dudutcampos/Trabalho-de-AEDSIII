#ifndef GRAFO
#define GRAFO

#include "grafo.h"

#endif

typedef struct event Event;

struct event{
    char *name;
    char myState;
    char newState;
    int time;
    int timeDelay;
    double probability;
    int repeat;
};

void runEvent(Grafo *g, Event *e);
void updateNeighbourState(List *l, Event *e);
double probability();

Event* newEvent(char *name, char myS, char newS, int t, int td, double p, int r);
Event* newEmptyEvent();
void freeEvent(Event *e);
void printEvent(FILE *f, Event *e);

char* getName(Event *e);
char getMyState(Event *e);
char getNewState(Event *e);
int getTime(Event *e);
int getTimeDelay(Event *e);
double getProbability(Event *e);
int getRepeat(Event *e);

void setName(Event *e, char *name);
void setMyState(Event *e, char c);
void setNewState(Event *e, char c);
void setTime(Event *e, int t);
void setTimeDelay(Event *e, int td);
void setProbability(Event *e, double p);
void setRepeat(Event *e, int r);