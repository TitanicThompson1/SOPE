// PROGRAMA p2.c
#include <stdio.h>
#include <unistd.h>

int main(void) {

    printf("1\n");
    if(fork() > 0) {
        //Processo-Pai
        printf("2\n");
        printf("3\n");
    } else {
        //Processo-Filho
        printf("4\n");
        printf("5\n");
    }
    printf("\n");
    return 0;
}
//Duvida: porque o 1 aparece duas vezes?
/* Exemplo de output:
123
145
É porque o printf põe para um buffer temporario e
o fork faz uma copia desse buffer tambem?
*/
/*
Ao fazer \n o 1 aparece apenas no inicio
Output:

*/