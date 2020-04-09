#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LENGTH 50
#define READ 0
#define WRITE 1

void decompose(char *result[]);

int main(void){
    char *result[20];

    decompose(result);
    FILE *fpin, *fpout;

    int fd[2];
    
    pid_t pid = fork();

    if(pid == 0){
         while(result[i+1] != NULL){

        
    }
    }
    int i=1;
   

    
    


    return 0;
   
}
//cat *.c | grep "Hello"| more

void decompose(char *result[]){
    
    const char *pipe = "|";
    const char *and = ";";

    char *cmd = malloc(MAX_LENGTH * sizeof(char));
    char *cmdTemp = malloc(MAX_LENGTH * sizeof(char));
    fgets(cmd, MAX_LENGTH, stdin);

    //printf("%s\n",cmd);

    strcpy(cmdTemp, cmd);

    int i = 1;

    //para depois poder ler NULL (caso em que nao é pipeline)
    strtok(cmdTemp,pipe);

    if (strtok(NULL,pipe) != NULL){            //caso em que é pipeline
        
        //printf("%s\n",cmd);
        result[0] = strtok(cmd, pipe);
        
        while (( result[i] = strtok(NULL, pipe) ) != NULL)
        {
            i++;    
        }
    }else {                                     //caso em que é ;
        //printf("oi");
        result[0] = strtok(cmd, and);
        
        while ((result[i] = strtok(NULL, and)) != NULL)
        {
            i++;
        }
    }
    
}

void trim(char *array){

}