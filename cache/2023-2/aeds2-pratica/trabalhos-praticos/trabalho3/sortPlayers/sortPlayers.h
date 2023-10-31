#ifndef SORTPLAYERS_H
#define SORTPLAYERS_H

// Define a struct to player object
struct Player {
    char name[256];
    char position[64];
    char naturalness[64];
    int age;
};

// Instance Reader
int readPlayers(struct Player playersArray[], int maxPlayers);
void printPlayer(struct Player player);

void swapPlayers(struct Player *a, struct Player *b);

// Sort Algorithms
int bubbleSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);
int selectionSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);
int insertionSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);
int mergeSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);
int quickSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);

// Print Benchmarks
void sortMetrics(const char *sortName, double timeUsed, int comparisons, int exchanges, int memoryUsage);

void displayMenu();

#endif
