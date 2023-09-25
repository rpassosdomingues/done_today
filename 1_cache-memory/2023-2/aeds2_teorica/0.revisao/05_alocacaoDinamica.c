/**
 * Alocação dinâmica de memória
 * Aritmética de ponteiros
 * Passagem de parâmetro por referência
*/

#include <stdio.h>
#include <stdlib.h>

// Preenche as posições de memória alocadas dinamicamente
void preenche_valores (int (*pont), int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        // Endereço contido em pont + i * sizeof(int)
        *(pont + i) = i + i;
        //p[i] = i + i;
    }
}

// Imprime na tela os valores alocados dinamicamente
void imprime_valores (int (*pont), int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", *(pont + i));
        //printf("%d ", p[i]);
    }
}

int main () {
    // Aloca dinamicamente 4 posições de memória do tamanho de um inteiro
    int num_elementos = 4;
    int *pont = malloc(num_elementos * sizeof(int));

    // Mostra, por debaixo dos panos, a quantidade de bytes demandados por cada tipo de variável
    printf("Um inteiro ocupa %d Bytes de memoria.\n", sizeof(int));
    printf("Um float ocupa %d Bytes de memoria.\n", sizeof(double));

    preenche_valores(pont, num_elementos);
    imprime_valores(pont, num_elementos);
    
    // Libera a memória alocada dinamicamente
    free(pont);

    return 0;
}
