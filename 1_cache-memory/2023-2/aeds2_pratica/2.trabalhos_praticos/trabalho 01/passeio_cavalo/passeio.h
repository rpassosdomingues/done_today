#ifndef PASSEIO_H
#define PASSEIO_H

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
NoPosicao* inicializarNo(PosicaoCavalo posicao);

// Função para adicionar um nó no final da lista de posições
void adicionarNo(NoPosicao** cabeca, PosicaoCavalo posicao);

// Função para remover e liberar a memória de um nó da lista de posições
void removerNo(NoPosicao** cabeca, NoPosicao* no);

void letra2numero(char letra, int *coluna);

bool ehPar(int linha, int coluna);

bool ehImpar(int linha, int coluna);

void verificaCorCasa(int linha, int coluna);

void computa_passeios(bool **tabuleiro);

bool **ler_instancia(int instancia_num);

#endif /* PASSEIO_H */
