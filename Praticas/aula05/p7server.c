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

void exit_routine();

int main(void){

    mkfifo("/tmp/fifo_req", 0660);
    mkfifo("/tmp/fifo_ans", 0660);

    int fdR = open("/tmp/fifo_req", O_RDONLY);
    int fdW = open("/tmp/fifo_ans", O_WRONLY);

    char line[MAX_LINE];

    if(read(fdR, line, MAX_LINE) == -1){
        printf("Error in reading pipe\n");
        close(fdR); close(fdW);
        unlink("/tmp/fifo_req"); unlink("/tmp/fifo_ans");
        exit(1);
    }

    int n1, n2;

    while (n1 != 0 || n2 != 0){

        //Calculations
        struct p2 data;
        data.sum = n1 + n2;
        data.sub = n1 - n2;
        data.mult = n1 * n2;
        if(n2 == 0) data.valid = false;
        else{ 
            data.valid = true;
            data.div = (double) n1 / n2;
        }
        //Writing the data
        write(fdW, &data, sizeof(data));

        //Reading other numbers
        if(read(fdR, line, MAX_LINE) == -1){
            printf("Error in reading pipe\n");
            close(fdR); close(fdW);
            unlink("/tmp/fifo_req"); unlink("/tmp/fifo_ans");
            exit(1);
        }
        sscanf(line, "%d %d", &n1, &n2);

    }

    //Cleanup code
    close(fdR); close(fdW);
    unlink("/tmp/fifo_req"); unlink("/tmp/fifo_ans");
    exit(0);
    
   
}