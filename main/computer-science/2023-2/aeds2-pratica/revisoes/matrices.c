#include <stdio.h>

int calculateDeterminant(int matrix[3][3]) {
    int determinant = 0;

    for (int i = 0; i < 3; i++) {
        determinant += (matrix[0][i] * (matrix[1][(i + 1) % 3] * matrix[2][(i + 2) % 3] -
                                       matrix[1][(i + 2) % 3] * matrix[2][(i + 1) % 3]));
    }

    return determinant;
}

void multiplyMatrices(int n, int m1[][n], int m2[][n], int result[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0; // Inicialize o resultado para zero
            for (int k = 0; k < n; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void sumMatrices(int n, int array1[][n], int array2[][n], int result[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = array1[i][j] + array2[i][j];
        }
    }
}

void showArray(int n, int array[][n]) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int array1[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int array2[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int result[3][3];

    printf("Array 1");
    showArray(3, array1);

    printf("Array 2");
    showArray(3, array2);

    sumMatrices(3, array1, array2, result);
    printf("Sum");
    showArray(3, result);

    multiplyMatrices(3, array1, array2, result);
    printf("Multiply");
    showArray(3, result);

    int determinant = calculateDeterminant(array1);
    printf("Determinant: %d\n", determinant);

    return 0;
}
