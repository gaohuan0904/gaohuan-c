//
// Created by acer on 2016/8/29.
//

#ifndef GAOHUAN_C_TREE_H
#define GAOHUAN_C_TREE_H

#include <stdbool.h>

typedef struct item {
    char petName[20];
    char petKind[20];
} Item;

#define MAX_ITEMS 10

typedef struct node {
    Item item;
    struct node *left;
    struct node *right;
} Node;

typedef struct tree {
    Node *root;
    int size;
} Tree;


void initializeTree(Tree *pTree);

bool treeIsEmpty(const Tree *pTree);

bool treeIsFull(const Tree *pTree);

int treeItemCount(const Tree *pTree);

bool addItem(const Item *pItem, Tree *pTree);

bool inTree(const Item *pItem, Tree *pTree);

bool deleteItem(const Item *pItem, Tree *pTree);

void traverse(const Tree *pTree, void(*pFun)(Item item));

void deleteAll(Tree *pTree);


#endif //GAOHUAN_C_TREE_H
