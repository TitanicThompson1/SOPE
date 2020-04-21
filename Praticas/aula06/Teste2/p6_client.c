#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/file.h>
#include <string.h>
#include <wait.h>
#include <stdbool.h>

#define READ 0
#define WRITE 1
#define MAX_LINE 100

struct p2
{
    bool valid;      //false->invalido;  true->valido
    int sum, sub, mult;
    double div;

};

void print_result(struct p2 res);

int main(void){

    char fifo[30];
    sprintf(fifo, "/tmp/fifo_ans_%d", getpid());
    mkfifo(fifo, 0644);

    int fdW = open("/tmp/fifo_req", O_WRONLY), fdR;

    char line[MAX_LINE];
    char req[MAX_LINE];
    struct p2 res;

    while(1){

        //Reads form standard input
        read(STDIN_FILENO, line, MAX_LINE);

        //Builds up request
        sprintf(req, "%s %s", fifo, line);

        //Writes request on fifo
        write(fdW, req, MAX_LINE);
        
        fdR = open(fifo, O_RDONLY);
        
        //Reads response
        if(read(fdR, &res, sizeof(struct p2)) == 0){
            break;
        }

        //Prints response
        print_result(res);

    }
    close(fdW); close(fdR);
    unlink(fifo);
    exit(0);
}

void print_result(struct p2 res){

    printf("Sum: %d\n", res.sum);

    printf("Subtraction: %d\n", res.sub);

    printf("Multiplication: %d\n", res.mult);

    if(res.valid)
        printf("Divison: %f\n", res.div);
    else
        printf("Divison: NaN\n");
}