#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

void child_handler(int signo);

int main(int argc, char * argv[], char *envp[]){

    if(argc < 3){
        printf("Usage: limit <t> <prog> <prog_args>\n");
        exit(3);
    }

    struct sigaction act;
    act.sa_handler = child_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(SIGCHLD, &act, NULL) < 0){
        printf("Error in installing signal handler!\n");
        exit(1);
    }

    int time = 0;
    //Converting string to number
    sscanf(argv[1], "%d", &time);

    pid_t pid = fork();
    if(pid == 0){       //Child Process
        execvp(argv[2], &argv[2]);
        printf("Error in running %s\n", argv[2]);
        exit(2);
    }
    
    sleep(time);
    kill(pid, SIGKILL);
    printf("Program didnt end in time!\n");
    exit(0);

}

void child_handler(int signo){
    int status;
    waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status)){
        printf("Program ended within time!\n");
        exit(0);
    }
}