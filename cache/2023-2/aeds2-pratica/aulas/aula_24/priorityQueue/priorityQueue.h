#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct queue {
    int key;
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
int readPlayers(struct Player playersArray[], int maxPlayers);
void printPlayer(struct Player player);

void initQueue(Queue *queue, int size);

int isFull(Queue *queue);
int isEmpty(Queue *queue);

void insertPlayer(Queue *queue, int data);
int removePlayer(Queue *queue);

void printPlayer(Player player);

void displayMenu();

#endif
