// PROGRAMA p04a.c
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    

    pid_t pid;
    int i, n, status;
    for (i=1; i<=3; i++) {
        pid=fork();
        if (pid == 0){
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
            sleep(i*7); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
            exit(0);
        }
    }
    
    for (i=1 ;i<=3; i++ ) {
        printf("PARENT: working hard (task no. %d) ...\n",i);
        n=20; while((n=sleep(n))!=0);
       
        printf("PARENT: end of task no. %d\n",i);
        printf("PARENT: waiting for child no. %d ...\n",i);


        pid = waitpid(-1,&status,WNOHANG);
        while (pid != 0 && pid != -1){
             printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));
            pid = waitpid(-1,&status,WNOHANG);
        }
           
        
    }
    exit(0);
}

//Alinea a). O problema é que o pai apenas recolhe o codigo de terminação de um dos filhos. Logo, alguns filhos ficaram zombies durante um periodo de tempo maior
