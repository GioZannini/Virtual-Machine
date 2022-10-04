/*MATR 873810*/
/*P1G37_873810*/

#include "prog.h"

void inizialise(stack *s){/*Inizializza lo stack*/
    s -> sp = 0;
    s -> dim = 16384;/*Stack di 64KB*/
    s -> vett =(int*)malloc(sizeof(int)*(s -> dim));
}

void destroy(stack s){/*Libera lo stack*/
    free(s.vett);
    s.vett = NULL;
}

int push (stack *s, int elem){/*Inserisce il contenuto del registro indicato nello stack*/
    if(s -> sp < s -> dim){/*Gestione stack saturo*/
        (s -> vett)[s -> sp] = elem;
        s -> sp += 1;
        return 0;
    }
    else{
        return 1;
    }
}

int pop(stack *s, int *elem){/*Decrementa sp e copia il valore in posizione sp*/
    if(s -> sp > 0){/*Gestione stack vuoto*/ 
        s -> sp -= 1;
        *elem = (s -> vett)[s -> sp];
        return 0;
    }
    else{
        return 2;
    }
}

void print_stack(stack s, int n){/*Stampa su console il numero indicato di posizioni dello stack*/
    int sp = s.sp;
    int i = 1;
    while(i <= n && sp - i >= 0){
        printf("[sp - %d] -> %d\n",i, (s.vett)[(s.sp) - i]);
        i++;    
    }
}

void display(int pos, int val){/*Stampa su console il valore del registro indicato*/
    printf("[R%d] -> %d\n", pos, val);
}

void mov(int *r, int elem){/*Copia il valore nel registro indicato*/
    *r = elem;
}

int add(int r1, int r2, stack *s){/*Addizione intera. Il risultato viene inserito nello stack.*/
    long val = (long)r1 + (long)r2;
    if(val > 2147483647 || val < -2147483648){/*Gestione oveflow*/
            return 3;
    }
    else{
            return push(s, r1 + r2);
    }
}

int sub(int r1, int r2, stack *s){/*Sottrazione intera. Il risultato viene inserito nello stack.*/
    long val = (long)r1 - (long)r2;
    if(val > 2147483647 || val < -2147483648){/*Gestione overflow*/
        return 3;
    }
    else{     
        return push(s, r1 - r2);
    }
}

int mult(int r1, int r2, stack *s){/*Moltiplicazione intera. Il risultato viene inserito nello stack.*/
    long val = (long)r1 * (long)r2;
    if(val > 2147483647 || val < -2147483648){/*Gestione overflow*/
        return 3;
    }
    else{
        return push(s, r1 * r2);
    }
}

int divi(int r1, int r2, stack *s){/*Divisione intera. Il risultato viene inserito nello stack.*/
    if(r2 != 0){/*Gestione overflow*/
        return push(s, (r1 / r2));
    }
    else{
        return 3;
    }
}

void halt(int *val){/*Termina il programma*/
    *val = 0;
}

void jmp(unsigned int *contatore, int pos){/*Sostituisce il valore di IP con il valore indicato*/
    *contatore = pos;
}

int jpos(unsigned int *contatore, int pos, stack *s){/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento inserito nello stack è maggiore di zero e lo rimuove*/
    if(s -> sp > 0){/*Gestione stack vuoto*/
        s -> sp -= 1;
        if ((s -> vett)[s -> sp] > 0){
            *contatore = pos;
        }    
        else{
           *contatore += 2;
        }
        return 0;
    }
    else{
        return 2;
    }
} 

int jneg(unsigned int *contatore, int pos, stack *s){/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento inserito nello stack è minore di zero e lo rimuove*/
    if(s -> sp > 0){/*Gestione stack vuoto*/
        s -> sp -= 1;
        if ((s -> vett)[s -> sp] < 0){
            *contatore = pos;
        }
        else{
            *contatore += 2;
        }
        return 0;
    }
    else{
        return 2;
    }
}

int jz(unsigned int *contatore, int pos, stack *s){/*Sostituisce il valore di IP con il valore indicato se l’ultimo elemento inserito nello stack è uguale a zero e lo rimuove*/
    if(s -> sp > 0){/*Gestione stack vuoto*/
        s -> sp -= 1;
        if ((s -> vett)[(s -> sp)] == 0){
            *contatore = pos;
        }
        else{
            *contatore += 2;
        }
        return 0;
    }
    else{
        return 2;
    }
}

int call(stack *s, int val, unsigned int *contatore, unsigned int pos){/*Chiamata a subroutine*/
    *contatore = pos;
    return push(s, val);
}

int ret(stack *s, unsigned int *elem){/*Ritorno da chiamata a subroutine, inserire in ip l'ultimo elemento nello stack*/
    if(s -> sp > 0){/*Gestione stack vuoto*/
        s -> sp -= 1;
        *elem = (s -> vett)[s -> sp];
        return 0;
    }
    else{
        return 2;
    }
}

void error(int val, int *run){/*Gestione errori*/
    if(val){
        *run = 0;
        switch(val){
            case 1:
                printf("\tSTACK OVERFLOW\n");
                break;
            case 2:
                printf("\tSTACK UNDERFLOW\n");
                break;
            case 3:
                printf("\tOVERFLOW SU OPERAZIONE ARITMETICA\n");
                break;
         }
    }
}

void esegui(int *istr){     
        stack pila;/*Stack*/  
        int reg[32] = {0}; /*Vettore per i registri*/
        int run = 1;/*Gestisce il ciclo while dello switch*/
        unsigned int ip = 0;/*Contatore istruzioni*/
        inizialise(&pila);/*Creazione stack*/
        assert(pila.vett != NULL);
        while(run){
            switch(istr[ip]){
                case 0: /*HALT*/
                    halt(&run);
                    break;
                case 1: /*DISPLAY*/
                    display(istr[ip + 1], reg[istr[ip + 1]]);
                    ip += 2;
                    break;
                case 2: /*PRINT STACK*/
                    print_stack(pila, istr[ip + 1]);
                    ip += 2;
                    break;
                case 10: /*PUSH*/
                    error(push(&pila, reg[istr[ip + 1]]), &run);
                    ip += 2;
                    break;
                case 11: /*POP*/
                    error(pop(&pila, &(reg[istr[ip + 1]])), &run);
                    ip += 2;
                    break;
                case 12: /*MOV*/
                    mov(&(reg[istr[ip + 1]]), istr[ip + 2]);
                    ip += 3;
                    break;
                case 20: /*CALL*/
                    error(call(&pila, ip + 2, &ip, istr[ip + 1]), &run);
                    break;
                case 21: /*RET*/
                    error(ret(&pila, &ip), &run);
                    break;
                case 22: /*JMP*/
                    jmp(&ip, istr[ip + 1]);
                    break;
                case 23: /*JZ*/
                    error(jz(&ip, istr[ip + 1], &pila), &run);
                    break;
                case 24: /*JPOS*/
                    error(jpos(&ip, istr[ip + 1], &pila), &run);
                    break;
                case 25: /*JNEG*/
                    error(jneg(&ip, istr[ip + 1], &pila), &run);
                    break;
                case 30: /*ADD*/
                    error(add(reg[istr[ip + 1]],reg[istr[ip + 2]], &pila), &run);
                    ip += 3;
                    break;
                case 31: /*SUB*/
                    error(sub(reg[istr[ip + 1]],reg[istr[ip + 2]], &pila), &run);
                    ip += 3;
                    break;
                case 32: /*MUL*/
                    error(mult(reg[istr[ip + 1]],reg[istr[ip + 2]], &pila), &run);
                    ip += 3;
                    break;
                case 33: /*DIV*/
                    error(divi(reg[istr[ip + 1]],reg[istr[ip + 2]], &pila), &run);
                    ip += 3;
                    break;
                default: /*ISTRUZIONE INESISTENTE*/
                    printf("\tISRUZIONE NON VALIDA\n");
                    halt(&run);
                    break;
            }
        }
        destroy(pila);
}
