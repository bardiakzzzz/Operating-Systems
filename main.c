
#include <stdio.h>
#include "Pqueue.h"



int main() {
    Pqueue q;
    Pqueue_init(&q);
    Pqueue_enqueue(&q,0,1);
    Pqueue_enqueue(&q,0,2);
    Pqueue_enqueue(&q,0,3);
    int x;
    Pqueue_dequeue(&q,0,&x);
    printf("%d",x);


    return 0;
}

