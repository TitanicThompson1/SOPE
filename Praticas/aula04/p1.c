// PROGRAMA p01a.c 
#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 

void sigint_handler(int signo) {
   printf("In SIGINT handler ...\n"); 
} 

void sigusr1_handler(int signo){
    printf("In SIGUSR1 handler...\n");
}

int main(void) {   
    
    struct sigaction actInt;
    struct sigaction actUsr1;

    actInt.sa_handler = sigint_handler;
    actUsr1.sa_handler = sigusr1_handler;
    
    sigemptyset(&actInt.sa_mask);
    sigemptyset(&actUsr1.sa_mask);

    actInt.sa_flags = 0;
    actUsr1.sa_flags = 0;

    if (sigaction(SIGINT,&actInt, NULL) < 0)   {     
        fprintf(stderr,"Unable to install SIGINT handler\n");     
        exit(1);   
    }   

    if (sigaction(SIGUSR1,&actUsr1, NULL) < 0)   {     
        fprintf(stderr,"Unable to install SIGUSR1 handler\n");     
        exit(2);   
    }   

    printf("Sleeping for 30 seconds ...\n");

    int nsecs = sleep(30);
      
    while (nsecs!=0)
    {
        printf("Received a signal!\n");
        nsecs = sleep(nsecs);
    }
    
    printf("Waking up ...\n");
    exit(0); 
}