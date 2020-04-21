#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void * thr(void * arg){
    sleep(1);
    printf("I am threat %lu\n", pthread_self());
    pthread_exit(arg);
}

int main(){
    int N;
    scanf("%d", &N);
    pthread_t tids[N];
    int thrs[N];
    void *ret;
    
    for(int i = 0; i < N; i++){
        thrs[i] = i;
        pthread_create(&tids[i], NULL, thr, &thrs[i]);
    }
    for(int i = 0; i < N; i++){
        pthread_join(tids[i], &ret);
        printf("Value of return of %d thread: %d\n", i+1, *(int *)ret);    
    }
    pthread_exit(NULL);

}   