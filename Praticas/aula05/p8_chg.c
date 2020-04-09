#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Usage: %s <message>\n", argv[0]);
        exit(1);
    }

    int fd = open("/tmp/fifo_chg", O_WRONLY);

    write(fd, argv[1], strlen(argv[1]));

    return 0;

}