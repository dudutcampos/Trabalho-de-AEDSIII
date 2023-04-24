#include "grafo.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Grafo* newEmptyGrafo(int n, int dir){
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    g->no = (No**)malloc(n*sizeof(No*));
    g->size = n;
    g->dir = dir;

    for (int i = 0; i < n; i++){ 
        No *no = newEmptyNo(i);
        g->no[i] = no; 
    }
    return g; 
}

// funciona apenas par 20 elementos.
Grafo* newGrafoA(int n, int dir){
    Grafo *g = newEmptyGrafo(n, dir);
    
    //linhas
    for (int i = 1; i < g->size; i++){
        if(i == 4 || i == 8 || i == 12 || i == 16) continue;
        insertEdge(g->no[i-1]->l, g->no[i]);
        if(!g->dir){
            insertEdge(g->no[i]->l, g->no[i-1]);    
        }
    }
    //colunas    
    for (int i = 1; i+3 < g->size; i++){
        insertEdge(g->no[i-1]->l, g->no[i+3]);
        if(!g->dir){
            insertEdge(g->no[i+3]->l, g->no[i-1]);    
        }
    }
    return g;
}

// funciona apenas par 20 elementos.
Grafo* newGrafoB(int n, int dir){
    Grafo *g = newEmptyGrafo(n, dir);

    //grupo 1 = 4 pessoas
    insertEdge(g->no[0]->l, g->no[1]);
    insertEdge(g->no[1]->l, g->no[0]);
    
    insertEdge(g->no[0]->l, g->no[2]);
    insertEdge(g->no[2]->l, g->no[0]);

    insertEdge(g->no[0]->l, g->no[3]);
    insertEdge(g->no[3]->l, g->no[0]);

    insertEdge(g->no[1]->l, g->no[3]);
    insertEdge(g->no[3]->l, g->no[1]);
    
    insertEdge(g->no[2]->l, g->no[3]);
    insertEdge(g->no[3]->l, g->no[2]);
    
    //grupo 2 = 5 pessoas
    insertEdge(g->no[4]->l, g->no[5]);
    insertEdge(g->no[5]->l, g->no[4]);

    insertEdge(g->no[5]->l, g->no[6]);
    insertEdge(g->no[6]->l, g->no[5]);

    insertEdge(g->no[4]->l, g->no[6]);
    insertEdge(g->no[6]->l, g->no[4]);

    insertEdge(g->no[6]->l, g->no[8]);
    insertEdge(g->no[8]->l, g->no[6]);

    insertEdge(g->no[7]->l, g->no[4]);
    insertEdge(g->no[4]->l, g->no[7]);

    insertEdge(g->no[7]->l, g->no[8]);
    insertEdge(g->no[8]->l, g->no[7]);

    //grupo 3 = 4 pessoas
    insertEdge(g->no[9]->l, g->no[10]);
    insertEdge(g->no[10]->l, g->no[9]);

    insertEdge(g->no[9]->l, g->no[11]);
    insertEdge(g->no[11]->l, g->no[9]);

    insertEdge(g->no[10]->l, g->no[12]);
    insertEdge(g->no[12]->l, g->no[10]);

    insertEdge(g->no[11]->l, g->no[12]);
    insertEdge(g->no[12]->l, g->no[11]);

    insertEdge(g->no[9]->l, g->no[12]);
    insertEdge(g->no[12]->l, g->no[9]);

    //grupo 4 = 4 pessoas
    insertEdge(g->no[13]->l, g->no[14]);
    insertEdge(g->no[14]->l, g->no[13]);
    
    insertEdge(g->no[13]->l, g->no[15]);
    insertEdge(g->no[15]->l, g->no[13]);

    insertEdge(g->no[15]->l, g->no[16]);
    insertEdge(g->no[16]->l, g->no[15]);

    insertEdge(g->no[15]->l, g->no[14]);
    insertEdge(g->no[14]->l, g->no[15]);

    //grupo 5 = 3 pessoas
    insertEdge(g->no[17]->l, g->no[18]);
    insertEdge(g->no[18]->l, g->no[17]);

    insertEdge(g->no[17]->l, g->no[19]);
    insertEdge(g->no[19]->l, g->no[17]);
    
    //junta grupos
    insertEdge(g->no[3]->l, g->no[10]);
    insertEdge(g->no[10]->l, g->no[3]);

    insertEdge(g->no[3]->l, g->no[17]);
    insertEdge(g->no[17]->l, g->no[3]);

    insertEdge(g->no[7]->l, g->no[10]);
    insertEdge(g->no[10]->l, g->no[7]);

    insertEdge(g->no[7]->l, g->no[13]);
    insertEdge(g->no[13]->l, g->no[7]);

    insertEdge(g->no[17]->l, g->no[13]);
    insertEdge(g->no[13]->l, g->no[17]);

    return g;
}

//mudando o estado de 1 no do grafo;
void chandGrafo1(Grafo *g, int I){
    g->no[I]->state = 'I';
}

//mudando estado de I nos alenatorios do Grafo.
void chandGrafo2(Grafo *g, int I, char c){
    int v[20];
    for (int i = 0; i < g->size; i++){
        v[i] = i;
    }

    srand(time(NULL));  
    for (int i = 0; i < g->size; i++)
	{
		int r = rand() % g->size;

		int temp = v[i];
		v[i] = v[r];
		v[r] = temp;
	}
    
    for (int i = 0; i < I; i++){
        g->no[v[i]]->state = c;
    }
}

No* newEmptyNo(int id){
    No *no = (No*)malloc(sizeof(No));
    no->id = id;
    no->state = 'S';
    no->l = newEmptyList();
    return no;
}

char getNoState(No *n){
    return n->state;
}

void setNoState(No *n, char c){
    n->state = c;
}

List* newEmptyList(){
    List *l = (List*)malloc(sizeof(List));
    l->begin = (Edge*)malloc(sizeof(Edge));
    l->begin->no = NULL;
    l->begin->prox = NULL;
    l->end = l->begin;
    return l;
}

int listEmpty(List *l){
    if(l->begin == l->end){
        return 1;
    }
    return 0;
}

void insertEdge(List *l, No *n){
    l->end->prox = (Edge*)malloc(sizeof(Edge));
    l->end = l->end->prox;
    l->end->prox = NULL;
    l->end->no = n;
}

void printGrafoConections(Grafo *g, FILE *f){
    for (int i = 0; i < g->size; i++){
        fprintf(f, "%d: {", g->no[i]->id);
        printList(g->no[i]->l, f);
    }
}

void printGrafo(Grafo *g, FILE *f){
    fprintf(f, "\n");
    for (int i = 0; i < g->size; i++){
        fprintf(f, "%d ->  %c\n", g->no[i]->id, g->no[i]->state);
    }
    fprintf(f, "\n");    
}

void printList(List *l, FILE *f){
    Edge *aux = l->begin->prox;
    while (aux != NULL){
        if(aux->prox == NULL)
            fprintf(f, "%d", aux->no->id);
        else
            fprintf(f, "%d, ", aux->no->id);
        aux = aux->prox;
    }
    fprintf(f, "}\n");
}

void calculatePercentage(Grafo *g, FILE *f){
    double R = 0, S = 0, I = 0, RI = 0;
    for (int i = 0; i < g->size; i++){
        switch (g->no[i]->state)
        {
        case 'R':
            R++;
            break;
        case 'S':
            S++;
            break;
        case 'I':
            I++;
            break;
        default:
            break;
        }       
    }
    RI = R + I;
    fprintf(f, "\nS: %0.0lf, I: %0.0lf, R: %0.0lf, IR: %0.0lf\n", S, I, R, RI);
    R = R/20.00;
    S = S/20.00;
    I = I/20.00;
    RI = RI/20.00;
    fprintf(f, "S: %0.2lf, I: %0.2lf, R: %0.2lf, IR: %0.2lf\n", S, I, R, RI);

}

void freeGrafo(Grafo *g){
    for (int i = 0; i < g->size; i++){
        freeNo(g->no[i]);
    }
    free(g->no);
    free(g);
    
}

void freeNo(No *no){
    freeLista(no->l);
    free(no);
}

void freeLista(List *l){
    Edge *aux = l->begin;
    Edge *aux1 = l->begin->prox;
    while (aux != NULL){
        free(aux);
        aux = aux1;
        if(aux1 != NULL){
            aux1 = aux1->prox;
        }
    }
    free(l);
}