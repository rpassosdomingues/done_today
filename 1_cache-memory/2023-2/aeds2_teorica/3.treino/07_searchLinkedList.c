#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int value;
    struct node *next;
} Node;

void search (Node *ptlist, Node *ptr, Node *pont, Node *ant, int value) {
    ant = ptlist;
    pont = NULL;
    ptr = ptlist->next;
    while (ptr != NULL) {
        if (ptr->key < value) {
            ant = ptr;
            ptr = ptr->next;
        } else if (ptr->key == value) {
            pont = ptr;
            ptr = NULL;
        }
    }
}

/*
 * void insert (?) {
 * int insert = -1;
 * search(ptlist, ptr, pont, ant, value);
 * if (pont == NULL) {
 *  Node->next = ant->next;
 * ant->next = Node;
 * insert = 0;
 * }
*} 
*/

int main () {
    //Node *node = NULL;
    //insert(node);
    return 0;
}