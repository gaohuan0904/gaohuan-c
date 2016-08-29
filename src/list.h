#ifndef LIST_H_

#define LIST_H_
#define  TSIZE 45

struct film {
    char title[TSIZE];
    int rating;
};
//一般类型定义
typedef struct film Item;
typedef struct node {
    Item item;
    struct node *next;
} Node;

typedef Node *List;

void initializeList(List *pList);

bool listIsEmpty(const List *plist);

bool listIsFull(const List *plist);

unsigned int listItemCount(const List *plist);

bool addItem(Item item, List *plist);

void traverse(const List *plist, void(*pf)(Item item));

void clearList(List *plist);


#endif