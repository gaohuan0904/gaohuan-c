//
// Created by acer on 2016/8/29.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

static void copyToNode(Item item, Node *pNode);

static void copyToItem(Node *pNode, Item *pItem);

void initializeQueue(Queue *pq) {
    pq->front = NULL;
    pq->rear = NULL;
    pq->items = 0;
}

bool queueIsFull(const Queue *pq) {
    return pq->items == MAX_QUEUE;
}

bool queueIsEmpty(const Queue *pq) {
    return pq->items == 0;
}

int queueCount(const Queue *pq) {
    return pq->items;
}

bool enQueue(Item item, Queue *pq) {
    Node *pNew;
    if (queueIsFull(pq)) {
        return false;
    }
    pNew = (Node *) malloc(sizeof(Node));
    if (pNew == NULL) {
        fprintf(stderr, "unalble to allocate memory!\n");
        exit(1);
    }
    copyToNode(item, pNew);//节点设置值
    pNew->next = NULL;
    if (queueIsEmpty(pq)) {
        pq->front = pNew;//没有元素，放在队头
    } else {
        pq->rear->next = pNew;//放在队尾
    }
    //设置新的队尾
    pq->rear = pNew;
    pq->items++;//元素数增加
    return true;
}

bool delQueue(Item *pItem, Queue *pq) {
    Node *pNode;
    if (queueIsEmpty(pq)) {
        return false;
    }
    copyToItem(pq->front, pItem);
    pNode = pq->front;//第一个元素
    //把后一个元素的链接往前移一位
    pq->front = pq->front->next;
    free(pNode);
    pq->items--;
    if (pq->items == 0) {//空队列，队尾指向空
        pq->rear = NULL;
    }
    return true;
}

void clearQueue(Queue *pq) {
    Item dummy;
    while (!queueIsEmpty(pq)) {
        delQueue(&dummy, pq);
    }
}


static void copyToNode(Item item, Node *pNode) {
    pNode->item = item;
}

static void copyToItem(Node *pNode, Item *pItem) {
    *pItem = pNode->item;
}