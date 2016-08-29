#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"


static void copyToNode(Item item, Node *pnode);

void initializeList(List *pList) {
    *pList = NULL;
}

bool listIsEmpty(const List *plist) {
    if (*plist == NULL) {
        return true;
    } else {
        return false;
    }
}

bool listIsFull(const List *plist) {
    Node *pt;
    bool full;
    pt = (Node *) malloc(sizeof(Node));
    if (pt == NULL) {
        full = true;
    } else {
        full = false;
    }
    free(pt);
    return full;

}


unsigned int listItemCount(const List *plist) {
    unsigned int count = 0;
    Node *pNode = *plist;//设置到列表开始处
    while (pNode != NULL) {
        ++count;
        pNode = pNode->next;
    }
    return count;

}

bool addItem(Item item, List *plist) {
    Node *pnew;
    Node *scan = *plist;
    pnew = (Node *) malloc(sizeof(Node));
    if (pnew == NULL) {
        return false;
    }
    copyToNode(item, pnew);
    pnew->next = NULL;
    if (scan == NULL) {
        *plist = pnew;//新节点放在列表头
    } else {
        while (scan->next != NULL) {
            scan = scan->next;
        }
        scan->next = pnew;
    }
    return true;

}

void traverse(const List *plist, void(*pf)(Item item)) {
    Node *pnode = *plist;
    while (pnode != NULL) {
        (*pf)(pnode->item);
        pnode = pnode->next;
    }
}

void clearList(List *plist) {
    Node *pnode;
    while (*plist != NULL) {
        pnode = (*plist)->next;
        free(pnode);//释放当前节点
        *plist = pnode;
    }
}

static void copyToNode(Item item, Node *pnode) {
    pnode->item = item;
}


