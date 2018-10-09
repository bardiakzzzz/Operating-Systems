//
// Created by bardia kz on 10/5/2018.
//

#ifndef HW1_LINKLIST_H
#define HW1_LINKLIST_H

#include <afxres.h>

typedef struct LinkList {
    int value;
    struct node *next;
} node;

node *create(int value, node *next);

node *add(node *header, int data);

node *remove_front(node *header);

node *remove_back(node *header);

node *remove_any(node *header, node *list1);

void print(node *header);

node *search(node *header, int data);

node *removeByData(node *header, int data);


#endif //HW1_LINKLIST_H
