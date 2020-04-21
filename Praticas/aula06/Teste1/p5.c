#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct p5
{
    float n1, n2;
};

struct response{
    float res;
    int valid;
};

void * sum(void *arg){
    struct p5 data = *(struct p5 *) arg;

    struct response resp;
    resp.res = data.n1 + data.n2; resp.valid = 0;

    void * ret = malloc(sizeof(struct response));
    *(struct response * ) ret = resp;
    return ret;
}

void * sub(void *arg){
    struct p5 data = *(struct p5 *) arg;

    struct response resp;
    resp.res = data.n1 - data.n2; resp.valid = 0;
    
    void * ret = malloc(sizeof(struct response));
    *(struct response * ) ret = resp;
    return ret;
}

void * divis(void *arg){
    struct p5 data = *(struct p5 *) arg;

    struct response resp;
    if(data.n2 == 0) resp.valid = 1;
    else{ 
        resp.res = data.n1 / data.n2;
        resp.valid = 0;
    }

    void * ret = malloc(sizeof(struct response));
    *(struct response * ) ret = resp;
    return ret;
}

void * mult(void *arg){
    struct p5 data = *(struct p5 *) arg;

    struct response resp;
    resp.res = data.n1 * data.n2; resp.valid = 0;
    
    void * ret = malloc(sizeof(struct response));
    *(struct response * ) ret = resp;
    return ret;
}

int main(){

    
    pthread_t tids[4];
    struct p5 data;
    void *ret;
    struct response resp;

    scanf("%f %f", &data.n1, &data.n2);

    //Sum
    pthread_create(&tids[0], NULL, sum, &data);

    //Subtraction
    pthread_create(&tids[1], NULL, sub, &data);

    //Multiplication
    pthread_create(&tids[2], NULL, mult, &data);

    //Division
    pthread_create(&tids[3], NULL, divis, &data);

    pthread_join(tids[0], &ret);
    resp = *(struct response *) ret;
    printf("Sum: %f\n", resp.res);

    pthread_join(tids[1], &ret);
    resp = *(struct response *) ret;
    printf("Subtraction: %f\n", resp.res);

    pthread_join(tids[2], &ret);
    resp = *(struct response *) ret;
    printf("Multiplication: %f\n", resp.res);

    pthread_join(tids[3], &ret);
    resp = *(struct response *) ret;
    if(resp.valid == 1) printf("Division: NaN\n");
    else printf("Division: %f\n", resp.res);

    pthread_exit(NULL);

}   

/*
pthread_t tids[4];
    struct p5 data;

    scanf("%d %d", &data.n1, &data.n2);

    //Sum
    pthread_create(&tids[0], NULL, sum, &data);

    //Subtraction
    pthread_create(&tids[1], NULL, sub, &data);

    //Multiplication
    pthread_create(&tids[2], NULL, mult, &data);

    //Division
    pthread_create(&tids[3], NULL, div, &data);

    pthread_exit(NULL);
*/
