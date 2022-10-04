/*MATR 873810*/
/*P1G37_873810*/

#include "prog.h"

int control_str(char *str, int val){/*Verifica la composizione della stringa acquisita dal getline*/
    if(val != -1){/*Verifica il caso in cui il getline non abbia letto nulla*/
        int contr = 0;/*Caso stringa vuota o con commento*/
        while(*str != ';' && *str != '\n' && *str != '\r' && contr != 1){
            if((*str >= 33 && *str < 43) || *str == 58 || *str == 44 || *str == 46 || *str == 47 || (*str >= 60 && *str <= 126))/*Verifica il caso in cui sia stato letto un carattere*/
                contr = 1;
            else if(*str >= '0' && *str <= '9'){/*Verfica il caso in cui nella stringa ci sia un numero*/
                if(contr == 2 && *(str - 1) == ' ')/*Verifica il caso in cui ci sia più di un numero nella stringa*/
                    contr = 1;
                else
                    contr = 2;
            }
            str++;
        }
        return contr;
    }
    else
        return -1;/*Caso in cui il getline abbia finito di leggere il file*/
}

int find_error(int val, int riga){/*Mi gestisce i casi d'errore possibili in fase di lettura del file*/
    if(val == -1)/*In questo caso vuol dire che il file letto è stato scritto rispettando lo standard imposto*/
        return 0;
    else{/*Il file letto non è conforme allo standard*/
        switch(val){
                case 1:
                    printf("\tERRORE NELLA CREAZIONE DEL VETTORE ALLA RIGA %d\n", riga);
                    break;
                case 3:
                    printf("\tERRORE, IL NUMERO DELLE LINEE NON E' SUFFICIENTE\n");
                    break;
         }
        return 1;/*Torna uno in caso di errore*/
    }
}

int *leggi_file(FILE *frase, int *error, int *dim_vett){
    char *punta;/*Puntatore al primo byte della stringa*/
    int *istr;/*Vettore istruzioni*/
    size_t dim_frase = 10;/*Dimensione per getline*/
    int conta = 0;/*Contatore vettore*/
    int first_entry = 1;/*Serve per gestire la dimensione del vettore*/
    int errore_riga = 0;/*In caso di errore nella creazione del vettore mi restituisce la riga*/
    *dim_vett = 0;/*Dimensione vettore istruzioni*/
    *error = 0; /*Controlla il getline e i vari casi d'errore*/
    punta = (char*)malloc(sizeof(char) * dim_frase);
    assert(punta != NULL);
    while(*error != -1 && *error != 1 && *error != 3){/*-1 fine file, 1 inserito carattere non corretto nel file, 3 dimensione vettore insufficiente*/
        errore_riga++;
        *error = getline(&punta, &dim_frase, frase);                         
        *error = control_str(punta, *error);/*Controllo della stringa*/
        if(*error == 2){
            if(first_entry){/*Entra solo la prima volta per determinare la grandezza del vettore per le istruzioni e lo crea*/
                sscanf(punta, "%d", dim_vett);/*Lettura della dimensione del vettore da creare*/
                istr = (int*)malloc(sizeof(int) * (*dim_vett));
                assert(istr != NULL);
                first_entry = 0;/*Portandolo a zero mi assicuro che non entri più in questo if*/
            }
            else{
                if(conta < *dim_vett){/*Verifica che il numero di linee sia sufficiente*/
                    sscanf(punta, "%d", &istr[conta]);/*Inserimento degli elementi dentro al vettore per le istruzioni*/                                    
                    conta++;
                }
                else
                    *error = 3;/*Codice d'errore nel caso in cui il vettore non sia abbastanza grande*/
            }
        }
    }
    fclose(frase);
    free(punta);
    *error = find_error(*error, errore_riga);/*Verifica se c'è un errore*/
    return istr;
}
