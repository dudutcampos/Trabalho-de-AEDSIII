#include <stdio.h>

FILE* openFILE(char *path, char *c);
void closeFILE(FILE *f);
void reedEntry(FILE *entrada, int *I, int *tfinal, int *tdI, int *tdR, double *pI, double *pR, char *file);