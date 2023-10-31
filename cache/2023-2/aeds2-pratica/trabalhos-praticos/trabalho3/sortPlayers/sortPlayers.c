#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sortPlayers.h"

// Function to read player data from the file
int readPlayers(struct Player playersArray[], int maxPlayers) {
    FILE *file = fopen("players.csv", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return (0);
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

// Function to print a player
void printPlayer(struct Player player) {
    printf("Name: %s, Position: %s, Naturalness: %s, Age: %d\n", player.name, player.position, player.naturalness, player.age);
}

// Function to swap two players
void swapPlayers(struct Player *a, struct Player *b) {
    struct Player temp = *a;
    *a = *b;
    *b = temp;
}

int bubbleSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage) {
    int bubbleUsage = 0; // Counter for Bubble Sort usage
    int i, j;
    *comparisons = 0; // Initialize comparisons count
    *exchanges = 0;   // Initialize exchanges count
    *memoryUsage = sizeof(struct Player) * length; // Memory usage is the size of the array

    for (i = 0; i < length - 1; i++) {
        for (j = 0; j < length - i - 1; j++) {
            (*comparisons)++; // Increment comparisons count
            if (strcmp(array[j].name, array[j + 1].name) > 0) {
                swapPlayers(&array[j], &array[j + 1]);
                (*exchanges)++;  // Increment exchanges count
            }
        }
    }
    return (bubbleUsage);
}

// Function to perform Selection Sort
int selectionSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage) {
    int selectionUsage = 0; // Counter for Selection Sort usage
    int i, j;
    *comparisons = 0; // Initialize comparisons count
    *exchanges = 0;   // Initialize exchanges count
    *memoryUsage = sizeof(struct Player) * length; // Memory usage is the size of the array

    for (i = 0; i < length - 1; i++) {
        int minIndex = i;
        for (j = i + 1; j < length; j++) {
            (*comparisons)++; // Increment comparisons count
            if (strcmp(array[j].name, array[minIndex].name) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swapPlayers(&array[i], &array[minIndex]);
            (*exchanges)++;  // Increment exchanges count
        }
    }
    return (selectionUsage);
}

// Function to perform Insertion Sort
int insertionSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage) {
    int insertionUsage = 0; // Counter for Insertion Sort usage
    int i, j;
    *comparisons = 0; // Initialize comparisons count
    *exchanges = 0;   // Initialize exchanges count
    *memoryUsage = sizeof(struct Player) * length; // Memory usage is the size of the array

    for (i = 1; i < length; i++) {
        struct Player handle = array[i];
        j = i - 1;
        while (j >= 0 && strcmp(array[j].name, handle.name) > 0) {
            array[j + 1] = array[j];
            (*comparisons)++; // Increment comparisons count
            (*exchanges)++;   // Increment exchanges count
            j--;
        }
        array[j + 1] = handle;
    }
    return (insertionUsage);
}

// Function to perform Merge Sort and count merge operations
int mergeSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage) {
    int mergeUsage = 0; // Counter for Merge Sort usage

    if (length <= 1) {
        return mergeUsage; // No need to sort an array of length 0 or 1
    }

    int middle = length / 2;
    int leftLength = middle;
    int rightLength = length - middle;

    struct Player leftArray[leftLength];
    struct Player rightArray[rightLength];

    // Copy data to left and right sub-arrays
    for (int i = 0; i < leftLength; i++) {
        leftArray[i] = array[i];
    }
    for (int i = 0; i < rightLength; i++) {
        rightArray[i] = array[i + middle];
    }

    mergeUsage += leftLength + rightLength; // Count the copy operations

    mergeUsage += mergeSort(leftArray, leftLength, comparisons, exchanges, memoryUsage);
    mergeUsage += mergeSort(rightArray, rightLength, comparisons, exchanges, memoryUsage);

    int i = 0, j = 0, k = 0;
    while (i < leftLength && j < rightLength) {
        (*comparisons)++; // Comparison operation
        if (strcmp(leftArray[i].name, rightArray[j].name) <= 0) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
        (*exchanges)++;  // Increment exchanges count
    }

    while (i < leftLength) {
        array[k] = leftArray[i];
        i++;
        k++;
        (*exchanges)++;  // Increment exchanges count
    }

    while (j < rightLength) {
        array[k] = rightArray[j];
        j++;
        k++;
        (*exchanges)++;  // Increment exchanges count
    }

    return (mergeUsage);
}

// Function to perform Quick Sort
int quickSort(struct Player array[], int length, int* comparisons, int* exchanges, int* memoryUsage) {
    int quickUsage = 0; // Counter for Quick Sort usage

    if (length <= 1) {
        return quickUsage; // No need to sort an array of length 0 or 1
    }

    int pivotIndex = length / 2; // Choose a pivot element (e.g., middle element)
    struct Player pivot = array[pivotIndex];

    struct Player leftArray[length];
    struct Player rightArray[length];

    int leftLength = 0;
    int rightLength = 0;

    for (int i = 0; i < length; i++) {
        if (i == pivotIndex) {
            continue; // Skip the pivot element
        }
        (*comparisons)++; // Comparison operation
        if (strcmp(array[i].name, pivot.name) <= 0) {
            leftArray[leftLength] = array[i];
            leftLength++;
        } else {
            rightArray[rightLength] = array[i];
            rightLength++;
        }
        (*exchanges)++; // Increment exchanges count
    }

    quickUsage += leftLength + rightLength; // Count the copy operations

    quickUsage += quickSort(leftArray, leftLength, comparisons, exchanges, memoryUsage);
    quickUsage += quickSort(rightArray, rightLength, comparisons, exchanges, memoryUsage);

    for (int i = 0; i < leftLength; i++) {
        array[i] = leftArray[i];
    }
    for (int i = 0; i < rightLength; i++) {
        array[leftLength + i] = rightArray[i];
    }
    quickUsage += leftLength + rightLength; // Count the copy operations

    return (quickUsage);
}

// Function to display sorting results
void sortMetrics(const char *sortName, double timeUsed, int comparisons, int exchanges, int memoryUsage) {
    printf("\n===============================================");
    printf("\n\t%s Sort Performance Metrics", sortName);
    printf("\n-----------------------------------------------");
    printf("\nTime taken: %.4f milliseconds", timeUsed);
    printf("\nComparison operations: %d", comparisons);
    printf("\nExchange operations: %d", exchanges);
    printf("\nMemory used: %d bytes", memoryUsage);
    printf("\n===============================================");
}

void displayMenu() {
    printf("\n===============================");
    printf("\n\t MENU");
    printf("\n===============================");
    printf("\n0. Exit");
    printf("\n1. Bubble Sort");
    printf("\n2. Selection Sort");
    printf("\n3. Insertion Sort");
    printf("\n4. Merge Sort");
    printf("\n5. Quick Sort");
    printf("\n===============================");
}

int main() {
    // Read player data from the file
    int maxPlayers = 100; // Maximum number of players to read
    struct Player playersArray[maxPlayers];
    int numPlayers = readPlayers(playersArray, maxPlayers);

    if (numPlayers == 0) {
        return (1);
    }

    int choice = -1;
    while (1) {
        displayMenu();
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);

        // Initialize clock to time benckmark
        clock_t start_time, end_time;
        double cpu_time_used = 0;

        // Initialize memory acess metrics
        int comparisons = 0;
        int exchanges = 0;
        int memoryUsage = 0;

        switch (choice) {
            case 0:
                // </> Halt </>.
                return 0;
            case 1:
                // Bubble Sort Time benchmark
                start_time = clock();
                bubbleSort(playersArray, numPlayers, &comparisons, &exchanges, &memoryUsage);
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Bubble Sort performance metrics
                sortMetrics("Bubble", cpu_time_used, comparisons, exchanges, memoryUsage);
                break;
            case 2:
                // Selection Sort Time benchmark
                start_time = clock();
                selectionSort(playersArray, numPlayers, &comparisons, &exchanges, &memoryUsage);
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Selection Sort performance metrics
                sortMetrics("Selection", cpu_time_used, comparisons, exchanges, memoryUsage);
                break;
            case 3:
                // Insertion Sort Time benchmark
                start_time = clock();
                insertionSort(playersArray, numPlayers, &comparisons, &exchanges, &memoryUsage);
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Insertion Sort performance metrics
                sortMetrics("Insertion", cpu_time_used, comparisons, exchanges, memoryUsage);
                break;
            case 4:
                // Merge Sort Time benchmark
                start_time = clock();
                mergeSort(playersArray, numPlayers, &comparisons, &exchanges, &memoryUsage);
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Merge Sort performance metrics
                sortMetrics("Merge", cpu_time_used, comparisons, exchanges, memoryUsage);
                break;
            case 5:
                // Quick Sort Time benchmark
                start_time = clock();
                quickSort(playersArray, numPlayers, &comparisons, &exchanges, &memoryUsage);
                end_time = clock();
                cpu_time_used = ((double)(1000 * (end_time - start_time))) / CLOCKS_PER_SEC;

                // Quick Sort performance metrics
                sortMetrics("Quick", cpu_time_used, comparisons, exchanges, memoryUsage);
                break;
            default:
                printf("\nInvalid Output!");
                break;
        }
    }
}
