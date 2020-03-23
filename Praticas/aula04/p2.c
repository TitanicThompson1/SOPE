// PROGRAMA p02a.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

void sigint_handler(int signo) {   
    printf("Entering SIGINT handler ...\n");   
    sleep(10);   
    printf("Exiting SIGINT handler ...\n");  
}

void sigterm_handler(int signo){
    printf("Entering SIGTERM handler ...\n");   
    sleep(10);   
    printf("Exiting SIGTERM handler ...\n");  
}


int main(void) {  
    
    //Para o interruption
    struct sigaction actionInt;  
    actionInt.sa_handler = sigint_handler;  
    sigemptyset(&actionInt.sa_mask);  
    actionInt.sa_flags = 0;  

    //Para o Termination
    struct sigaction actionTerm;
    actionTerm.sa_handler = sigterm_handler;
    sigemptyset(&actionTerm.sa_mask);
    actionTerm.sa_flags = 0;

    if (sigaction(SIGINT,&actionInt,NULL) < 0)  {
        fprintf(stderr,"Unable to install SIGINT handler\n");       
        exit(1);
    }

    if (sigaction(SIGTERM, &actionTerm, NULL) < 0){
        fprintf(stderr, "Unable to install SIGTERM handler\n");
        exit(2);
    }

    printf("Try me with CTRL-C ...\n");  
    while(1) 
        pause();  
    
    exit(0); 
}

//b) apesar de estar dentro do handler, o processo recebeu o sinal e terminou o processo.
// logo, um processo pode receber mais do que um sinal diferente ao mesmo tempo