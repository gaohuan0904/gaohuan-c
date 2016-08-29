#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include "tree.h"

char menu(void);

void addPet(Tree *pTree);

void dropPet(Tree *pTree);

void showPets(const Tree *pTree);

void findPet(const Tree *pTree);

void printItem(Item item);

void upperCase(char *str);


int main(int argc, char *argv[]) {

    Tree pets;
    char choic;
    initializeTree(&pets);
    while ((choic == menu()) != 'q') {
        switch (choic) {
            case 'a':
                addPet(&pets);
                break;
            case 'l':
                showPets(&pets);
                break;
            case 'f':
                findPet(&pets);
                break;
            case 'n':
                printf("%d pets in club\n", treeItemCount(&pets));
                break;
            case 'd':
                dropPet(&pets);
                break;
            default:
                puts("witching error!");
        }
    }
    deleteAll(&pets);
    puts("bye!");


    return EXIT_SUCCESS;

}

char menu(void) {
    int ch;
    puts("nerfville pet club membership program");
    puts("enter the letter corresponding to your choice:");
    puts("a）add a pet     l)show list of pets");
    puts("n）numer of perts     f)find pets");
    puts("d）delete a pet     q)quit");
    while ((ch = getchar()) != EOF) {
        while (getchar() != '\n') {
            continue;
        }
        ch = tolower(ch);
        if (strchr("alfndq", ch) == NULL) {
            puts("please enter an a l f n d or q.");
        } else {
            break;
        }

    }
    if (ch == EOF) {
        ch = 'q';
    }
    return ch;


}

void addPet(Tree *pTree) {
    Item temp;
    if (treeIsFull(pTree)) {
        puts("no room in the club");
    } else {
        puts("please enter  petName:");
        gets(temp.petName);
        puts("please enter petKind:");
        gets(temp.petKind);
        upperCase(temp.petName);
        upperCase(temp.petKind);
        addItem(&temp, pTree);
    }
}

void dropPet(Tree *pTree) {
    Item item;
    if (treeIsEmpty(pTree)) {
        puts("no entries");
        return;
    }
    puts("please enter name of pet you wish to delete:");
    gets(item.petName);
    puts("please enter pet kind:");
    gets(item.petKind);
    upperCase(item.petName);
    upperCase(item.petKind);
    printf("%s the %s", item.petName, item.petKind);
    if (deleteItem(&item, pTree)) {
        printf("is drooped from the club.\n");
    } else {
        printf("is not a member");
    }
}

void showPets(const Tree *pTree) {
    if (treeIsEmpty(pTree)) {
        puts("no entries");
    } else {
        traverse(pTree, printItem);
    }
}

void findPet(const Tree *pTree) {
    Item item;
    if (treeIsEmpty(pTree)) {
        puts("no entries");
        return;
    }
    puts("please enter name of pet you wish to find:");
    gets(item.petName);
    puts("please enter pet kind:");
    gets(item.petKind);
    upperCase(item.petName);
    upperCase(item.petKind);
    printf("%s the %s", item.petName, item.petKind);
    if (inTree(&item, pTree)) {
        printf("is a member.\n");
    } else {
        printf("is not a member");
    }

}

void printItem(Item item) {
    printf("pet:%-19s kind:%-19s\n", item.petName, item.petKind);
}

void upperCase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}






