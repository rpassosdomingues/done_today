#include <stdio.h>
#include <stdlib.h>

// Define as dimensões do cubo
#define DIM_X 3
#define DIM_Y 3
#define DIM_Z 3

// Preenche as posições de memória alocadas dinamicamente
void preenche_valores (int ***pont, int dim_x, int dim_y, int dim_z) {
    // Aloca a primeira dimensão (x)
    for (int i = 0; i < dim_x; i++) {
        // Aloca a segunda dimensão (y)
        for (int j = 0; j < dim_y; j++) {
            // Aloca a terceira dimensão (z)
            for (int k = 0; k < dim_z; k++) {
                pont[i][j][k] = i + j + k;
            }
        }
    }
}

// Imprime na tela os valores alocados dinamicamente
void imprime_valores (int ***pont, int dim_x, int dim_y, int dim_z) {
    for (int i = 0; i < dim_x; i++) {
        for (int j = 0; j < dim_y; j++) {
            for (int k = 0; k < dim_z; k++) {
                printf("%4d ", pont[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

// Libera a memória alocada dinamicamente
void desaloca_cubo (int ***pont, int dim_x, int dim_y) {
    for (int i = 0; i < dim_x; i++) {
        for (int j = 0; j < dim_y; j++) {
            free((*pont)[i][j]);
        }
        free((*pont)[i]);
    }
    free(*pont);
}

int main () {
    int ***cubo;
    // Aloca o cubo tridimensional
    cubo = (int ***)malloc(DIM_X * sizeof(int **));
    for (int i = 0; i < DIM_X; i++) {
        cubo[i] = (int **)malloc(DIM_Y * sizeof(int *));
        for (int j = 0; j < DIM_Y; j++) {
            cubo[i][j] = (int *)malloc(DIM_Z * sizeof(int));
        }
    }

    preenche_valores(cubo, DIM_X, DIM_Y, DIM_Z);
    imprime_valores(cubo, DIM_X, DIM_Y, DIM_Z);
    desaloca_cubo(cubo, DIM_X, DIM_Y);

    return 0;
}
