//
// Created by bardia kz on 11/4/2018.
//

#ifndef Q1_PQUEUE_H
#define Q1_PQUEUE_H

#include <sys/param.h>

typedef struct __node_t {
    int value;
    struct __node_t *next;
} node_t;

typedef struct __queue_t {
    node_t *head[10];
    int size[10];
    pthread_mutex_t HeadLock[10];
} Pqueue;



void Pqueue_init(Pqueue *q);
int Pqueue_enqueue(Pqueue *q, int level, int value);
int Pqueue_dequeue(Pqueue *q, int level, int *value);

#endif //Q1_PQUEUE_H
