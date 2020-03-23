#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

int main(void){

    const char *pipe = "|";
    const char *and = ";";

    char *cmd = malloc(MAX_LENGTH * sizeof(char));
    fgets(cmd, MAX_LENGTH, stdin);

    char *token[20];
    int i = 1;

    //para depois poder ler NULL (caso em que nao é pipeline)
    strtok(cmd,pipe);

    if (strtok(NULL,pipe) != NULL){            //caso em que é pipeline

        token[0] = strtok(cmd, pipe);
        
        while ((token[i] = strtok(NULL, pipe)) != NULL)
        {
            i++;    
        }
    }else {                                 //caso em que é ;
        //printf("oi");
        token[0] = strtok(cmd, and);
        
        while ((token[i] = strtok(NULL, and)) != NULL)
        {
            i++;
        }
    }

    //faz print para a consola dos comandos
    for (int j = 0; j < i; j++)
    {
        printf("%s\n", token[j]);
    }
    //printf("%s",token[i]);
}

/*10a)
    char *cmd = malloc(50*sizeof(char));
    fgets(cmd, 50, stdin);
    char *token = strtok(cmd, " ");
    printf("%s \n",token);
    while( (token=strtok(NULL," "))!=NULL){
        printf("%s\n",token);
    }

    return 0;
*/

/*10b)

    
    char *cmd = malloc(50 * sizeof(char));
    fgets(cmd, 50, stdin);

    char *token[20];
    token[0] = strtok(cmd, " ");

    int i = 1;
    while ((token[i] = strtok(NULL, " ")) != NULL)
    {
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        printf("%s\n", token[j]);
    }
*/