#include <stdio.h>

int main (int argc, char *argv[]){

    if(argc!=3){
        printf("Usage: %s source destination\n ",argv[0]);
        return 1;
    }

    char *src_n=argv[1], *dest_n=argv[2];

    //Abertura dos ficheiros
    FILE * src = fopen(src_n,"r");
    FILE * dest = fopen(dest_n,"w");

    size_t bytes_read=0;
    char * text[50+1];

    while ((bytes_read=fread(text, 1, 50, src))==50){
        fwrite(text, 1, 50, dest);
    }

    if(bytes_read > 0){
        text[bytes_read+1]='\0';
        fwrite(text, 1, bytes_read, dest);
    }
    
    fclose(src);
    fclose(dest);

    return 0;
}