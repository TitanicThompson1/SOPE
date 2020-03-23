#include <stdio.h>
#include <stdlib.h>

void exit_handler1(void){
    printf("Executing exit handler 1\n");
    
}

void exit_handler2(void){
    printf("Executing exit handler 2\n");
    exit(0);
}

int main(void){

    printf("Main done!\n");

    atexit(exit_handler1);
    atexit(exit_handler2);
    return 0;
}

//os handlers sao executados por ordem inversa do seu registo
//ao fazer abort(), os handlers nao são chamados
// ao faze exit no fim dos handler, nao muda nada
