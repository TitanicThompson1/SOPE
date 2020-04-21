// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000
/*
void * thrfunc(void * arg)
{
    int i;
    fprintf(stderr, "Starting thread %s\n", (char *) arg);
    for (i = 1; i <= NUMITER; i++) write(STDERR,arg,1);
    return NULL;
}
*/
void * thrfunc(void * arg)
{
    int i;
    char *to_print = malloc(5);
    fprintf(stderr, "Starting thread %d\n", *(int *) arg);
    sprintf(to_print,"%d",*(int * )arg);
    for (i = 1; i <= NUMITER; i++) write(STDERR,to_print,1);
    return NULL;
}

int main()
{
    pthread_t ta, tb;
    int a = 1, b = 2; //For int version

    //char *a, *b; //For char version

    pthread_create(&ta, NULL, thrfunc, &a);
    pthread_create(&tb, NULL, thrfunc, &b);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}