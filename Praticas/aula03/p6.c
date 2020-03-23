// PROGRAMA p6.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(void)
{
    pid_t pid;
    int i, j, lixo=-1;
    printf("I'm process %d. My parent is %d.\n", getpid(),getppid());
    for (i=1; i<=3; i++) {
        lixo=-1;
        pid = fork();
        if ( pid < 0) {
            printf("fork error");
            exit(1);
        }
        else if (pid == 0) {
            printf("I'm process %d. My parent is %d. I'm going to work for 1 second ...\n", getpid(),getppid());
            sleep(1); // simulando o trabalho do filho
            printf("I'm process %d. My parent is %d. I finished my work\n", getpid(),getppid());
            
        }
        else{
            // a eliminar na alinea c)
            // simulando o trabalho do pai
            for (j=1; j<=10; j++) {
                sleep(1);

                if(lixo == -1 && waitpid(pid, &lixo, WNOHANG) < 0){
                    perror("Wait error");
                    exit(2);
                }
                
                printf("father working ...\n");
            }

            
        }
    }
    exit(0);
}

//5c)  Como o filho nao vai acabar, irá fazer o os 3 ciclos (i=1,2,3). 
//Isso irá aumentar exponencialmente o numero de processos, uma vez que agora o p-filho tb ira gerar processos.