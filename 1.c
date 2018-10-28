
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int *a;
    int *b;
    int sum;
    int veclen;
} DOTDATA;

DOTDATA dotdata;
pthread_t *callThd;
pthread_mutex_t mutexsum;


void *dotprod(void *arg) {
    int start, end, len;
    int offset;
    int mysum, *x, *y;
    offset = (int) arg;
    printf("Thread %d Computing My Part \n", offset);
    len = dotdata.veclen;
    start = offset * len;
    end = start + len;
    x = dotdata.a;
    y = dotdata.b;
    mysum = 0;
    for (int i = start; i < end; i++) {
        mysum += (x[i] * y[i]);
    }

    pthread_mutex_lock(&mutexsum);
    dotdata.sum += mysum;
    pthread_mutex_unlock(&mutexsum);
    pthread_exit((void *) 0);
    return NULL;
}

void printVector(int *vec, int n) {
    printf("Vector = < ");
    for (int i = 0; i < n-1; ++i) {
        printf("%d , ", vec[i]);
    }
    printf("%d >\n",vec[n-1]);


}

int main(int argc, char *argv[]) {
    int vecLenght;
    int threadNumber;
    int *a, *b;
    a = (int *) malloc(vecLenght * sizeof(int));
    b = (int *) malloc(vecLenght * sizeof(int));
    printf("Length Of Vector: ");
    scanf("%d", &vecLenght);
    printf("Number Of Threads: ");
    scanf("%d", &threadNumber);
    printf("Main thread: filling the vectors with random numbers. \n");
    for (int i = 0; i < vecLenght; i++) {
        a[i] = i + 1;
        b[i] = a[i];
    }
    printVector(a, vecLenght);
    printVector(b, vecLenght);
    pthread_attr_t attr;
    callThd = (pthread_t *) malloc(threadNumber * sizeof(pthread_t));
    dotdata.veclen = vecLenght / threadNumber;
    dotdata.a = a;
    dotdata.b = b;
    dotdata.sum = 0;

    pthread_mutex_init(&mutexsum, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (int i = 0; i < threadNumber; i++) {
        pthread_create(&callThd[i], &attr, dotprod, (void *) i);
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i < threadNumber; i++) {
        pthread_join(callThd[i], NULL);
    }
    printf("Main thread: dot product result: %d . Exiting \n", dotdata.sum);
    free(a);
    free(b);
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
}
