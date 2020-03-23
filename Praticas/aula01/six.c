    // PROGRAMA p6a.c 
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>

#define BUF_LENGTH 256 

int main(int argc, char *argv[]) {   
    FILE *src, *dst;   
    char buf[BUF_LENGTH];

    //verificação da passagem correta dos argumentos
    if (argv[1]==NULL || argv[2]==NULL){
        printf("usage: nome_do_executavel file1 file2\n");
        exit(3);
    }

    if ( ( src = fopen(argv[1], "r" ) ) == NULL )    {

        perror("Erro na linha 12");
        printf("errno: %d\n",errno);
        exit(1);
    }   
    
    if ((dst = fopen( argv[2], "w")) == NULL )   
    {
        perror("Erro na linha 18");
        exit(2);
    }

    while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL )  {  
       fputs( buf, dst );   
    }   
    fclose( src );   
    fclose( dst );   
    exit(0);  // zero é geralmente indicativo de "sucesso" 
}

//6b) motivo: nao existem os ficheiros infile nem outfile