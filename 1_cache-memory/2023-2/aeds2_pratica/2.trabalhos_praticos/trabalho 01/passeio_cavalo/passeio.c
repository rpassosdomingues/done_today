#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "passeio.h"

void printTabuleiro(bool **tabuleiro, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int x, int y, int n, int m, bool **tabuleiro) {
    return (x >= 0 && x < n && y >= 0 && y < m && !tabuleiro[x][y]);
}

bool solveKT(int x, int y, int movei, int n, int m, bool **tabuleiro, int xMove[], int yMove[]) {
    if (movei == n * m) {
        return true;
    }

    for (int k = 0; k < 8; k++) {
        int next_x = x + xMove[k];
        int next_y = y + yMove[k];
        if (isSafe(next_x, next_y, n, m, tabuleiro)) {
            tabuleiro[next_x][next_y] = true;
            if (solveKT(next_x, next_y, movei + 1, n, m, tabuleiro, xMove, yMove)) {
                return true;
            } else {
                tabuleiro[next_x][next_y] = false;
            }
        }
    }
    return false;
}

void computa_passeios(bool **tabuleiro, int n, int m) {
    int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (int startX = 0; startX < n; startX++) {
        for (int startY = 0; startY < m; startY++) {
            // Não é necessário inicializar a matriz aqui
            // tabuleiro[startX][startY] = true;

            if (solveKT(startX, startY, 1, n, m, tabuleiro, xMove, yMove)) {
                printf("Solução encontrada a partir da posição inicial (%d, %d):\n", startX, startY);
                printTabuleiro(tabuleiro, n, m);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 20) {
        printf("Para executar o código, digite ./passeio x\nonde x é um número entre 1 e 20 que simboliza a instância utilizada\n");
        exit(0);
    }

    int n, m;
    bool **tabuleiro;

    // Leitura do tamanho do tabuleiro
    scanf("%d%d", &n, &m);

    // Alocação dinâmica do tabuleiro
    tabuleiro = (bool **)malloc(n * sizeof(bool *));
    for (int i = 0; i < n; i++) {
        tabuleiro[i] = (bool *)malloc(m * sizeof(bool));
    }

    computa_passeios(tabuleiro, n, m);

    // Liberação de memória
    for (int i = 0; i < n; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 1;
}

