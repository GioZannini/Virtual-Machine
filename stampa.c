/*MATR 87810*/
/*P1G37_873810*/

#include "prog.h"

void stampa(int *istr, int dim_vett){
        unsigned int ip = 0;/*Contatore istruzioni*/              
        while(ip < (unsigned int)dim_vett){
            switch(istr[ip]){
                case 0: /*HALT*/
                    printf("[%4d] HALT\n", ip);
                    ip +=1;
                    break;
                case 1: /*DISPLAY*/
                    printf("[%4d] DISPLAY R%d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 2: /*PRINT STACK*/
                    printf("[%4d] PRINT STACK %d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 10: /*PUSH*/
                    printf("[%4d] PUSH R%d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 11: /*POP*/
                    printf("[%4d] POP R%d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 12: /*MOV*/
                    printf("[%4d] MOV R%d %d\n", ip, istr[ip + 1], istr[ip + 2]);
                    ip += 3;
                    break;
                case 20: /*CALL*/
                    printf("[%4d] CALL %d\n", ip, istr[ip + 1]); 
                    ip += 2;
                    break;
                case 21: /*RET*/
                    printf("[%4d] RET\n", ip);
                    ip += 1;
                    break;
                case 22: /*JMP*/
                    printf("[%4d] JMP %d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 23: /*JZ*/
                    printf("[%4d] JZ %d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 24: /*JPOS*/
                    printf("[%4d] JPOS %d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 25: /*JNEG*/
                    printf("[%4d] JNEG %d\n", ip, istr[ip + 1]);
                    ip += 2;
                    break;
                case 30: /*ADD*/
                    printf("[%4d] ADD R%d R%d\n", ip, istr[ip + 1], istr[ip + 2]);
                    ip += 3;
                    break;
                case 31: /*SUB*/
                    printf("[%4d] SUB R%d R%d\n", ip, istr[ip + 1], istr[ip + 2]);
                    ip += 3;
                    break;
                case 32: /*MUL*/
                    printf("[%4d] MUL R%d R%d\n", ip, istr[ip + 1], istr[ip + 2]);
                    ip += 3;
                    break;
                case 33: /*DIV*/
                    printf("[%4d] DIV R%d R%d\n", ip, istr[ip + 1], istr[ip + 2]);
                    ip += 3;
                    break;
                default: /*ISTRUZIONE INESISTENTE*/
                    printf("\tISRUZIONE NON VALIDA\n");
                    ip = dim_vett;
                    break;
            }
        }
}
