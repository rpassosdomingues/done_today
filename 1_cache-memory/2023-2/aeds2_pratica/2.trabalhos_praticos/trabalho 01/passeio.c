#include <stdio.h>
#include <stdbool.h>

// Struct para representar a posição do cavalo
typedef struct {
    char letra;
    int linha;
} PosicaoCavalo;

// Struct para representar os movimentos do cavalo
typedef struct {
    int dx; // Deslocamento na horizontal
    int dy; // Deslocamento na vertical
} MovimentoCavalo;

void letra2numero(char letra, int *coluna) {
    switch (letra) {
        case 'a': *coluna = 1; break;
        case 'b': *coluna = 2; break;
        case 'c': *coluna = 3; break;
        case 'd': *coluna = 4; break;
        case 'e': *coluna = 5; break;
        case 'f': *coluna = 6; break;
        case 'g': *coluna = 7; break;
        case 'h': *coluna = 8; break;
        default: *coluna = 0; break;
    }
}

bool ehPar(int linha, int coluna) {
    return (linha % 2 == 0) || (coluna % 2 == 0);
}

bool ehImpar(int linha, int coluna) {
    return (linha % 2 == 1) || (coluna % 2 == 1);
}

void verificaCorCasa(int linha, int coluna) {
    if (ehPar(linha, coluna)) {
        printf("A casa eh de cor preta.\n");
    } else {
        printf("A casa eh de cor branca.\n");
    }
}

int main() {
    PosicaoCavalo posicao;
    int qtdMovimentos;

    printf("Digite a posicao inicial do cavalo: [letra x coluna] ");
    scanf(" %c%d", &posicao.letra, &posicao.linha);

    int numeroColuna;
    letra2numero(posicao.letra, &numeroColuna);

    if (ehPar(posicao.linha, numeroColuna)) {
        printf("A posicao inicial eh par.\n");
    } else if (ehImpar(posicao.linha, numeroColuna)) {
        printf("A posicao inicial eh impar.\n");
    }

    printf("Digite a quantidade de movimentos: ");
    scanf(" %d", &qtdMovimentos);

    verificaCorCasa(posicao.linha, numeroColuna);

    // Exemplo de uso da struct MovimentoCavalo
    MovimentoCavalo movimento = {2, 1}; // Exemplo de um movimento de cavalo
    printf("Movimento do cavalo: dx=%d, dy=%d\n", movimento.dx, movimento.dy);

    return 0;
}
