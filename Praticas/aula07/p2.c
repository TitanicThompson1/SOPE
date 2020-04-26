// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 1000

int N = NUMITER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void * thrfunc(void * arg)
{
    void *ret = malloc(sizeof(int));
    int i = 0;
    char *to_print = malloc(1);
    fprintf(stderr, "Starting thread %d\n", *(int *) arg);
    sprintf(to_print, "%d", *(int * )arg);
    pthread_mutex_lock(&mut);
    while (N != 0) {
         N--;
        pthread_mutex_unlock(&mut);

        write(STDERR, to_print, 1);
        i++;
        pthread_mutex_lock(&mut);
    }
 
    pthread_mutex_unlock(&mut);
    write(STDERR, "\n", 2);
    
    *(int *)ret = i;
    return ret;
}

int main()
{
    pthread_t ta, tb;
    int a = 1, b = 2; //For int version
    void *retA = malloc(sizeof(int)), *retB  = malloc(sizeof(int));
    //char *a, *b; //For char version

    pthread_create(&ta, NULL, thrfunc, &a);
    pthread_create(&tb, NULL, thrfunc, &b);

    pthread_join(ta, &retA);
    printf("Number of interactions in thread A: %d\n", *(int *) retA);
    free(retA);

    pthread_join(tb, &retB);
    printf("Number of interactions in thread B: %d\n", *(int *) retB);
    free(retB);

    printf("N final value: %d\n", N);
    return 0;
}