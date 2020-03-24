#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>

#define READ 0
#define WRITE 1
#define MAX_LINE 1024

struct p2
{
    char type;      //0->invalido;  1->inteiro; 2->decimal
    int inteiro;
    double decimal;

};


int main(void){

    int fd[2], fd2[2];

    if(pipe(fd) < 0){
        printf("Pipe error\n");
        exit(1);
    }

    if(pipe(fd2) < 0){
        printf("Pipe error\n");
        exit(1);
    }


    pid_t pid = fork();

    if(pid > 0){           //Processo-pai
        
        close(fd[READ]);
        close(fd2[WRITE]);

        int  x, y, status, res;
        struct p2 dados;

        scanf("%d", &x);
        scanf("%d", &y);
        
        write(fd[WRITE], &x, sizeof(int));
        write(fd[WRITE], &y, sizeof(int));

        read(fd2[READ], &res, sizeof(int));
        printf("Sum: %d\n", res);

        read(fd2[READ], &res, sizeof(int));
        printf("Subtraction: %d\n", res);

        read(fd2[READ], &res, sizeof(int));
        printf("Multiplication: %d\n", res);

        read(fd2[READ], &dados, sizeof(struct p2));
        if(dados.type=='0'){
            printf("Divison: NaN\n");   

        }else if(dados.type == '1'){
           printf("Divison: %d\n", dados.inteiro);
             
        }else if (dados.type =='2'){
           printf("Divison: %f\n", dados.decimal);  
        }

        wait(&status);

        exit(0);
    }else {         //Processo-Filho

        close(fd[WRITE]);
        close(fd2[READ]);

        int x=0, y=0;
        struct p2 dados; 
        int simple_data;

        read(fd[READ], &x, sizeof(int));
        read(fd[READ], &y, sizeof(int));

        simple_data = x+y;
        write(fd2[WRITE], &simple_data, sizeof(int));

        simple_data = x-y;
        write(fd2[WRITE], &simple_data, sizeof(int));

        simple_data = x*y;
        write(fd2[WRITE], &simple_data, sizeof(int));

        if(y==0){
            dados.type='0';
            write(fd2[WRITE], &dados, sizeof(dados));    
        }else if(x%y==0){
            dados.type='1';
            dados.inteiro = x/y;
            write(fd2[WRITE], &dados, sizeof(dados));
        }else {
            dados.type='2';
            dados.decimal = (double) x/y;
            write(fd2[WRITE], &dados, sizeof(dados));
        }
        exit(0);
        
    }
}