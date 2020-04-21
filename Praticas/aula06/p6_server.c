#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/file.h>
#include <string.h>
#include <wait.h>
#include <stdbool.h>
#include <pthread.h>


#define READ 0
#define WRITE 1
#define MAX_LINE 100
#define MAX_THREADS 4

struct p2
{
    bool valid;      //false->invalido;  true->valido
    int sum, sub, mult;
    double div;

};

void decompose_string(char *line, char *cmd, char * pid);


int num_thread;

int main(void){

    mkfifo("/tmp/fifo_req", 0660);

    int fdR = open("/tmp/fifo_req", O_RDONLY);

    pthread_t tids[MAX_THREADS];

    num_thread = 0;

    char line[MAX_LINE];

    //Reads data from FIFO
    if(read(fdR, line, MAX_LINE) == -1){
        printf("Error in reading pipe\n");
        close(fdR); unlink("/tmp/fifo_req");
        exit(1);
    }

    pthread_create(&tids[num_thread], NULL, processesRequest, line);
    num_thread++;
    
    //Cleanup code
    close(fdR);
    unlink("/tmp/fifo_req");
    exit(0);
    
   
}


void *processesRequest(void *arg){

    pthread_detach(pthread_self());

    char * line = *(char *)arg;
    
    int n1, n2;
    char numbers[MAX_LINE], fifo[MAX_LINE];
    decompose_string(line, numbers, fifo);

    sscanf(numbers, "%d %d", &n1, &n2);

    int fdW = open(fifo, O_WRONLY);   

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
    close(fdW);

    num_thread--;
    return NULL;
}

void decompose_string(char *line, char *cmd, char * pid){
    char temp[MAX_LINE];
    strcpy(temp,line);

    strcpy(pid, strtok(temp, " "));

    strcpy(cmd, strtok(NULL, ""));

}