#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <string.h> 

#define MAX_LENGTH 50

int main(void){

    int file = open("class.txt",O_WRONLY | O_CREAT, 0644);

    if (file == -1) { perror("prob4"); return 1;}

    char *line = malloc(MAX_LENGTH+1);

    write(STDIN_FILENO, "To exit introduce E\n", sizeof("To exit introduce E\n"));
    
    ssize_t bytes_read = read(STDIN_FILENO, line, MAX_LENGTH);
    
    while(line[0]!='\n'){
        
        //Escreve no ficheiro
        if(write(file,line,bytes_read)==-1){
            close(file);
            perror("prob4");
            return 2;
        }
               
        //Lê uma linha
        bytes_read = read(STDIN_FILENO, line, MAX_LENGTH);

    }
    close(file);
    return 0;
}