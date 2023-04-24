#include <stdio.h>

typedef struct no No;
typedef struct list List;
typedef struct grafo Grafo;
typedef struct edge Edge;

struct grafo{
    int dir;
    int size;
    No **no;
};

struct no{
    int id;
    char state;
    List *l;
};

struct list{
    Edge *begin, *end;
};

struct edge{
    No *no;
    Edge *prox;
};

Grafo* newEmptyGrafo(int n, int dir);
Grafo* newGrafoA(int n, int dir);
Grafo* newGrafoB(int n, int dir);
void chandGrafo1(Grafo *g, int I);
void chandGrafo2(Grafo *g, int I, char c);


No* newEmptyNo(int id);
char getNoState(No *n);
void setNoState(No *n, char c);

List* newEmptyList();
int listEmpty(List *l);
void insertEdge(List *l, No *n);

void printGrafoConections(Grafo *g, FILE *f);
void printGrafo(Grafo *g, FILE *f);
void printList(List *l, FILE *f);
void calculatePercentage(Grafo *g, FILE *f);

void freeGrafo(Grafo *g);
void freeNo(No *no);
void freeLista(List *l);