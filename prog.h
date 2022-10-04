/*MATR 873810*/
/*P1G37_873810*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct cella{
    int *vett;
    unsigned int sp;
    unsigned int dim;
};
typedef struct cella stack;

void esegui(int *istr);
void stampa(int *istr, int dim_vett);
int *leggi_file(FILE *frase, int *error, int *dim_vett);
