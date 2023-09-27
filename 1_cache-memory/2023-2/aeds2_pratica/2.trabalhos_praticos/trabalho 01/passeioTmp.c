#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x, y;
    struct Node *next, *prev;
} Node;

Node* newNode(int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->x = x;
    node->y = y;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void addNode(Node** head, int x, int y) {
    Node* node = newNode(x, y);
    if (*head == NULL) {
        *head = node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("(%d, %d)\n", temp->x, temp->y);
        temp = temp->next;
    }
}

int main() {
    Node* head = NULL;

    // Adicione os movimentos do cavalo à lista
    addNode(&head, 0, 0);
    addNode(&head, 1, 2);
    addNode(&head, 2, 4);
    // Continue adicionando os movimentos...

    printList(head);

    return 0;
}
