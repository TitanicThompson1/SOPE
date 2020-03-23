// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2) {
        printf("usage: %s dirname\n",argv[0]);
        exit(1);
    }
    pid=fork();
    
    if (pid > 0)
        printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
    else if (pid == 0){
        char *new_argv[] = {"ls", "-laR", argv[1], NULL};
        execve("/bin/ls", new_argv, envp);
        printf("Command not executed !\n");
        exit(1);
    }
    printf("\n");
    exit(0);
}

//execl("/bin/ls", "-laR", argv[1], NULL);

//execlp("ls", "ls", "-laR", argv[1], NULL);

//char *new_argv[] = {"ls", "-laR", argv[1], NULL};
//execvp("ls", new_argv);

//char *new_argv[] = {"ls", "-laR", argv[1], NULL};
//execv("/bin/ls", new_argv);

//char *new_argv[] = {"ls", "-laR", argv[1], NULL};
//execve("/bin/ls", new_argv, envp);
