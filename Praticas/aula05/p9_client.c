#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 100

int main(void){

    char fifo[30];
    sprintf(fifo, "/tmp/fifo.%d", getpid());

    mkfifo(fifo,0644);

    int fdW = open("/tmp/fifo.s", O_WRONLY);
    

    char line[MAX_LINE+1];

    sprintf(line, "%d ls", getpid());

    write(fdW,line, strlen(line));

    int fdR = open(fifo, O_RDONLY);
    int n_read;

    while(n_read = read(fdR, line, MAX_LINE), n_read > 0){
        write(STDOUT_FILENO, line, n_read);
    }

    close(fdR); unlink(fifo);
}