/**
 * Relação entre vetores, matrizes e abstração de figuras multidimensionais
*/

#include <stdio.h>
#include <stdlib.h>

// Preenche as posições de memória alocadas dinamicamente
void preenche_valores (int (**pont), int num_linhas, int num_colunas) {
    // Cada posição de linha recebe um malloc com um número de colunas
    for (int i = 0; i < num_linhas; i++) {
        *(pont + i) = malloc(num_colunas * sizeof(int));
        // Percorre as colunas
        for (int j = 0; j < num_colunas; j++) {
            *(*(pont + i) + j) = i + j;
            //pont[i][j] = i + j;
        }
    }
}

// Imprime na tela os valores alocados dinamicamente
void imprime_valores (int (**pont), int num_linhas, int num_colunas) {
    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            printf("%4d ", *(*(pont + i) + j));
            //printf("%4d ", pont[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Libera a memória alocada dinamicamente
void desaloca_matriz (int (**pont), int num_linhas) {
    // Cada posição de linha é desalocada com um número de colunas
    for (int i = 0; i < num_linhas; i++) {
        free(*(pont + i));
    }
    free(pont);
}

int main () {
    int num_linhas = 2;
    int num_colunas = 4;
    // Aloca o ponteiro de ponteiro
    int **pont;
    // Aloca um vetor de linhas
    pont = malloc(num_linhas * sizeof(int*));

    preenche_valores(pont, num_linhas, num_colunas);
    imprime_valores(pont, num_linhas, num_colunas);
    desaloca_matriz(pont, num_linhas);

    return 0;
}
