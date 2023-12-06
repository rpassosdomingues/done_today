#ifndef SORTPLAYERS_H
#define SORTPLAYERS_H

// Define a struct to player object
typedef struct Player {
    char name[256];
    char position[64];
    char naturalness[64];
    char team[64];
    int age;
} Player;

void swapPlayers(Player *a, Player *b);

// Sort Algorithms
int bubbleSort(Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);
int selectionSort(Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);
int insertionSort(Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);

int mergeSort(Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);
int quickSort(Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage);

int getMax(Player array[], int length);
void countingSort(Player array[], int length, int exp, int* radixUsage, int* comparisons, int* exchanges);
int radixSort(Player playersArray[], int length, int* comparisons, int* exchanges, int* memoryUsage);

// Instance Reader
int readPlayers(Player playersArray[], int maxPlayers);

void printPlayer(Player player);
void printSortedPlayers(Player playersArray[], int numPlayers);

// Show Benchmarks
void sortMetrics(const char *sortName, double timeUsed, int comparisons, int exchanges, int memoryUsage);

void displayMenu();

#endif
