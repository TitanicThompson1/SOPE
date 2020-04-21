#include <stdio.h>
#include <pthread.h>

int global;
void *thr_func(void *arg){
	global++;
	printf("Aux thread: %d\n", global);
	return NULL;
}

int main(void){
	pthread_t tid;global = 10;
	printf("Main thread: %d\n", global);
	pthread_create(&tid, NULL, thr_func, NULL);
    pthread_join(tid, NULL);
	printf("Main thread: %d\n", global);
	return 0;
}