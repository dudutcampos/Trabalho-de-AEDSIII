#include "queue.h"
#include <stdlib.h>

Queue* newEmptyQueue(int tam){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->e = (Event**)malloc(tam*sizeof(Event*));
    for (int i = 0; i < tam; i++){
        q->e[i] = NULL;
    }
    q->tam = 0;
    return q;
}

int empty(Queue *q){
    if(q->tam == 0){
        return 1;
    }
    return 0;
}

Event* top(Queue *q){
    return q->e[0];
}

void pop(Queue *q){
    Event *e = q->e[0];
    for (int i = 1; i < q->tam; i++){
        q->e[i-1] = q->e[i];
    }
    q->tam--;
}

void push(Queue *q, Event *e){
    q->tam++;
    q->e[q->tam-1] = e;
    orders(q);
}

void orders(Queue *q){
    int i, j;
    Event *aux;
    for(i = 1; i < q->tam; i++) {
        aux = q->e[i];
        j = i - 1;
        while((j >= 0) && (aux->time < q->e[j]->time)) {
            q->e[j + 1] = q->e[j];
            j--;
        }
        q->e[j + 1] = aux;
    }
}

void freeQueue(Queue *q){
    for (int i = 0; i < q->tam; i++){
        freeEvent(q->e[i]);
    }
    free(q->e);
    free(q);
}