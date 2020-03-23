
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define MAX_PIDS 20

void fillpids(pid_t *a, int n);

int putpid(pid_t *a, int n, pid_t pid);

int main(int argc, char *argv[]){

    DIR * src; DIR * dest;
    struct dirent *file;
    struct stat filestat;
    pid_t pids[MAX_PIDS];
    int it_pid=0, status;


    //Checking for illegal arguments
    if(argc != 3){
        printf("Usage: %s dirname_source dirnname_dest\n", argv[0]);
        exit(1);
    }

    //Opening source
    if((src = opendir(argv[1])) == NULL){
        perror(argv[1]);
        exit(2);
    }

    //Opening destination
    if((dest = opendir(argv[2])) == NULL){
        perror(argv[2]);
        exit(3);
    }

    //Filling pid array
    fillpids(pids, MAX_PIDS);

    while((file = readdir(src))!=NULL){

        //Reads file
        lstat(file->d_name, &filestat);
        
        //Verifies if is    
        if(S_ISREG(filestat.st_mode)){
            pid_t pid = fork();
            
            if(pid == 0){        //Processo-Filho
                execlp("cp","cp", argv[1],argv[2], NULL);
                printf("Error in executing cp");
                exit(4);
            }else {
                if(putpid(pids, MAX_PIDS, pid)!=0){
                    printf("Maximum number of forks exceeded\n");
                    exit(5);
                }
            }
        }

        //Verifica se algum processo filho acabou
        it_pid = 0;
        while (pids[it_pid] != (pid_t) -1){
            
            if(pids[it_pid] != (pid_t) 0){
                waitpid(pids[it_pid], &status, WNOHANG);
            }
            it_pid++;
            
        }
        
    }

   

}

void fillpids(pid_t *a, int n){
    for (int i = 0; i<n; i++){
        a[i]= (pid_t) 0;
    }
    a[n-1]= (pid_t) -1;
}

int putpid(pid_t *a, int n, pid_t pid){
    int i=0;
    while(a[i]!=-1){
        if(a[i]==0){
            a[i] = pid;
            return 0;
        }
    }
    return 1;
}
