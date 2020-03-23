
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <fcntl.h>


#define MAX_LEN 20

int main(int argc, char * argv[]){
    
    int bytes_read, keep=0, dest=0,k=100;

    while(1){
        
        fflush(stdout);

        write(STDOUT_FILENO,"minish >",9);
        char *cmd= malloc(MAX_LEN+1);



        bytes_read = read(STDIN_FILENO,cmd,20);

        //Checks for errors
        if(bytes_read == -1){
            perror(argv[0]);
            write(STDOUT_FILENO,"\n",2);
            continue;
        }
        
        cmd[bytes_read] = '\0';

        //Removes ending \n
        cmd = strtok(cmd,"\n");

        //Verifies if user didnt write a command
        if(cmd==NULL){
            continue;
        }

        //Parse the string
        char *subcmd[4]; int i=1;

        subcmd[0] = strtok(cmd, " ");
      
        while ((subcmd[i] = strtok(NULL, " ")) != NULL && i < 4){
            i++;
        }

        //Do commands
        //Checks if user wants to exit
        if(strcmp(subcmd[0],"quit") == 0){
            break;
        }

        pid_t pid;

        if((pid = fork()) < 0){     //Erro
            perror(argv[0]);
            exit(1);
        }else if(pid==0){           //Filho

            k=0;
            //Verifica se tem o -o
            while(subcmd[k] != NULL && strcmp(subcmd[k],"-o")!=0){
                k++;
            }

            //Se tiver
            if(k < i && subcmd[k+1]!=NULL){
                keep = dup(STDOUT_FILENO);
                dest = open(subcmd[k+1],O_WRONLY);
                dup2(dest,STDOUT_FILENO);
                subcmd[k]=NULL;
            }

            execvp(subcmd[0],subcmd);
            write(STDOUT_FILENO, "Error in trying to execute command\n",36);
            exit(2);
        }
        
        int status;
        wait(&status);
        
        if(k < i) {
            dup2(keep,STDOUT_FILENO);
            close(dest);
        }

    }
    return 0;
}