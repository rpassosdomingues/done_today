#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int *elements;
    int front;
    int back;
    int length;
} Queue;

void init(Queue *queue, int size) {
    queue->elements = (int *)malloc(sizeof(int) * size);
    queue->front = -1;
    queue->back = -1;
    queue->length = size;
}

int isFull(Queue *queue) {
    return (queue->back + 1) % queue->length == queue->front;
}

int isEmpty(Queue *queue) {
    return queue->front == -1;
}

void insert(Queue *queue, int data) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot insert.\n");
        return;
    }
    
    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->back = (queue->back + 1) % queue->length;
    queue->elements[queue->back] = data;
}

int removeElement(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot remove.\n");
        return -1; // Or some other error value
    }

    int data = queue->elements[queue->front];

    if (queue->front == queue->back) {
        // Queue has only one element, reset front and back to -1
        queue->front = -1;
        queue->back = -1;
    } else {
        queue->front = (queue->front + 1) % queue->length;
    }

    return data;
}

// Function to display the menu
void display_menu() {
    printf("---------------------------\n");
    printf("\t Menu \n");
    printf("---------------------------\n");
    printf("0. Quit\n");
    printf("...........................\n");
    printf("1. Insert into the queue\n");
    printf("2. Remove from the queue\n");
    printf("3. Print the queue\n");
    printf("---------------------------\n");
    printf("Enter your choice: ");
}

void printQueue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    int i = queue->front;
    do {
        printf("%d ", queue->elements[i]);
        i = (i + 1) % queue->length;
    } while (i != (queue->back + 1) % queue->length);
    printf("\n");
}

int main() {
    Queue myQueue;
    int size = 5;

    init(&myQueue, size);

    int choice;
    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Quitting...\n");
                break;
            case 1:
                // Insert into the queue
                int data;
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                insert(&myQueue, data);
                break;
            case 2:
                // Remove from the queue
                printf("Removed: %d\n", removeElement(&myQueue));
                break;
            case 3:
                // Print the queue
                printQueue(&myQueue);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    free(myQueue.elements);

    return 0;
}
