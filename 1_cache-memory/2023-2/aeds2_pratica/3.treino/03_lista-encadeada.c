#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct Node *next;
} Node;

typedef struct list {
    Node *start;
    int length;
} List;

void insert_start (List *linkedList, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    
    newNode->value = value; // (*newNode).value = value;
    newNode->next = linkedList->start;//newNode->next = NULL;
    
    linkedList->start = newNode;
    linkedList->length++;
}

void insert_end(List *linkedlist, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (linkedlist->start != NULL) {
        Node *node = linkedlist->start; // Corrección: Declarar 'node' como un puntero Node.
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = newNode;
        linkedlist->length++;
        
    } else {
        linkedlist->start = newNode;
        linkedlist->length++;
    }
}

void print_list (List *linkedList) {
    Node *start = linkedList->start;
    printf("\nLength of list: %d\n", linkedList->length);
    while (start != NULL) {
        printf("%d ", start->value);
        start = start->next;
    }
    printf("\n");
    
}


int main () {
    List linkedList;
    
    linkedList.start = NULL;
    linkedList.length = 0;

    int choice, value;

    do {
       printf("\n0 - Quit\n1 - Insert Start\n2 - Insert End\n3 - Print List\nEnter your choice[0-3]: ");
       scanf("%d", &choice);
        switch (choice) {
        case 0:
            //free(newNode);
            return 0;
        case 1:
            printf("\n\tEnter a inserted value in the start: ");
            scanf("%d", &value);
            insert_start(&linkedList, value);
            break;
        case 2:
            printf("\n\tEnter a inserted value in the end: ");
            scanf("%d", &value);
            insert_end(&linkedList, value);
            break;    
        case 3:
            print_list(&linkedList);
            break;
        default:
        break;
       }
    } while (1);
}
