#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>

int v = 0;
bool up= true;

void sigusr_handler(int signo){
    if(signo == SIGUSR1){
        up=true;
    }else if(signo == SIGUSR2){
        up = false;
    }
}

int main(void){

    struct sigaction action;
    action.sa_handler = sigusr_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGUSR1, &action, NULL)){
        printf("Something bad happened while installing the SIGUSR1 handler!\n");
        exit(1);
    }

    if (sigaction(SIGUSR2, &action, NULL)){
        printf("Something bad happened while installing the SIGUSR2 handler!\n");
        exit(2);
    }

    pid_t pid = fork();
    

    if(pid == 0){   //Processo-filho

        srand(time(0));
        pid_t parent = getppid();
        int signo = rand() % 2;
        while(1){
            sleep(1);
            if(signo == 0){
                kill(parent, SIGUSR1);
            }else if( signo == 1) {
                kill(parent, SIGUSR2);
            }
            signo = rand() % 2;
            
        }

    }else{
        int i = 0;

        while(i!=50){
            
            //output para a consola
            printf("%d\n", v);

            //determina se cresce ou decresce
            if(up) v++;
            else v--;

            //espera 1 sec
            sleep(1);
            i++;
        }
        kill(pid, SIGTERM);
    }

    

}

/*a)
struct sigaction action;
    action.sa_handler = sigusr_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGUSR1, &action, NULL)){
        printf("Something bad happened while installing the SIGUSR1 handler!\n");
        exit(1);
    }

    if (sigaction(SIGUSR2, &action, NULL)){
        printf("Something bad happened while installing the SIGUSR2 handler!\n");
        exit(2);
    }

    
    while(1){
        printf("%d\n", v);
        sleep(1);
        if(up) v++;
        else v--;
    }

*/