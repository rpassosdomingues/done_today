#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int *front;
    int *back;
    int length;
    int data;
} Queue;

void insert (Queue *queue, int data) {
    Queue *newElement = (Queue*)malloc(sizeof(Queue));
    int aux = -1;
    int prov = (newElement->back % newElement->length) + 1;
    if (prov != newElement->front) {
        newElement->back = prov;
        newElement->back = data;
        aux = newElement->back;
    } else if (newElement->front == 0) {
        newElement->front = 1;
    }
}

void remove () {
    //to-do
}

int main () {
    //to-do
    return 0;
}