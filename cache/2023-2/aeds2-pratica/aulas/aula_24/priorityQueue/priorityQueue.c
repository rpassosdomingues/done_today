#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorityQueue.h"

// Function to read player data from the file
int readPlayers(Player playersArray[], int maxPlayers) {
    FILE *file = fopen("players.csv", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return (1);
    }

    int count = 0;
    char line[256]; // Assuming each line is at most 256 characters

    // Skip the header line
    fgets(line, sizeof(line), file);

    while (count < maxPlayers && fgets(line, sizeof(line), file)) {
        // Parse the CSV line into struct fields
        char *token = strtok(line, ",");
        strcpy(playersArray[count].name, token);

        token = strtok(NULL, ",");
        strcpy(playersArray[count].position, token);

        token = strtok(NULL, ",");
        strcpy(playersArray[count].naturalness, token);

        token = strtok(NULL, ",");
        playersArray[count].age = atoi(token);

        count++;
    }
    fclose(file);

    return (count);
}

void initQueue(Queue *queue, int size) {
    queue->players = (int *)malloc(sizeof(int) * size);
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

void insertPlayer(Queue *queue, Player player) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot insert.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->back = (queue->back + 1) % queue->length;
    queue->players[queue->back] = player.age;
}

int removePlayer(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot remove.\n");
        return -1; // Or some other error value
    }

    int data = queue->players[queue->front];

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
    printf("\n===========================");
    printf("\n\t Menu");
    printf("\n===========================");
    printf("\n0. Quit");
    printf("\n...........................");
    printf("\n1. Insert into the queue");
    printf("\n2. Remove from the queue");
    printf("\n===========================");
    printf("\nChoose an option: ");
}

int main() {
    Queue myQueue;
    int numPlayers = 1150;
    int size = numPlayers;

    initQueue(&myQueue, size);

    Player playersArray[numPlayers];
    int playerCount = readPlayers(playersArray, numPlayers);

    int option;

    do {
        display_menu();
        scanf("%d", &option);

        switch (option) {
            case 0:
                free(myQueue.players);
                return 0;
            case 1:
                double time_insert = 0;

                clock_t begin_insert = clock();
                for (int i = 0; i < playerCount; i++) {
                    insertPlayer(&myQueue, playersArray[i]);
                }
                clock_t end_insert = clock();

                time_insert += (double)(end_insert - begin_insert) / CLOCKS_PER_SEC;
                printf("\n\t Time Insertion = %lf ms", 1000 * time_insert);

                break;
            case 2:
                double time_remove = 0;

                clock_t begin_remove = clock();
                removePlayer(&myQueue);
                clock_t end_remove = clock();

                time_remove += (double)(end_remove - begin_remove) / CLOCKS_PER_SEC;
                printf("\n\t Time Removed = %lf ms", 1000 * time_remove);

                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);
}
