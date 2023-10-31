#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Bubble Sort
int bubbleSort(int array[], int length) {
  int bubbleUsage = 0; // Counter for Bubble Sort usage
  int i, j;
  for (i = 0; i < length - 1; i++) {
    bubbleUsage += 2; // Increment counter for Bubble Sort usage
    for (j = 0; j < length - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
      }
      bubbleUsage += 4;
    }
  }
  return (bubbleUsage);
}

// Function to perform Selection Sort
int selectionSort(int array[], int length) {
  int selectionUsage = 0; // Counter for Selection Sort usage
  int i, j;
  for (i = 0; i < length - 1; i++) {
    int minIndex = i;
    selectionUsage += 2; // Increment counter for Selection Sort usage
    for (j = i + 1; j < length; j++) {
      if (array[j] < array[minIndex]) {
        minIndex = j;
      }
    }
    int swap = array[i];
    array[i] = array[minIndex];
    array[minIndex] = swap;
    selectionUsage += 4;
  }
  return (selectionUsage);
}

// Function to perform Insertion Sort
int insertionSort(int array[], int length) {
  int insertionUsage = 0; // Counter for Insertion Sort usage
  int i, j;
  for (i = 1; i < length; i++) {
    int handle = array[i];
    insertionUsage += 2; // Increment counter for Insertion Sort usage
    for (j = i - 1; j >= 0 && array[j] > handle; j--) {
      array[j + 1] = array[j];
      insertionUsage += 3;
    }
    array[j + 1] = handle;
  }
  return (insertionUsage);
}

// Function to copy the elements from source to destination array
void copyArray(int source[], int destination[], int length) {
  for (int i = 0; i < length; i++) {
    destination[i] = source[i];
  }
}

// Function to perform Merge Sort and count merge operations
int mergeSort(int array[], int length) {
  int mergeUsage = 0; // Counter for Merge Sort usage
  if (length <= 1) {
    return mergeUsage; // No need to sort an array of length 0 or 1
  }

  int middle = length / 2;
  int leftLength = middle;
  int rightLength = length - middle;

  int leftArray[leftLength];
  int rightArray[rightLength];

  // Copy data to left and right sub-arrays using the copyArray function
  copyArray(array, leftArray, leftLength);
  mergeUsage += leftLength; // Count the copy operations

  copyArray(array + middle, rightArray, rightLength);
  mergeUsage += rightLength; // Count the copy operations

  // Recursively sort the left and right sub-arrays
  mergeUsage += mergeSort(leftArray, leftLength);
  mergeUsage += mergeSort(rightArray, rightLength);

  // Merge the sorted sub-arrays
  int i = 0, j = 0, k = 0;
  while (i < leftLength && j < rightLength) {
    if (leftArray[i] <= rightArray[j]) {
      array[k] = leftArray[i];
      i++;
    } else {
      array[k] = rightArray[j];
      j++;
    }
    mergeUsage += 3; // Comparison and assignment operations
    k++;
  }

  // Copy the remaining elements of leftArray, if any
  while (i < leftLength) {
    array[k] = leftArray[i];
    i++;
    k++;
    mergeUsage += 2; // Assignment operations
  }

  // Copy the remaining elements of rightArray, if any
  while (j < rightLength) {
    array[k] = rightArray[j];
    j++;
    k++;
    mergeUsage += 2; // Assignment operations
  }

  return (mergeUsage);
}

// Function to perform Quick Sort
int quickSort(int array[], int length) {
  int quickUsage = 0; // Counter for Quick Sort usage
  if (length <= 1) {
    return quickUsage; // No need to sort an array of length 0 or 1
  }

  // Choose a pivot element (for simplicity, we'll choose the last element)
  int pivot = array[length - 1];
  int i = -1;

  for (int j = 0; j < length - 1; j++) {
    if (array[j] <= pivot) {
      // Swap array[i] and array[j]
      int temp = array[++i];
      array[i] = array[j];
      array[j] = temp;
      quickUsage += 3; // Three assignment operations
    }
    quickUsage++; // Comparison operation
  }

  // Swap array[i + 1] and pivot
  int temp = array[i + 1];
  array[i + 1] = array[length - 1];
  array[length - 1] = temp;
  quickUsage += 3; // Three assignment operations

  // Recursively sort the elements on the left and right of the pivot
  quickUsage += quickSort(array, i + 1); // Sort elements less than or equal to the pivot
  quickUsage += quickSort(array + i + 2, length - i - 2); // Sort elements greater than the pivot

  return (quickUsage);
}

// Function to generate an ordered array and shuffle it
void randomArrayGenerator(int step, int length, int randomArray[]) {
    for (int i = 0; i < length; i++) {
        randomArray[i] = i;
    }

    // shuffle array
    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = randomArray[i];
        randomArray[i] = randomArray[j];
        randomArray[j] = temp;
    }

    for (int i = 0; i < length; i++) {
        randomArray[i] += step;
    }
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
  // Inicialize a semente
  srand(time(NULL));

  int length = 50;
  int step = 10;

  int array[length];
  randomArrayGenerator(step, length, array);

  int choice = -1;
  while (1) {
    displayMenu();
    printf("\n\tEnter your choice: ");
    scanf("%d", &choice);

    clock_t start_time, end_time;
    double cpu_time_used;
    int memoryUsage = 0;

    switch (choice) {
      case 0:
        return 0;
      case 1:
        // Bubble Sort Time benchmark
        start_time = clock();
        memoryUsage = bubbleSort(array, length);
        end_time = clock();
        cpu_time_used = ((double)(1000*(end_time - start_time))) / CLOCKS_PER_SEC;
        printf("Bubble Sort took %.9f milliseconds to complete\n", cpu_time_used);
        printf("%d Memory Acess.\n", memoryUsage);
        break;
      case 2:
        // Selection Sort Time benchmark
        start_time = clock();
        memoryUsage = selectionSort(array, length);
        end_time = clock();
        cpu_time_used = ((double)(1000*(end_time - start_time))) / CLOCKS_PER_SEC;
        printf("Selection Sort took %.9f milliseconds to complete\n", cpu_time_used);
        printf("%d Memory Acess.\n", memoryUsage);
        break;
      case 3:
        // Insertion Sort Time benchmark
        start_time = clock();
        memoryUsage = insertionSort(array, length);
        end_time = clock();
        cpu_time_used = ((double)(1000*(end_time - start_time))) / CLOCKS_PER_SEC;
        printf("Insertion Sort took %.9f milliseconds to complete\n", cpu_time_used);
        printf("%d Memory Acess.\n", memoryUsage);
        break;
      case 4:
        // Merge Sort Time benchmark
        start_time = clock();
        memoryUsage = mergeSort(array, length);
        end_time = clock();
        cpu_time_used = ((double)(1000*(end_time - start_time))) / CLOCKS_PER_SEC;
        printf("Merge Sort took %.9f milliseconds to complete\n", cpu_time_used);
        printf("%d Memory Acess.\n", memoryUsage);
        break;
      case 5:
        // Quick Sort Time benchmark
        start_time = clock();
        memoryUsage = quickSort(array, length);
        end_time = clock();
        cpu_time_used = ((double)(1000*(end_time - start_time))) / CLOCKS_PER_SEC;
        printf("Quick Sort took %.9f milliseconds to complete\n", cpu_time_used);
        printf("%d Memory Acess.\n", memoryUsage);
        break;
      default:
        printf("\nInvalid Output!");
        break;
    }
  }
}
