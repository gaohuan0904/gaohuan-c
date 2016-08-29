//
// Created by acer on 2016/8/29.
//

#ifndef GAOHUAN_C_QUEUE_H
#define GAOHUAN_C_QUEUE_H

#include <stdbool.h>

typedef int Item;

#define  MAX_QUEUE 10
typedef struct node {
    Item item;
    struct node *next;
} Node;

typedef struct queue {
    Node *front;
    Node *rear;
    int items;
} Queue;

void initializeQueue(Queue *pq);

bool queueIsFull(const Queue *pq);

bool queueIsEmpty(const Queue *pq);

int queueCount(const Queue *pq);

bool enQueue(Item item, Queue *pq);

bool delQueue(Item *pItem, Queue *pq);

void clearQueue(Queue *pq);


#endif //GAOHUAN_C_QUEUE_H
