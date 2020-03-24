
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[], char* envp[]){
    for(int i=0; i<3; i++){
        printf("%s\n",argv[1]);
        sleep(1);
    }
}