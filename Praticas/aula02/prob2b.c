#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h> 

int main (int argc, char *argv[]){

    if(argc!=3){
        printf("Usage: %s source destination\n ",argv[0]);
        return 1;
    }

    char *src_n=argv[1], *dest_n=argv[2];

    //Abertura dos ficheiros
    int src = open(src_n,O_RDONLY);
    if(src == -1){
        perror(src_n);
        return 2;
    }

    int dest = open(dest_n,O_WRONLY);
    if(dest == -1){
        perror(dest_n);
        close(src);
        return 3;
    }


    ssize_t bytes_read=0, bytes_written=0;

    char * text[50+1];

    while ((bytes_read= read(src,text,50) )==50){
        bytes_written = write(dest, text, 50);
        
        if(bytes_written == -1){
            perror(dest_n);
            close(src);
            close(dest);
            return 4;
        }
    }

    if(bytes_read == -1){
        perror(src_n);
        close(src);
        close(dest);
        return 4;

    }else if (bytes_read!=0){
        text[bytes_read+1]='\0';
        bytes_written = write(dest, text, bytes_read);

        if(bytes_written==-1){
            perror(dest_n);
            close(src);
            close(dest);
            return 4; 
        }
    }

    close(src);
    close(dest);

    return 0;

}