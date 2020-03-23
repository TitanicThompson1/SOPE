// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    int keep;
    int dest;

    if (argc > 3  || argc < 2) {
        printf("usage: %s dirname OR %s dirname filename\n",argv[0], argv[0]);
        exit(1);
    }

    if(argc == 3){
        
        //É necessário conservar o descritor
        keep = dup(STDOUT_FILENO);
        dest = open(argv[2],O_WRONLY);
        if(dest < 0){
            perror(argv[0]);
            exit(2);
        }
    }
    
    pid=fork();

    if (pid > 0)
        printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
    else if (pid == 0){
        
        if(dup2(dest,STDOUT_FILENO) < 0){
            perror(argv[0]);
            exit(3);
        }

        execlp("ls", "ls", "-laR", argv[1], NULL);
        printf("Command not executed !\n");
        exit(1);
    }

    if(dup2(keep,STDOUT_FILENO) < 0){
        perror(argv[0]);
        exit(4);
    }

    exit(0);
}