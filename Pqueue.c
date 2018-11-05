//
// Created by bardia kz on 11/4/2018.
//
#include <malloc.h>
#include <pthread.h>
#include <assert.h>
#include "Pqueue.h"

void Pqueue_init(Pqueue *q) {
    for (int i = 0; i < 10; ++i) {
        node_t *tmp = malloc(sizeof(node_t));
        tmp->next = NULL;
        q->head[i] = tmp;
        q->size[i] = 0;
        pthread_mutex_init(&q->HeadLock[i], NULL);
    }
}

int Pqueue_enqueue(Pqueue *q, int level, int value) {
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = value;
    tmp->next = NULL;

    pthread_mutex_lock(&q->HeadLock[level]);
    while (q->size[level]== 10);
    tmp->next = q->head[level];
    q->head[level] = tmp;
    q->size[level]++;
    pthread_mutex_unlock(&q->HeadLock[level]);
    return 0;
}

int Pqueue_dequeue(Pqueue *q, int level, int *value) {
    pthread_mutex_lock(&q->HeadLock[level]);
    node_t *tmp = q->head[level];
    if (tmp->next == NULL) {
        pthread_mutex_unlock(&q->HeadLock[level]);
        return -1;
    }
    *value = q->head[level]->value;
    q->head[level] = tmp->next;
    q->size[level]--;
    pthread_mutex_unlock(&q->HeadLock[level]);
    free(tmp);
    return 0;
}

