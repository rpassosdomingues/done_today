#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "circular_queue.h"

struct queue {
    int front, rear, current_max_size;
    int current_size;
    int *items;
};

struct queue *create_queue(int current_max_size) {
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    queue->current_max_size = current_max_size;
    queue->current_size = 0;
    queue->front = -1;
    queue->rear = -1;
    queue->items = (int *)malloc(queue->current_max_size * sizeof(int));
    return queue;
}

bool is_empty(struct queue *queue) {
    return queue->front == -1;
}

bool is_full(struct queue *queue) {
    return ((queue->rear + 1) % queue->current_max_size) == queue->front;
}

void enqueue(struct queue *queue, int item) {
    if (is_full(queue)) {
        printf("\nQueue is full. Cannot insert elements.");
        return;
    }
    if (is_empty(queue)) {
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % queue->current_max_size;
    queue->items[queue->rear] = item;
    queue->current_size++;
}

int dequeue(struct queue *queue) {
    if (is_empty(queue)) {
        printf("\nQueue is empty. Cannot remove elements.");
        return INT_MIN;
    }
    int item = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->current_max_size;
    }
    queue->current_size--;
    return item;
}

int get_front(struct queue *queue) {
    if (is_empty(queue)) {
        printf("\nQueue is empty. Cannot get elements.");
        return INT_MIN;
    }
    return queue->items[queue->front];
}

int main() {
    int val, choice;
    bool aux;
    // Create a queue with a maximum size of 5
    struct queue *queue = create_queue(5);
    do {
        printf("\n************************* MENU ************************");
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Get Front Element");
        printf("\n4. Is Queue Empty?");
        printf("\n5. Is Queue Full?");
        printf("\n6. Exit");
        printf("\n Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nEnter the value: ");
                scanf("%d", &val);
                enqueue(queue, val);
                break;
            case 2:
                printf("\nRemoved Element: %d", dequeue(queue));
                break;
            case 3:
                printf("\nFront Element: %d", get_front(queue));
                break;
            case 4:
                aux = is_empty(queue);
                if (aux) {
                    printf("\nQueue is empty");
                } else {
                    printf("\nQueue is not empty");
                }
                break;
            case 5:
                aux = is_full(queue);
                if (aux) {
                    printf("\nQueue is full");
                } else {
                    printf("\nQueue is not full");
                }
                break;
            case 6:
                free(queue->items);
                free(queue);
                return 0;
            default:
                printf("\nWrong option!");
                break;
        }
    } while (1);

    return 0;
}
