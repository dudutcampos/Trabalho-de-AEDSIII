#ifndef _BIB_H
#define _BIB_H

#include "event.h"

#endif

typedef struct queue Queue;
struct queue{
    Event **e;
    int tam;
    int size;
};

Queue* newEmptyQueue(int tam);
int empty(Queue *q);
Event* top(Queue *q);
void pop(Queue *q);
void push(Queue *q, Event *e);
void orders(Queue *q);
void freeQueue(Queue *q);