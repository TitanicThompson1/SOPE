#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 100
#define SIZE_OF_CHAR 1

void decompose_string(char *line, char *cmd, char * pid);

int main(void){

    mkfifo("/tmp/fifo.s", 0644);

    int fdR = open("/tmp/fifo.s", O_RDONLY);
    char line[MAX_LINE+1], cmd[MAX_LINE+1], pid[MAX_LINE], client_fifo[MAX_LINE];
    int n_read, n = 1; 

    n = read(fdR, line, MAX_LINE);
    while(n > 0){

        decompose_string(line, cmd, pid);
        sprintf(client_fifo, "/tmp/fifo.%s", pid);

        int fdW = open(client_fifo, O_WRONLY); 

        FILE * res = popen(cmd, "r");

        while((n_read = fread(line, SIZE_OF_CHAR, MAX_LINE, res)) != 0){
            write(fdW, line, n_read);
        }
        close(fdW);  
        n = read(fdR, line, MAX_LINE);
    }
}

void decompose_string(char *line, char *cmd, char * pid){
    char temp[MAX_LINE];
    strcpy(temp,line);

    strcpy(pid, strtok(temp, " "));

    strcpy(cmd, strtok(NULL, ""));

}
