#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct queue {
    int *players;
    int front;
    int back;
    int length;
} Queue;

typedef struct player {
    char name[256];
    char position[64];
    char naturalness[64];
    int age;
} Player;

// Instance Reader
int readPlayers(Player playersArray[], int maxPlayers);

void initQueue(Queue *queue, int size);
int isFull(Queue *queue);
int isEmpty(Queue *queue);

void insertPlayer(Queue *queue, Player player);
int removePlayer(Queue *queue);

void displayMenu();

#endif
