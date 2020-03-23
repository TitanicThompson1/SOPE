#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
 #include <sys/stat.h> 
 #include <fcntl.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
    
    if(argc!=2 && argc != 3){
        printf("Usage: %s <filename> OR %s <filename1> <filename2>\n", argv[0],argv[0]);
        return 1;
    }

    FILE * to_print = fopen(argv[1],"r");
    
    if(to_print==NULL){
        perror(argv[1]);
        return 2;
    }

    char text[BUFFER_SIZE+1];
    size_t bytes_read=1;

    if(argc==2){

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
    }else {
        int red;
        red = open(argv[2],O_WRONLY);
        dup2(STDOUT_FILENO,red);

    }
    return 0;

}