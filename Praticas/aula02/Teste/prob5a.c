#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>

// PROGRAMA p5a.c #include ... //a completar 
int main(void) {   
    int fd;   
    char *text1="AAAAA";   
    char *text2="BBBBB";

    fd = open("f1.txt", O_CREAT | O_EXCL | O_WRONLY|O_SYNC, 0600);
    
    if(fd==-1){
        perror("prob5a");
        return 1;
    }

    getchar();
    if(write(fd, text1, 5)==-1){
        perror("prob5a");
        close(fd);
        return 2;
    }

    getchar();
    if(write(fd, text2, 5)==-1){
        perror("prob5a");
        close(fd);
        return 3;
    }   
    
    close(fd);   
    return 0;      
} 