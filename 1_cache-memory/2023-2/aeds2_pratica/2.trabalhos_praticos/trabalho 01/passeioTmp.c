#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

// Struct para representar um nó da lista de posições
typedef struct No {
    PosicaoCavalo posicao;
    struct No* proximo;
    struct No* anterior;
} NoPosicao;

// Função para inicializar um nó da lista de posições
NoPosicao* inicializarNo(PosicaoCavalo posicao) {
    NoPosicao* no = (NoPosicao*)malloc(sizeof(NoPosicao));
    no->posicao = posicao;
    no->proximo = NULL;
    no->anterior = NULL;
    return no;
}

// Função para adicionar um nó no final da lista de posições
void adicionarNo(NoPosicao** cabeca, PosicaoCavalo posicao) {
    NoPosicao* novoNo = inicializarNo(posicao);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        NoPosicao* atual = *cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
        novoNo->anterior = atual;
    }
}

// Função para remover e liberar a memória de um nó da lista de posições
void removerNo(NoPosicao** cabeca, NoPosicao* no) {
    if (*cabeca == NULL || no == NULL) {
        return;
    }
    
    if (*cabeca == no) {
        *cabeca = no->proximo;
    }

    if (no->anterior != NULL) {
        no->anterior->proximo = no->proximo;
    }

    if (no->proximo != NULL) {
        no->proximo->anterior = no->anterior;
    }

    free(no);
}

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

void computa_passeios(bool **tabuleiro) {
    int fechados = 0;
    int abertos = 0;
    int n = 8;
    int m = 8;

    // Iniciar a busca em profundidade a partir da posição inicial (0, 0)
    NoPosicao* listaDePosicoes = NULL;
    adicionarNo(&listaDePosicoes, (PosicaoCavalo) {0, 0});

    while (listaDePosicoes != NULL) {
        PosicaoCavalo posicaoAtual = listaDePosicoes->posicao;
        int x = posicaoAtual.letra - 'a';
        int y = posicaoAtual.linha - 1;
        int movimentos = x * m + y + 1;

        if (movimentos == n * m) {
            if (x == 0 && y == 0) {
                if (movimentos % 2 == 0) {
                    fechados++;
                } else {
                    abertos++;
                }
            }
        } else {
            // Movimentos do cavalo
            int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
            int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

            for (int i = 0; i < 8; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                if (newX >= 0 && newX < n && newY >= 0 && newY < m && !tabuleiro[newX][newY]) {
                    tabuleiro[newX][newY] = true;
                    adicionarNo(&listaDePosicoes, (PosicaoCavalo) {'a' + newX, newY + 1});
                }
            }
        }

        // Remover a posição atual da lista
        NoPosicao* proximo = listaDePosicoes->proximo;
        removerNo(&listaDePosicoes, listaDePosicoes);
        listaDePosicoes = proximo;
    }

    // Imprimir resultados
    printf("Passeios Fechados: %d\nPasseios Abertos: %d\n", fechados, abertos);
}

int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 20) {
        printf("Para executar o código, digite ./passeio x\nonde x é um número entre 1 e 20 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    // Tabuleiro do jogo
    bool **tabuleiro = ler_instancia(instancia_num);

    computa_passeios(tabuleiro);

    return (1);
}
