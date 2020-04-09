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
#define MAX_LINE 1024

struct p2
{
    bool valid;      //false->invalido;  true->valido
    int sum, sub, mult;
    double div;

};

void print_result(struct p2 res);

int main(void){


    int fdW = open("/tmp/fifo_req", O_WRONLY);
    int fdR = open("/tmp/fifo_ans", O_RDONLY);

    char line[MAX_LINE];
    struct p2 res;

    while(1){

        read(STDIN_FILENO, line, MAX_LINE);

        write(fdW, line, MAX_LINE);

        if(read(fdR, &res, sizeof(struct p2)) == 0){
            break;
        }

        print_result(res);

    }
    close(fdW); close(fdR);
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