#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "passeio.h"

// Struct para representar o cavalo
struct Cavalo {
    int x, y;           // Posição atual do cavalo
    int movimentos[8][2];  // Movimentos possíveis do cavalo
};

// Struct para representar um nodo na lista
struct Nodo {
    int x, y;
    struct Nodo* proximo;
    struct Nodo* anterior;
};

// Função para criar um novo nodo
struct Nodo* criarNodo(int x, int y) {
    struct Nodo* novoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    novoNodo->x = x;
    novoNodo->y = y;
    novoNodo->proximo = NULL;
    novoNodo->anterior = NULL;
    return novoNodo;
}

// Função para adicionar um nodo ao fim da lista
void adicionarAoFim(struct Nodo* inicio, int x, int y) {
    struct Nodo* novoNodo = criarNodo(x, y);
    struct Nodo* temp = inicio;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novoNodo;
    novoNodo->anterior = temp;
}

// Função para verificar se um movimento é válido dentro do tabuleiro
int movimentoValido(int x, int y, int M, int N) {
    return (x >= 0 && x < M && y >= 0 && y < N);
}

// Função para contar percursos fechados do cavalo no tabuleiro
int contarPercursosFechados(struct Cavalo cavalo, int M, int N, bool **tabuleiro) {
    int** visitados = (int**)malloc(M * sizeof(int*));
    for (int i = 0; i < M; i++) {
        visitados[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            visitados[i][j] = 0;
        }
    }

    struct Nodo* lista = criarNodo(cavalo.x, cavalo.y);
    int contadorFechados = 0;

    while (lista != NULL) {
        int x = lista->x;
        int y = lista->y;
        visitados[x][y] = 1;
        struct Nodo* proximo = lista->proximo;

        for (int i = 0; i < 8; i++) {
            int novoX = x + cavalo.movimentos[i][0];
            int novoY = y + cavalo.movimentos[i][1];
            if (movimentoValido(novoX, novoY, M, N) && !visitados[novoX][novoY] && !tabuleiro[novoX][novoY]) {
                if (proximo == NULL && visitadosTodas(visitados, M, N) && novoX == cavalo.x && novoY == cavalo.y) {
                    contadorFechados++;
                } else {
                    adicionarAoFim(proximo, novoX, novoY);
                }
                visitados[novoX][novoY] = 0;
            }
        }
        free(lista);
        lista = proximo;
    }

    // Liberar memória alocada para visitados
    for (int i = 0; i < M; i++) {
        free(visitados[i]);
    }
    free(visitados);

    return contadorFechados;
}

// Função para verificar se todas as casas do tabuleiro foram visitadas
int visitadosTodas(int** visitados, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!visitados[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Função principal para calcular percursos abertos e fechados
void computa_passeios(bool **tabuleiro) {
    int fechados = 0;
    int abertos = 0;
    int M = 2;  // Defina as dimensões do tabuleiro conforme necessário
    int N = 2;

    struct Cavalo cavalo = {0, 0, {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}}};
    fechados = contarPercursosFechados(cavalo, M, N, tabuleiro);

    printf("%d\n%d\n", fechados, abertos);
    return;
}

// Função principal (não deve ser modificada)
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

// Função para ler instância (não deve ser modificada)
bool **ler_instancia(int instancia_num) {
    int n, m;
    int i;
    
    // Montando o caminho para a instancia
    char *arquivo_instancia = "./instancias/";
    asprintf(&arquivo_instancia, "%s%d", arquivo_instancia, instancia_num);
    
    // Ponteiro para a instância
    FILE* file;
 
    // Abrindo a instância em modo leitura
    file = fopen(arquivo_instancia, "r");
 
    if (NULL == file) {
        printf("Arquivo de instância não encontrado. Verifique se sua estrutura de diretórios está EXATAMENTE igual ao do Github\n");
        exit(0);
    }

    // Lendo o arquivo da instância
    fscanf (file, "%d", &n);
    fscanf (file, "%d", &m);

    // Alocando o tabuleiro dinamicamente
    // Usando calloc ao invés de malloc para inicializar todo o tabuleiro com zeros
    bool** tabuleiro = (bool**)calloc(n, sizeof(bool*));
    for (i = 0; i < n; i++) {
        tabuleiro[i] = (bool*)calloc(m, sizeof(bool));
    }

    return tabuleiro;
}
