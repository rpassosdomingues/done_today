/**
 * This code computes the paths of the
 * horse's walk across the chessboard.
 * 
 * Author's: Rafael Passos Domingues and Bing [AI]
 * Sep 27 Wed, 2023
 * 
 * This code was developed with careful consultation 
 * with Bing artificial intelligence.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "horseWalk.h"

/**
 * Creates a new node with the given x and y coordinates.
 * It allocates memory for the new node using the
 * malloc function, sets the node coordinates, and
 * initializes the next and prev pointers to NULL.
 */
Horse* newHouse(int x, int y) {
    Horse* horse = (Horse*)malloc(sizeof(Horse));
    horse->x = x;
    horse->y = y;
    horse->next = NULL;
    horse->prev = NULL;
    return horse;
}

/**
 * This function adds a new node with x and y coordinates
 * to the end of the linked list.
 * 
 * If the list is empty (that is, if the list head is NULL),
 * it sets the list head as the new node.
 * 
 * Otherwise, it traverses the list to the end and adds
 * the new node there.
 */
void addHouse(Horse** head, int x, int y) {
    Horse* horse = newHouse(x, y);
    if (*head == NULL) {
        *head = horse;
    } else {
        Horse* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = horse;
        horse->prev = temp;
    }
}

void addEnd(Horse* start, int x, int y) {
    Horse* lastHouse = newHouse(x, y);
    Horse* temp = start;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = lastHouse;
    lastHouse->prev = temp;
}

/**
 * This function prints the coordinates of each node in the linked list.
 * 
 * It starts at the head node of the list and follows the next pointers until
 * it reaches the end of the list.
 */
void printList(Horse* head) {
    Horse* temp = head;
    while (temp != NULL) {
        printf("(%d, %d)\n", temp->x, temp->y);
        temp = temp->next;
    }
}

/**
 * Check whether a move is valid within the chessboard
 */
int validMove(int x, int y, int N, int M) {
    return (x >= 0 && x < M && y >= 0 && y < N);
}

/**
 * Check if all squares on the chessboard have been visited
 */
int allHouses(int** visited, int N, int M) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int countTripsClosed(Horse horse, int N, int M, bool **chessboard) {
    int** visited = (int**)malloc(M * sizeof(int*));
    for (int i = 0; i < M; i++) {
        visited[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }

    Horse* list = newHouse(horse.x, horse.y);
    int countClosed = 0;

    while (list != NULL) {
    int x = list->x;
    int y = list->y;
    visited[x][y] = 1;
    Horse* next = list->next;

    for (int i = 0; i < 8; i++) {
        int newX = x + horse.moves[i][0];
        int newY = y + horse.moves[i][1];
        if (validMove(newX, newY, M, N) && !visited[newX][newY] && !chessboard[newX][newY]) {
            if (next == NULL && allHouses(visited, M, N) && newX == horse.x && newY == horse.y) {
                countClosed++;
            } else {
                addEnd(next, newX, newY);
            }
            visited[newX][newY] = 0;
        }
    }
        free(list);
        list = next;
    }

    for (int i = 0; i < M; i++) {
        free(visited[i]);
    }
    free(visited);

    return countClosed;
}

void calculatesTrips(bool **chessboard, int N, int M) {
    int closed = 0;
    int open = 0;

    // Possible movements of the horse.
    Horse horse = {0, 0, {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}}};
    closed = countTripsClosed(horse, N, M, chessboard);

    printf("%d\n%d\n", closed, open);
}

int main(int argc, char* argv[]) {
    int instance_num = -1;
    instance_num = atoi(argv[1]);
    if (instance_num <= 0 || instance_num > 10) {
        printf("To run the code, type ./horseWalk x\nwhere x is a number between 1 and 10 that symbolizes the instance used.\n");
        exit(0);
    }

    // Dimensions of the chessboard
    int n, m;

    // Create the chessboard
    bool **chessboard = readInstance(instance_num, &n, &m);

    calculatesTrips(chessboard, n, m);

    return 0;
}

bool **readInstance(int instance_num, int *n, int *m) {
    int i;
    // Mount the trip to instance
    char *file_instance = "./instances/";
    asprintf(&file_instance, "%s%d", file_instance, instance_num);

    // Pointer to instance
    FILE* file;

    // Open the instance in read mode
    file = fopen(file_instance, "r");

    if (NULL == file) {
        printf("Instance file not found! Check your directories.\n");
        exit(0);
    }

    // Read the instances file
    fscanf(file, "%d", n);
    fscanf(file, "%d", m);

    // Allocating the chessboard dynamically
    // Using calloc instead of malloc to initialize the entire chessboard with zeros
    bool** chessboard = (bool**)calloc(*n, sizeof(bool*));
    for (i = 0; i < *n; i++) {
        chessboard[i] = (bool*)calloc(*m, sizeof(bool));
    }
    return chessboard;
}
