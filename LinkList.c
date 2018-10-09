//
// Created by bardia kz on 10/5/2018.
//
#include "LinkList.h"
#include <stdlib.h>
#include <stdio.h>


node *create(int value, node *next) {
    node *new_node = (node *) malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->value = value;
    new_node->next = next;

    return new_node;
}


node *add(node *header, int data) {
    node *list1 = header;
    while (list1->next != NULL)
        list1 = (node *) list1->next;

    node *new_node = create(data, NULL);
    list1->next = new_node;

    return header;
}

node *search(node *head, int data) {

    node *list1 = head;
    while (list1 != NULL) {
        if (list1->value == data)
            return list1;
        list1 = (node *) list1->next;
    }
    return NULL;
}

node *remove_front(node *head) {
    if (head == NULL || head->next == NULL)
        return NULL;
    node *front = head;
    head = (node *) head->next;
    front->next = NULL;

    return head;

}


node *remove_back(node *head) {
    if (head == NULL)
        return NULL;

    node *list1 = head;
    node *back = NULL;
    while (list1->next != NULL) {
        back = list1;
        list1 = (node *) list1->next;
    }
    if (back != NULL)
        back->next = NULL;

    if (list1 == head)
        head = NULL;

    free(list1);

    return head;
}

node *remove_any(node *head, node *list1) {
    if (list1 == head) {
        head = remove_front(head);
        return head;
    }

    if (list1->next == NULL) {
        head = remove_back(head);
        return head;
    }

    node *list2 = head;
    while (list2 != NULL) {
        if (list2->next = list1)
            break;
        list2 = (node *) list2->next;
    }

    if (list2 != NULL) {
        node *tmp = (node *) list2->next;
        list2->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
    }
    return head;
}

node *removeByData(node *head, int data) {
    node *temp = search(head, data);
    return remove_any(head, temp);
}

void print(node *head) {
    while (head->next != NULL) {
        printf("%d ", head->value);
        head = (node *) head->next;
    }
    printf("%d\n", head->value);
}