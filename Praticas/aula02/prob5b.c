#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>

// PROGRAMA p5b.c #include ... //a completar 
int main(void) {   
    int fd;   
    char *text1="CCCCC";   
    char *text2="DDDDD";   
    fd = open("f1.txt", O_WRONLY|O_SYNC | O_APPEND,0600);  
    if(fd==-1){
        perror("prob5b");
        return 1;
    }

    getchar();
    if(write(fd,text1,5)==-1){
        perror("prob5b");
        close(fd);
        return 2;
    }

    getchar();
    if(write(fd,text2,5)==-1){
        perror("prob5b");
        close(fd);
        return 3;
    }   
    
    close(fd);   
    
    return 0;      
}