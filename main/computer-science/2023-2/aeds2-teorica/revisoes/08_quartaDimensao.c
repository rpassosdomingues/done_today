#include <stdio.h>
#include <stdlib.h>

// Define as dimensões da figura 4D
#define DIM_X 3
#define DIM_Y 3
#define DIM_Z 3
#define DIM_T 3

// Preenche as posições de memória alocadas dinamicamente
void preenche_valores (int ****pont, int dim_x, int dim_y, int dim_z, int dim_t) {
    // Aloca a primeira dimensão (X)
    for (int i = 0; i < dim_x; i++) {
        // Aloca a segunda dimensão (Y)
        for (int j = 0; j < dim_y; j++) {
            // Aloca a terceira dimensão (Z)
            for (int k = 0; k < dim_z; k++) {
                // Aloca a quarta dimensão (tempo)
                for (int t = 0; t < dim_t; t++) {
                    pont[i][j][k][t] = i + j + k + t;
                }
            }
        }
    }
}

// Imprime na tela os valores alocados dinamicamente
void imprime_valores (int ****pont, int dim_x, int dim_y, int dim_z, int dim_t) {
    for (int i = 0; i < dim_x; i++) {
        for (int j = 0; j < dim_y; j++) {
            for (int k = 0; k < dim_z; k++) {
                for (int t = 0; t < dim_t; t++) {
                    printf("%4d ", pont[i][j][k][t]);
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
    }
}

// Libera a memória alocada dinamicamente
void desaloca_figura4D (int ****pont, int dim_x, int dim_y, int dim_z) {
    for (int i = 0; i < dim_x; i++) {
        for (int j = 0; j < dim_y; j++) {
            for (int k = 0; k < dim_z; k++) {
                free((pont)[i][j][k]);
            }
            free((pont)[i][j]);
        }
        free((pont)[i]);
    }
    free(pont);
}

int main () {
    int ****figura4D;

    // Aloca dinamicamente a figura 4D
    figura4D = (int ****)malloc(DIM_X * sizeof(int ***));
    for (int i = 0; i < DIM_X; i++) {
        figura4D[i] = (int ***)malloc(DIM_Y * sizeof(int **));
        for (int j = 0; j < DIM_Y; j++) {
            figura4D[i][j] = (int **)malloc(DIM_Z * sizeof(int *));
            for (int k = 0; k < DIM_Z; k++) {
                figura4D[i][j][k] = (int *)malloc(DIM_T * sizeof(int));
            }
        }
    }

    preenche_valores(figura4D, DIM_X, DIM_Y, DIM_Z, DIM_T);
    imprime_valores(figura4D, DIM_X, DIM_Y, DIM_Z, DIM_T);
    desaloca_figura4D(figura4D, DIM_X, DIM_Y, DIM_Z);

    return 0;
}
