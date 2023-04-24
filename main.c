#ifndef _BIB_H
#define _BIB_H

#include "event.h"
#include "queue.h"

#endif
#ifndef GRAFO
#define GRAFO

#include "grafo.h"

#endif

#include "arquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void run(Grafo *g, char *path, int tdI, int tdR, double pI, double pR, int tfinal);
void save(Grafo *g, FILE *f);

void main(){
    int I, tfinal, tdI, tdR;
    double pI, pR;
    char path[50];
    Grafo *g;
    FILE *entrada = openFILE("entrada.txt", "r");
    
    //cenario 1 tfinal 30.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoA(20, 0);
    chandGrafo1(g, I);
    run(g, path, tdI, tdR, pI, pR, tfinal);
    
    //cenario 1 tfinal 50.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoA(20, 0);
    chandGrafo1(g, I);
    run(g, path, tdI, tdR, pI, pR, tfinal);
    
    //cenario 2 tfinal 30.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoA(20, 0);
    chandGrafo2(g, I, 'R');
    chandGrafo1(g, I);
    run(g, path, tdI, tdR, pI, pR, tfinal);
    
    //cenario 2 tfinal 50.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoA(20, 0);
    chandGrafo2(g, I, 'R');
    chandGrafo1(g, I);
    run(g, path, tdI, tdR, pI, pR, tfinal);
    
    //cenario 3 tfinal 30.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoA(20, 0);
    chandGrafo1(g, I);
    run(g, path, tdI, tdR, pI, pR, tfinal);

    //cenario 3 tfinal 50.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoA(20, 0);
    chandGrafo1(g, I);
    run(g, path, tdI, tdR, pI, pR, tfinal);

    //cenario 4 tfinal 30
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoB(20, 0);
    chandGrafo2(g, I, 'I');
    run(g, path, tdI, tdR, pI, pR, tfinal);

    //cenario 4 tfinal 50
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoB(20, 0);
    chandGrafo2(g, I, 'I');
    run(g, path, tdI, tdR, pI, pR, tfinal);

    //cenario 5 tfinal 30.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoB(20, 0);
    chandGrafo2(g, I, 'R');
    chandGrafo1(g, 11);
    chandGrafo1(g, 17);
    run(g, path, tdI, tdR, pI, pR, tfinal);

    //cenario 5 tfinal 50.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoB(20, 0);
    chandGrafo2(g, I, 'R');
    chandGrafo1(g, 2);
    chandGrafo1(g, 6);
    run(g, path, tdI, tdR, pI, pR, tfinal);

    //cenario 6 tfinal 30.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoB(20, 0);
    chandGrafo2(g, 2, 'I');
    run(g, path, tdI, tdR, pI, pR, tfinal);

    //cenario 6 tfinal 50.
    reedEntry(entrada, &I, &tfinal, &tdI, &tdR, &pI, &pR, path);
    g = newGrafoB(20, 0);
    chandGrafo2(g, 2, 'I');
    run(g, path, tdI, tdR, pI, pR, tfinal);

    closeFILE(entrada);
}

void run(Grafo *g, char *path, int tdI, int tdR, double pI, double pR, int tfinal){
    // cria eventos e fila de prioridades.
    Event *e1 = newEvent("Infecção", 'S', 'I', tdI, tdI, pI, 1);
    Event *e2 = newEvent("Recuperação", 'I', 'R', tdR, tdR, pR, 1);
    Queue *q = newEmptyQueue(2);
    push(q, e1);
    push(q, e2);

    FILE *f = openFILE(path, "w");
    fprintf(f, "Running the simulation\n\n");
    fprintf(f, "tFinal: %d\n\n", tfinal);

    fprintf(f, "Events\n");
    printEvent(f, e1);
    printEvent(f, e2);

    fprintf(f, "\nGrafo Conections\n");
    printGrafoConections(g, f);
    
    fprintf(f, "\n\nTempo Inicio: 0\n");
    save(g, f);
    
    int dt = 1;
    for (double t = dt; t <= tfinal; t += dt) {
        if (empty(q)) break; 
        Event *e = top(q);
        
        while (!empty(q) && getTime(e) <= t){
            srand(time(NULL));
            runEvent(g, e);
            
            pop(q);
            if (getRepeat(e)){
                setTime(e, t + getTimeDelay(e));
                push(q, e);
            }
            e = top(q);          
        }
        if ((int)t%5 == 0){
            fprintf(f, "\nTempo Atual: %0.0lf\n", t);
            save(g, f);
        }
    }

    fprintf(f, "\nTempo final: %d\n", tfinal);
    save(g, f);
    calculatePercentage(g, f);
    fprintf(f, "\nSimulation ended"); 
    
    closeFILE(f);
    freeQueue(q);
    freeGrafo(g);
}

void save(Grafo *g, FILE *f){
    printGrafo(g, f);
}