// PROGRAMA p7.c
#include <stdio.h>

int main(int argc, char *argv[]){

    char prog[20];
    sprintf(prog,"%s.c",argv[1]);
    execlp("gcc","gcc",prog,"-Wall","-o",argv[1],NULL);
    printf("Error: File not found");
    exit(1);
}

//Este programa compila o ficheiro passado como argumento
//execvp("ls", argv);
//execl("/bin/ls", "-laR", argv[1], NULL);
//execlp("ls", "-laR", argv[1], NULL);