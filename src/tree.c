//
// Created by acer on 2016/8/29.
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

/*
 * 局部数据类型
 */
typedef struct pair {
    Node *parent;
    Node *child;
} Pair;

/*
 * 局部函数原型
 */
static Node *makeNode(const Item *pItem);

static bool toLeft(const Item *pi1, const Item *pi2);

static bool toRight(const Item *pi1, const Item *pi2);

static void addNode(Node *pNewNode, Node *pRoot);

static void inOrder(const Node *pRoot, void(*pFun)(Item item));

static Pair seekItem(const Item *pItem, const Tree *pTree);

static void deleteNode(Node **ptr);

static void deleteAllNodes(Node *ptr);


void initializeTree(Tree *pTree) {
    pTree->root = NULL;
    pTree->size = 0;
}

bool treeIsEmpty(const Tree *pTree) {
    return (pTree->root == NULL);
}

bool treeIsFull(const Tree *pTree) {
    return pTree->size == MAX_ITEMS;
}

int treeItemCount(const Tree *pTree) {
    return pTree->size;
}

bool addItem(const Item *pItem, Tree *pTree) {
    Node *pNewNode;
    if (treeIsFull(pTree)) {
        fprintf(stderr, "tree is full.");
        return false;
    }
    if (seekItem(pItem, pTree).child != NULL) {
        fprintf(stderr, "attempted to add duplicate item\n");
        return false;
    }
    pNewNode = makeNode(pItem);
    if (pNewNode == NULL) {
        fprintf(stderr, "couldn't create node\n");
        return false;
    }
    pTree->size++;
    if (pTree->root == NULL) {
        pTree->root = pNewNode;
    } else {
        addNode(pNewNode, pTree);
    }
    return true;
}

bool inTree(const Item *pItem, Tree *pTree) {
    return (seekItem(pItem, pTree).child == NULL) ? false : true;
}

bool deleteItem(const Item *pItem, Tree *pTree) {
    Pair look;
    look = seekItem(pItem, pTree);
    if (look.child == NULL) {
        return false;
    }
    if (look.parent == NULL) {
        deleteNode(&pTree->root);
    } else if (look.parent->left == look.child) {
        deleteNode(&look.parent->left);
    } else {
        deleteNode(&look.parent->right);
    }
    pTree->size--;
    return true;
}

void traverse(const Tree *pTree, void(*pFun)(Item item)) {
    if (pTree != NULL) {
        inOrder(pTree->root, pFun);
    }
}

void deleteAll(Tree *pTree) {
    if (pTree != NULL) {
        deleteAllNodes(pTree->root);
    }
    pTree->root = NULL;
    pTree->size = 0;
}

static Node *makeNode(const Item *pItem) {
    Node *pNewNode;
    pNewNode = (Node *) malloc(sizeof(Node));
    if (pNewNode != NULL) {
        pNewNode->item = *pItem;
        pNewNode->left = NULL;
        pNewNode->right = NULL;

    }
    return pNewNode;
}

static bool toLeft(const Item *pi1, const Item *pi2) {
    int comp;
    if ((comp = strcmp(pi1->petName, pi2->petName)) < 0) {
        return true;
    } else if (comp == 0 && strcmp(pi1->petKind, pi2->petKind) < 0) {
        return true;
    } else {
        return false;
    }
}

static bool toRight(const Item *pi1, const Item *pi2) {
    int comp;
    if ((comp = strcmp(pi1->petName, pi2->petName)) > 0) {
        return true;
    } else if (comp == 0 && strcmp(pi1->petKind, pi2->petKind) > 0) {
        return true;
    } else {
        return false;
    }

}

static void addNode(Node *pNewNode, Node *pRoot) {
    if (toLeft(&pNewNode->item, &pRoot->item)) {
        if (pRoot->left == NULL) {
            pRoot->left = pNewNode;
        } else {
            addNode(pNewNode, pRoot->left);
        }
    } else if (toRight(&pNewNode->item, &pRoot->item)) {
        if (pRoot->right == NULL) {
            pRoot->right = pNewNode;
        } else {
            addNode(pNewNode, pRoot->right);
        }
    } else {
        fprintf(stderr, "location error in addNode()\n");
        exit(1);
    }
}

static void inOrder(const Node *pRoot, void(*pFun)(Item item)) {
    if (pRoot != NULL) {
        inOrder(pRoot->left, pFun);
        (*pFun)(pRoot->item);
        inOrder(pRoot->right, pFun);
    }
}

static Pair seekItem(const Item *pItem, const Tree *pTree) {
    Pair look;
    look.parent = NULL;
    look.child = pTree->root;
    while (look.child != NULL) {
        if (toLeft(pItem, &(look.child->item))) {
            look.parent = look.child;
            look.child = look.child->left;
        } else if (toRight(pItem, &(look.child->right))) {
            look.parent = look.child;
            look.child = look.child->right;
        } else {
            break;
        }
    }
    return look;

}

static void deleteNode(Node **ptr) {
    Node *temp;
    puts((*ptr)->item.petName);
    if ((*ptr)->left == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    } else if ((*ptr)->right == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    } else {
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right) {
            continue;
        }
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
}

static void deleteAllNodes(Node *node) {
    if (node != NULL) {
        deleteAllNodes(node->right);
        deleteAllNodes(node->left);
        free(node);
    }
}