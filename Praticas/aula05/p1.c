#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>

#define READ 0
#define WRITE 1
#define MAX_LINE 1024

struct Op
{
    int x,y;
};


int main(void){

    int fd[2];

    if(pipe(fd) < 0){
        printf("Pipe error\n");
        exit(1);
    }

    pid_t pid = fork();

    if(pid > 0){           //Processo-pai
        close(fd[READ]);
        int  x, y, status;
        scanf("%d", &x);
        scanf("%d", &y);
        
        write(fd[WRITE], &x, sizeof(int));
        write(fd[WRITE], &y, sizeof(int));

        wait(&status);

        exit(0);
    }else {         //Processo-Filho

        close(fd[WRITE]);
        int x=0, y=0;

        read(fd[READ], &x, sizeof(int));
        read(fd[READ], &y, sizeof(int));

        printf("Sum: %d\n", x+y);
        printf("Subtraction: %d\n", x-y);
        printf("Multiplication: %d\n", x*y);

        if(y==0){
            printf("Division: NaN\n");
        }else{
            printf("Division: %f\n", (double) x/y);
        }
        exit(0);
        
    }
}
/*a)
 int fd[2];

    if(pipe(fd) < 0){
        printf("Pipe error\n");
        exit(1);
    }

    pid_t pid = fork();

    if(pid > 0){           //Processo-pai
        close(fd[READ]);
        int  x, y, status;
        scanf("%d", &x);
        scanf("%d", &y);
        
        write(fd[WRITE], &x, sizeof(int));
        write(fd[WRITE], &y, sizeof(int));

        wait(&status);

        exit(0);
    }else {         //Processo-Filho

        close(fd[WRITE]);
        int x=0, y=0;

        read(fd[READ], &x, sizeof(int));
        read(fd[READ], &y, sizeof(int));

        printf("Sum: %d\n", x+y);
        printf("Subtraction: %d\n", x-y);
        printf("Multiplication: %d\n", x*y);

        if(y==0){
            printf("Division: NaN\n");
        }else{
            printf("Division: %f\n", (double) x/y);
        }
        exit(0);
        
    }*/

/*b)

    int fd[2];

    if(pipe(fd) < 0){
        printf("Pipe error\n");
        exit(1);
    }

    pid_t pid = fork();

    if(pid > 0){            //Processo-pai
        close(fd[READ]);

        int status;
        struct Op op1;

        scanf("%d %d", &op1.x, &op1.y);
        
        write(fd[WRITE], &op1, sizeof(op1));

        wait(&status);

        exit(0);

    }else {                 //Processo-Filho

        close(fd[WRITE]);

        struct Op op1;

        read(fd[READ], &op1, sizeof(struct Op));

        printf("Sum: %d\n", op1.x+op1.y);
        printf("Subtraction: %d\n", op1.x-op1.y);
        printf("Multiplication: %d\n", op1.x*op1.y);

        if(op1.y==0){
            printf("Division: NaN\n");
        }else{
            printf("Division: %f\n", (double) op1.x/op1.y);
        }
        exit(0);
        
    }
*/


/*c)

    int fd[2];
   
    char line[MAX_LINE];

    if(pipe(fd) < 0){
        printf("Pipe error\n");
        exit(1);
    }

    pid_t pid = fork();

    if(pid > 0){           //Processo-pai
        close(fd[READ]);
        int  n, status;
        fgets(line, MAX_LINE, stdin);
        
        n = strlen(line);
        
        write(fd[WRITE], line, n);

        wait(&status);

        exit(0);
    }else {         //Processo-Filho

        close(fd[WRITE]);
        int x=0, y=0;

        read(fd[READ], line, MAX_LINE);
        

        sscanf(line, "%d %d", &x, &y);

        printf("Sum: %d\n", x+y);
        printf("Subtraction: %d\n", x-y);
        printf("Multiplication: %d\n", x*y);

        if(y==0){
            printf("Division: NaN\n");
        }else{
            printf("Division: %f\n", (double) x/y);
        }
        exit(0);
        
    }
}

*/