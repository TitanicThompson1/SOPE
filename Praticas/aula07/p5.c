#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h> 
#include <semaphore.h>
#include <wait.h>

#define SHARED 0
#define SHM_SIZE 1


sem_t* empty, *full;
int data, numItems;

char SHM_NAME[] = "/shm20";
char SEM_NAME1[] = "/sem20";
char SEM_NAME2[] = "/sem30";


void consumer(int shmfd){
    int *shm = (int *) mmap (0,SHM_SIZE,PROT_READ,MAP_SHARED,shmfd,0);
    if(shm == MAP_FAILED){
        perror("failed to open shm");
        return;
    }

    empty = sem_open(SEM_NAME1, 0);
    if(empty == SEM_FAILED){
        perror("sem emtpy");
        return;
    }

    full = sem_open(SEM_NAME2, 0);
    if(full == SEM_FAILED){
        perror("sem full");
        return;
    }

    int total = 0, consumed;   
    printf("Consumer running\n"); 
    for (consumed = 1; consumed <= numItems; consumed++){     
        sem_wait(full);     
        total = total + *shm;     
        sem_post(empty);   
    }   
    printf("Consumer: total consumed is %d\n",total); 
    sem_close(full);
    sem_close(empty);
    return;
}

void producer(int shmfd){

    int *shm = (int *) mmap (0,SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if(shm == MAP_FAILED){
        perror("failed to open shm");
        return;
    }

    int total=0, produced;
    empty = sem_open(SEM_NAME1, 0);
    if(empty == SEM_FAILED){
        perror("sem emtpy");
        return;
    }

    full = sem_open(SEM_NAME2, 0);
    if(full == SEM_FAILED){
        perror("sem full");
        return;
    }

    printf("Producer running\n"); 
    for (produced = 1; produced <= numItems; produced++){     
        sem_wait(empty);     
        *shm = produced;     
        total = total + *shm;     
        sem_post(full);   
    }   
    printf("Producer: total produced is %d\n",total);

    sem_close(full);
    sem_close(empty);
    return;
}

int main(int argc, char *argv[]){

    pid_t pid1,pid2;

    if (argc != 2){     
        fprintf(stderr,"USAGE: %s numItems\n",argv[0]);     
        exit(1);   
    }   
    numItems = atoi(argv[1]);

    //Shared memory
    int shmfd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0644);
    if(shmfd < 0){
        perror("shm_open");
        exit(2);
    }

    if (ftruncate(shmfd, sizeof(int)) < 0){
        shm_unlink(SHM_NAME);   
        perror("ftruncate()");    
        exit(2);   
    }
    //Semaphores
    empty = sem_open(SEM_NAME1,O_CREAT, 0644, 1);
    if(empty == SEM_FAILED){
        perror("empty sem_open");
        shm_unlink(SHM_NAME);
    }

    full = sem_open(SEM_NAME2, O_CREAT, 0644, 0);
    if(full == SEM_FAILED){
        perror("empty sem_open");
        sem_close(empty);
        sem_unlink(SEM_NAME1);
        shm_unlink(SHM_NAME);
    }

    
    printf("Main started.\n");   

    if((pid1=fork())==0){
        producer(shmfd);
        return 0;
    }

    if((pid2=fork())==0){
        consumer(shmfd);
        return 0;
    }
    wait(NULL);
    wait(NULL);

    sem_close(full);
    sem_close(empty);
    sem_unlink(SEM_NAME1);
    sem_unlink(SEM_NAME2);
    shm_unlink(SHM_NAME);

    

    printf("Main done.\n");
    return 0;
}