#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int front;
    int rear;
    int size;
    int *items;
} Queue;

Queue* createQueue(int size) {
    Queue *newQueue = malloc(sizeof(Queue));
    if (newQueue == NULL) {
        printf("\n! Memory allocation error !\n");
        return NULL;
    } else {
        newQueue->size = size;
        newQueue->front = -1;
        newQueue->rear = -1;
        newQueue->items = (int *)malloc(sizeof(int) * size);
        if (newQueue->items == NULL) {
            printf("\n! Memory allocation error for queue items !\n");
            free(newQueue);
            return NULL;
        }
        printf("\n Memory allocated successfully!\n");
        return newQueue;
    }
}

int isFull(Queue *queue) {
    return (queue->rear == queue->size - 1);
}

int isEmpty(Queue *queue) {
    return (queue->front == -1);
}

void enqueue(Queue *queue, int value) {
    if (isFull(queue)) {
        printf("\n Queue is full. Cannot enqueue.\n");
    } else {
        if (isEmpty(queue)) {
            queue->front = 0;
        }
        queue->items[++queue->rear] = value;
        printf("\n Enqueued %d into the queue.\n", value);
    }
}

void dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("\n Queue is empty. Cannot dequeue.\n");
    } else {
        int dequeued = queue->items[queue->front++];
        printf("\n Dequeued %d from the queue.\n", dequeued);
        if (queue->front > queue->rear) {
            // Reset queue when it becomes empty
            queue->front = queue->rear = -1;
        }
    }
}

void showQueue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("\n Queue is empty.\n");
    } else {
        printf("\n Queue contents (front to rear):\n");
        for (int i = queue->front; i <= queue->rear; i++) {
            printf("%d ", queue->items[i]);
        }
        printf("\n");
    }
}

void showMenu(int *choice) {
    printf("---------------------------\n");
    printf("\t Menu \n");
    printf("---------------------------\n");
    printf("0. Quit\n");
    printf("...........................\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Show Queue\n");
    printf("---------------------------\n");
    printf("Enter your choice (0-3): ");
    scanf("%d", choice);
    while (*choice < 0 || *choice > 3) {
        printf("Invalid input, try again: ");
        scanf("%d", choice);
    }
}

int main() {
    Queue *queue = NULL;
    int size;

    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    queue = createQueue(size);
    if (queue == NULL) {
        return 1; // Error in creating the queue
    }

    int choice;
    do {
        showMenu(&choice);
        switch (choice) {
            case 0:
                break;
            case 1:
                int value;
                printf("\tEnter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                dequeue(queue);
                break;
            case 3:
                showQueue(queue);
                break;
            default:
        }
    } while (choice != 0);

    free(queue->items);
    free(queue);
    return 0;
}
