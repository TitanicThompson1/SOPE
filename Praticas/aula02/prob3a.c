#include <stdio.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
    
    if(argc!=2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE * to_print = fopen(argv[1],"r");
    
    if(to_print==NULL){
        perror(argv[1]);
        return 2;
    }

    char text[BUFFER_SIZE+1];
    size_t bytes_read=1;

    while((bytes_read=fread(text, 1, BUFFER_SIZE, to_print))>0){
        if(bytes_read!=BUFFER_SIZE){
            text[bytes_read+1]='\0';
        }
        printf("%s",text);
    }

    fclose(to_print);

    if(bytes_read<0){
        perror(argv[0]);
        return 3;
    }

    return 0;

}