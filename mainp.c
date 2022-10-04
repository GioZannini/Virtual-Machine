/*MATR 873810*/
/*P1G37_873810*/

#include "prog.h" 
 
int main(int argc, char **argv){  
    if(argc == 3){/*Gestisce il caso in cui non vengano immessi i dati corretti*/ 
        FILE *frase; 
        frase = fopen(argv[1], "r");
        if(frase != NULL){/*Gestione apertura del file da leggere*/ 
            int verifica_err;/*Controlla il caso di errori nella creazione del vettore di istruzioni*/
            int dim_vett;/*Dimensione del vettore istr*/
            int *istr;/*Vettore di istruzioni*/
            istr = leggi_file(frase, &verifica_err, &dim_vett);/*Creazione del vettore di istruzioni e verifica di eventuali errori*/
            if(!verifica_err && (!strcmp(argv[2], "esegui"))){/*Esegue*/   
                esegui(istr);
            }
            else if(!verifica_err && (!strcmp(argv[2], "stampa"))){/*Stampa*/
                stampa(istr, dim_vett);
            }
            free(istr);                    
        }
        else{
            printf("\tFILE NON ESISTENTE\n");
        }
    }
    else{
        printf("\tARGOMENTI INSERITI SCORRETTAMENTE\n\tEsempio: ./eseguibile file_testo.cvm esegui/stampa\n");
    }
    return 0;
}
