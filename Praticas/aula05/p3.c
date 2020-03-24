#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LEN 50
#define MAX_LINE 1024

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    char line[MAX_LINE];

    FILE *fp = popen("sort", "w");
    FILE *fs = fopen(argv[1],"r");


    

    while(fgets(line, MAX_LINE, fs) != NULL){
        fputs(line,fp);
    }

    pclose(fp);

    exit(0);
}
/* Outra maneira de fazer (esta maneira nao esta de acordo com o enunciado)
 if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    char cmd[MAX_LEN], line[MAX_LINE];

    sprintf(cmd, "sort %s", argv[1]);

    FILE *fp = popen(cmd, "r");

    while( fgets(line, MAX_LINE, fp) != NULL){
        fputs(line,stdout);
    }
    
    pclose(fp);

    exit(0);
*/

/* Versão sem cat

    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    char line[MAX_LINE];

    FILE *fp = popen("sort", "w");
    FILE *fs = fopen(argv[1],"r");

    while(fgets(line, MAX_LINE, fs) != NULL){
        fputs(line,fp);
    }

    pclose(fp);

    exit(0);
*/