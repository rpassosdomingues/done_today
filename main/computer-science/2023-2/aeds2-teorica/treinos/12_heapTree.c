/**
 * Heap Tree (Min Heap and Max Heap)
 */

#include<stdio.h>
#include<stdlib.h>

// Node structure for the heap
typedef struct _heap_node {
    int value;
} heap_node;

// Heap structure
typedef struct _heap {
    heap_node *elements; // Array to store elements
    int size;            // Current size of the heap
    int capacity;        // Maximum capacity of the heap
} heap;

// Function to swap two elements in the heap
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Implementation of Min Heap
void minHeapify(heap *h, int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // Compare with left child
    if (leftChild < h->size && h->elements[leftChild].value < h->elements[smallest].value) {
        smallest = leftChild;
    }

    // Compare with right child
    if (rightChild < h->size && h->elements[rightChild].value < h->elements[smallest].value) {
        smallest = rightChild;
    }

    // If the smallest value is not the current root, swap and recursively heapify
    if (smallest != index) {
        swap(&h->elements[index].value, &h->elements[smallest].value);
        minHeapify(h, smallest);
    }
}

// Function to build a Min Heap
void buildMinHeap(heap *h) {
    for (int i = (h->size - 2) / 2; i >= 0; i--) {
        minHeapify(h, i);
    }
}

// Implementation of Max Heap
void maxHeapify(heap *h, int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // Compare with left child
    if (leftChild < h->size && h->elements[leftChild].value > h->elements[largest].value) {
        largest = leftChild;
    }

    // Compare with right child
    if (rightChild < h->size && h->elements[rightChild].value > h->elements[largest].value) {
        largest = rightChild;
    }

    // If the largest value is not the current root, swap and recursively heapify
    if (largest != index) {
        swap(&h->elements[index].value, &h->elements[largest].value);
        maxHeapify(h, largest);
    }
}

// Function to build a Max Heap
void buildMaxHeap(heap *h) {
    for (int i = (h->size - 2) / 2; i >= 0; i--) {
        maxHeapify(h, i);
    }
}

// Function to insert a new value into the heap
void insertHeap(heap *h, int value) {
    if (h->size == h->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    h->size++;
    int index = h->size - 1;
    h->elements[index].value = value;

    // Reorganize the heap according to the property (min or max)
    int parent = (index - 1) / 2;

    if (h->elements[index].value < h->elements[parent].value) {
        while (index > 0 && h->elements[index].value < h->elements[parent].value) {
            swap(&h->elements[index].value, &h->elements[parent].value);
            index = parent;
            parent = (index - 1) / 2;
        }
    } else {
        while (index > 0 && h->elements[index].value > h->elements[parent].value) {
            swap(&h->elements[index].value, &h->elements[parent].value);
            index = parent;
            parent = (index - 1) / 2;
        }
    }
}

// Function to print the elements of the heap
void printHeap(heap *h) {
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->elements[i].value);
    }
    printf("\n");
}

// Function to display the menu options
void menu() {
    printf("================================\n");
    printf("Menu:\n");
    printf("--------------------------------\n");
    printf("0 - Exit\n");
    printf("1 - Insert into Min Heap\n");
    printf("2 - Insert into Max Heap\n");
    printf("3 - Print Min Heap\n");
    printf("4 - Print Max Heap\n");
    printf("================================\n");
}

int main() {
    heap minHeap;
    minHeap.capacity = 10;
    minHeap.size = 0;
    minHeap.elements = (heap_node *)malloc(minHeap.capacity * sizeof(heap_node));

    heap maxHeap;
    maxHeap.capacity = 10;
    maxHeap.size = 0;
    maxHeap.elements = (heap_node *)malloc(maxHeap.capacity * sizeof(heap_node));

    int option, value;

    do {
        menu();
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                free(minHeap.elements);
                free(maxHeap.elements);
                return 0;
            case 1:
                // Insert into Min Heap
                printf("Enter value to insert into Min Heap: ");
                scanf("%d", &value);
                insertHeap(&minHeap, value);
                printf("Value %d inserted into Min Heap.\n", value);
                break;
            case 2:
                // Insert into Max Heap
                printf("Enter value to insert into Max Heap: ");
                scanf("%d", &value);
                insertHeap(&maxHeap, value);
                printf("Value %d inserted into Max Heap.\n", value);
                break;
            case 3:
                // Print Min Heap
                printf("Min Heap: ");
                printHeap(&minHeap);
                break;
            case 4:
                // Print Max Heap
                printf("Max Heap: ");
                printHeap(&maxHeap);
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

}
