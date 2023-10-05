#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showArray(int *array, int n) {
    printf("\narray: { ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("}\n\n");
}

int* createArray(int n) {
    int *array = (int *)malloc(n * sizeof(int));

    srand(time(NULL));

    if (array == NULL) {
        printf("\n...Memory allocation error...\n");
        return (NULL);
    } else {
        printf("\nSuccessfully allocated memory!\n");
        for (int i = 0; i < n; i++) {
            array[i] = rand() % 100;
        }
        showArray(array, n);
        return (array);
    }
}

void destroyArray(int *array) {
    if (array == NULL) {
        printf("\n...Memory release error...\n\n");
    } else {
        free(array);
        printf("\nSuccessfully freed memory!\n\n");
    }
}

int main() {
    int length;
    printf("\n\nEnter a length of the array: ");
    scanf(" %d", &length);
    while (length <= 0) {
        printf("\nInvalid input. Try again: ");
        scanf(" %d", &length);
    }

    int *array = createArray(length);
    destroyArray(array);

    return (0);
}
