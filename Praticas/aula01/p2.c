#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_NAME 50     

int main(int argc, char *argv[], char *envp[])  {
    return 0;

}

/*
 char name[MAX_LEN_NAME];
    fgets(name, 50, stdin);
    int t=0;
    scanf("%d", &t);

    //elimina o \n no fim do array
    strtok(name, "\n");

    for (int i=0; i < t; i++){
        printf("Hello %s ! \n", name);   
    }
    return 0; 
*/

/* 5b)
int j=0;
    while(strncmp("USER",envp[j],4)!=0 && envp[j]!=NULL){
        j++;
    }

    char name[strlen(envp[j])-9];
    
    for (int i=9, n=0; envp[j][i]!='\0'; i++,n++){
        name[n]= envp[j][i];
        
    }
    
    printf("Hello %s ! \n", name);   
    
    return 0; 
*/

/* 5c)

    int j=0;
    while(strncmp("USER",envp[j],4)!=0 && envp[j]!=NULL){
        j++;
    }
    
    printf("Hello %s ! \n", getenv("USERNAME"));   
    
    return 0; 
*/

/* 5d) (tem que se criar a variavel de ambiente com export no terminal!)
    
    int j=0;
    while(strncmp("USER",envp[j],4)!=0 && envp[j]!=NULL){
        j++;
    }
    
    printf("Hello %s ! \n", getenv("USER_NAME"));   
    
    return 0; 

*/