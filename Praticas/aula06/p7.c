#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h> 
#include <string.h>

//Read-Only variables
char *sourcePath;
char *destPath;

#define BUFFER_SIZE 1024

void *copyFile(void * arg);

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Usage: %s <source> <destiny>\n", argv[0]);
        exit(1);
    }
    sourcePath = argv[1];
    destPath = argv[2];


    DIR *source_dir, *dest_dir;

    if(source_dir = opendir(argv[1]), source_dir == NULL){
        printf("Error on opening source_dir\n");
        exit(2);
    }

    if(dest_dir = opendir(argv[1]), dest_dir == NULL){
        printf("Error on opening dest_dir\n");
        exit(2);
    }

    struct dirent *dentry; 
    struct stat stat_entry;

    pthread_t tid;
    
    while(dentry = readdir(source_dir), dentry != NULL){
        stat(dentry->d_name, &stat_entry);
        if(S_ISREG(stat_entry.st_mode)){
            pthread_create(&tid, NULL, copyFile, dentry->d_name);
        }
    }

    pthread_exit((void *) 0);
}

void *copyFile(void * arg) {
    char *filename = (char *) arg;

    char dest[30], src[30];
    strcpy(src, sourcePath);
    strcpy(dest,destPath);

    sprintf(dest, "%s/%s", dest, filename);
    sprintf(src, "%s/%s", src, filename);

    int fdSrc = open(src, O_RDONLY);
    if(fdSrc == -1){
        perror(src);
        return NULL;
    }

    int fdDest = open(dest, O_WRONLY | O_CREAT, 0644);
    if(fdDest == -1){
        perror(dest); close(fdSrc);
        return NULL;
    }
    int nr,nw;
    char buffer[BUFFER_SIZE];

    while ((nr = read(fdSrc, buffer, BUFFER_SIZE)) > 0) 
        if ((nw = write(fdDest, buffer, nr)) <= 0 || nw != nr) {    
            perror(dest);    
            close(fdDest); close(fdSrc); 
            return NULL;   
        }   
     close(fdDest); close(fdSrc);  
    return 0;

    
}