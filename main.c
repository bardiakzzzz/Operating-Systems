//#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>

// C program for generic linked list
#include<stdio.h>
#include<stdlib.h>
#include "LinkList.h"

/* A linked list node */
int main(){
    node*s = create(1,NULL);
    add(s, 2);
    add(s, 3);
    add(s, 4);
    add(s, 5);
    add(s, 6);
    add(s, 7);
    add(s, 8);
    add(s, 9);
    s = removeByData(s,2);
    s = removeByData(s,3);
    s = remove_front(s);
    s = remove_back(s);
    print(s);

    return  0;
}