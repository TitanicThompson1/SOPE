// PROGRAMA p01.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <sys/types.h>
#include <semaphore.h> 
#include <sys/mman.h> 
#include <unistd.h>
#include <wait.h>

#define MAXELEMS 10000000 // nr. max de posicoes
#define MAXTHREADS 100
// nr. max de threads
#define min(a, b) (a)<(b)?(a):(b)
int npos;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int pos=0, val=0;

char *SHM_NAME = "/shm1";
char *SEM_NAME = "/sem1";


// mutex p/a sec.critica
// variaveis partilhadas
int fill(int shmfd, sem_t *sem)
{   
    int * buf = (int *) mmap(0, npos*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    int nr = 0;
    while (1) {
        sem_wait(sem);
        if (pos >= npos) {
            sem_post(sem);
            munmap(buf, npos*sizeof(int));
            return nr;
        }
        buf[pos] = val;
        pos++; val++;
        sem_post(sem);
        nr += 1;
    }
    
}

void verify(int shmfd)
{
    int * buf = (int *) mmap(0, npos*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    int k;
    for (k=0; k<npos; k++)
        if (buf[k] != k)
        // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    
    munmap(buf, npos*sizeof(int));
    
}

int main(int argc, char *argv[])
{

    int k, nthr, count[MAXTHREADS];

    // array para contagens
    pid_t pids[MAXTHREADS];
    int total;

    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n",argv[0]);
        return 1;
    }

    npos = min(atoi(argv[1]), MAXELEMS);
    nthr = min(atoi(argv[2]), MAXTHREADS);

    //no. efectivo de posicoes
    //no. efectivo de threads

    //Shared Memmory Criation
    
    int shmfd = shm_open(SHM_NAME, O_CREAT | O_RDONLY, 0600);
    if(shmfd < 0){
        perror("shm_open");
        exit(2);
    }

    if (ftruncate(shmfd, npos*sizeof(int)) < 0)   {     
        perror("WRITER failure in ftruncate()");    
        exit(2);   
    }

    //Semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0600, 1);
    
    
    //Fill threads
    for (k=0; k<nthr; k++) {
        
        if((pids[k] =fork()) == 0){
            return fill(shmfd, sem);
        }
    }


    total = 0;    
    for (k=0; k<nthr; k++) {
        //espera threads 'fill'
        waitpid(pids[k], &count[k], 0);
        printf("count[%d] = %d\n", k, count[k]);
        total += count[k];
    }

    printf("total count = %d\n",total);
    // mostra total
    if(fork() == 0){
        verify(shmfd);
    }

    wait(NULL);
    
    sem_close(sem);
    sem_unlink(SEM_NAME);

    if(shm_unlink(SHM_NAME) < 0){
        perror("shm_unlink");
        exit(4);
    }
    return 0;
}