
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "Pqueue.h"

Pqueue pqueue;

void *producer(void *arg) {
    int randomNumber = (int) arg;
    srand((unsigned int) randomNumber);
    while (true) {
        int randomNumber = rand() % 1000 +1;
        int level = randomNumber /100;
        Pqueue_enqueue(&pqueue, level, randomNumber);
        printf("Enqueued number : %d in level %d\n", randomNumber, level);
        sleep(rand() % 5 + 1);
    }
}

void *consumer(void *arg) {
    int randomNumber = (int) arg;
    srand((unsigned int) randomNumber);
    while (true) {
        int i = 9;
        int x;
        while (i >= 0) {
            if (Pqueue_dequeue(&pqueue, i, &x) == 0) {
                printf("Dequeued number = %d in level %d\n", x, i);
            }
            i--;
        }
        sleep(rand() % 5 + 1);


    }

}

int main() {
    srand((unsigned) time(NULL));
    Pqueue_init(&pqueue);
    pthread_t producers[8];
    pthread_t consumers[8];
    for (int i = 0; i < 8; i++) {
        pthread_create(&producers[i], NULL, producer, i);
        pthread_create(&consumers[i], NULL, consumer, i);
    }
    for (int j = 0; j < 8; ++j) {
        pthread_join(producers[j], NULL);
        pthread_join(consumers[j], NULL);
    }
    free(&producers);
    free(&consumers);
    free(&pqueue);


    return 0;
}

