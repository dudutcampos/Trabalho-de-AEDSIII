#include "arquivo.h"
#include <stdlib.h>

FILE* openFILE(char *path, char *c){
    FILE *f;
    f = fopen(path, c);// abre o arquivo e retorna NULL em caso de erro.
    
    if(f==NULL){
        printf("Erro ao abrir o arquivo\n");
        getchar();
        exit(1);
    }
    return f;
}

void closeFILE(FILE *f){
    if(fclose(f) != 0){ // fecha o arquivo e retorna 0 em caso de exito;
        printf("Erro ao fechar o arquivo\n");
        getchar();
        exit(1);
    }
}

void reedEntry(FILE *entrada, int *I, int *tfinal, int *tdI, int *tdR, double *pI, double *pR, char *file){
    fscanf(entrada, "%s", file);
    fscanf(entrada, "%s %d", file, I);
    fscanf(entrada, "%s %lf", file, pI);
    fscanf(entrada, "%s %lf", file, pR);
    fscanf(entrada, "%s %d", file, tdI);
    fscanf(entrada, "%s %d", file, tdR);
    fscanf(entrada, "%s %d", file, tfinal);
    fscanf(entrada, "%s", file);
    //printf("%d, %lf, %lf, %d, %d, %d, %s\n", *I, *pI, *pR, *tdI, *tdR, *tfinal, file);
}