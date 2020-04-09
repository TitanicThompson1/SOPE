#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Usage: <executavel> <dir> <pattern>\n");
        exit(1);
    }

    int fd[2];

    if(pipe(fd) == -1){
        perror(argv[0]);
        exit(2);
    }
    
    pid_t pid = fork();
    if(pid == 0){       //Child-process
        close(fd[WRITE]);

        //Redirects standard input to pipe exit (the program now reads from pipe)
        dup2(fd[READ], STDIN_FILENO);
        int fd2[2];


        if(pipe(fd2) == -1){
            perror(argv[0]);
            exit(3);
        }
        
        pid_t pid2 = fork();
        if(pid2 == 0){      //Child-process
            close(fd2[WRITE]);

            //Redirects standard input to pipe exit
            dup2(fd[READ], STDIN_FILENO);

            //Executes sort
            execlp("sort", "sort", NULL);
            printf("Error in executing execlp\n");
            exit(4);
        }
        close(fd2[READ]);

        //Redirects standard output to pipe entry
        dup2(fd2[WRITE], STDOUT_FILENO);

        //Executes grep
        execlp("grep", "grep", argv[2], NULL);
        printf("Error in executing execlp\n");
        exit(5);

    }
    close(fd[READ]);

    //Redirects standard output to pipe entry
    dup2(fd[WRITE], STDOUT_FILENO);

    //Executes ls
    execlp("ls", "ls", argv[1], "-laR", NULL);

    printf("Error in executing execlp\n");
    close(fd[WRITE]);
    exit(6);

}