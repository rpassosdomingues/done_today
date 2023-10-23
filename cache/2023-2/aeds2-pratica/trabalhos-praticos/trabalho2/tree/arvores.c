#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Estrutura para nós de árvores.
 */
typedef struct arvore {
    struct arvore *esquerda;
    int conteudo;
    struct arvore *direita;
    int altura; // Para árvore AVL
} arvore;

/**
 * Função para criar um novo nó.
 */
arvore *criaNo(int conteudo) {
    arvore *novo = (arvore *)malloc(sizeof(arvore));
    if (novo == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    novo->conteudo = conteudo;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1; // Para árvore AVL
    return novo;
}

/**
 * Função para calcular a altura de um nó.
 */
int altura(arvore *raiz) {
    if (raiz == NULL)
        return 0;
    return raiz->altura;
}

/**
 * Função para obter o máximo de dois inteiros.
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Função para realizar uma rotação simples à direita.
 */
arvore *rotacaoDireita(arvore *raiz) {
    arvore *novaRaiz = raiz->esquerda;
    arvore *subArvore = novaRaiz->direita;

    novaRaiz->direita = raiz;
    raiz->esquerda = subArvore;

    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    novaRaiz->altura = max(altura(novaRaiz->esquerda), altura(novaRaiz->direita)) + 1;

    return novaRaiz;
}

/**
 * Função para realizar uma rotação simples à esquerda.
 */
arvore *rotacaoEsquerda(arvore *raiz) {
    arvore *novaRaiz = raiz->direita;
    arvore *subArvore = novaRaiz->esquerda;

    novaRaiz->esquerda = raiz;
    raiz->direita = subArvore;

    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    novaRaiz->altura = max(altura(novaRaiz->esquerda), altura(novaRaiz->direita)) + 1;

    return novaRaiz;
}

/**
 * Função para verificar o fator de balanceamento de um nó.
 */
int fatorBalanceamento(arvore *raiz) {
    if (raiz == NULL)
        return 0;
    return altura(raiz->esquerda) - altura(raiz->direita);
}

/**
 * Função para inserir um elemento em uma árvore AVL.
 */
arvore *insereAVL(arvore *raiz, int conteudo) {
    if (raiz == NULL)
        return criaNo(conteudo);

    if (conteudo < raiz->conteudo)
        raiz->esquerda = insereAVL(raiz->esquerda, conteudo);
    else if (conteudo > raiz->conteudo)
        raiz->direita = insereAVL(raiz->direita, conteudo);
    else
        return raiz; // Elemento já existe, não insere novamente

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balance = fatorBalanceamento(raiz);

    // Verifica o balanceamento e realiza rotações, se necessário
    if (balance > 1) {
        if (conteudo < raiz->esquerda->conteudo) {
            // Rotação à direita (caso esquerda-esquerda)
            return rotacaoDireita(raiz);
        } else {
            // Rotação à esquerda-direita
            raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
            return rotacaoDireita(raiz);
        }
    }
    if (balance < -1) {
        if (conteudo > raiz->direita->conteudo) {
            // Rotação à esquerda (caso direita-direita)
            return rotacaoEsquerda(raiz);
        } else {
            // Rotação à direita-esquerda
            raiz->direita = rotacaoDireita(raiz->direita);
            return rotacaoEsquerda(raiz);
        }
    }

    return raiz;
}

/**
 * Função para inserir um elemento em uma árvore binária.
 */
arvore *insereBinaria(arvore *raiz, int conteudo) {
    if (raiz == NULL)
        return criaNo(conteudo);

    if (conteudo < raiz->conteudo)
        raiz->esquerda = insereBinaria(raiz->esquerda, conteudo);
    else if (conteudo > raiz->conteudo)
        raiz->direita = insereBinaria(raiz->direita, conteudo);

    return raiz;
}

/**
 * Função para realizar uma busca em uma árvore.
 */
arvore *busca(arvore *raiz, int procurado) {
    if (raiz == NULL || raiz->conteudo == procurado)
        return raiz;

    if (procurado < raiz->conteudo)
        return busca(raiz->esquerda, procurado);

    return busca(raiz->direita, procurado);
}

/**
 * Função para encontrar o nó de valor mínimo em uma árvore.
 */
arvore *minimoValor(arvore *raiz) {
    arvore *atual = raiz;

    while (atual->esquerda != NULL)
        atual = atual->esquerda;

    return atual;
}

/**
 * Função para remover um elemento de uma árvore.
 */
arvore *removeNo(arvore *raiz, int valor) {
    if (raiz == NULL)
        return raiz;

    if (valor < raiz->conteudo)
        raiz->esquerda = removeNo(raiz->esquerda, valor);
    else if (valor > raiz->conteudo)
        raiz->direita = removeNo(raiz->direita, valor);
    else {
        // Encontrou o nó a ser removido
        if (raiz->esquerda == NULL) {
            arvore *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            arvore *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        arvore *sucessor = minimoValor(raiz->direita);

        raiz->conteudo = sucessor->conteudo;
        raiz->direita = removeNo(raiz->direita, sucessor->conteudo);
    }

    return raiz;
}

/**
 * Função para calcular o tempo decorrido.
 */
double calculaTempo(clock_t inicio, clock_t fim) {
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

/**
 * Função para liberar a memória de uma árvore.
 */
void liberaMemoria(arvore *raiz) {
    if (raiz == NULL)
        return;

    liberaMemoria(raiz->esquerda);
    liberaMemoria(raiz->direita);
    free(raiz);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <número de elementos>\n", argv[0]);
        return 1;
    }

    int numElementos = atoi(argv[1]);

    // Árvore binária
    arvore *raizBinaria = NULL;
    clock_t inicio = clock();
    for (int i = 1; i <= numElementos; i++) {
        raizBinaria = insereBinaria(raizBinaria, i);
    }
    clock_t fim = clock();
    double tempoBinaria = calculaTempo(inicio, fim);

    // Árvore AVL
    arvore *raizAVL = NULL;
    inicio = clock();
    for (int i = 1; i <= numElementos; i++) {
        raizAVL = insereAVL(raizAVL, i);
    }
    fim = clock();
    double tempoAVL = calculaTempo(inicio, fim);

    printf("Tempo para inserir %d elementos em árvore binária: %f segundos\n", numElementos, tempoBinaria);
    printf("Tempo para inserir %d elementos em árvore AVL: %f segundos\n", numElementos, tempoAVL);

    // Realizar busca e remoção de um elemento nas árvores (exemplo)
    int elementoBusca = numElementos / 2;
    inicio = clock();
    arvore *encontradoBinaria = busca(raizBinaria, elementoBusca);
    fim = clock();
    double tempoBuscaBinaria = calculaTempo(inicio, fim);

    inicio = clock();
    arvore *encontradoAVL = busca(raizAVL, elementoBusca);
    fim = clock();
    double tempoBuscaAVL = calculaTempo(inicio, fim);

    if (encontradoBinaria)
        raizBinaria = removeNo(raizBinaria, elementoBusca);

    if (encontradoAVL)
        raizAVL = removeNo(raizAVL, elementoBusca);

    printf("Tempo para busca em árvore binária: %f segundos\n", tempoBuscaBinaria);
    printf("Tempo para busca em árvore AVL: %f segundos\n", tempoBuscaAVL);

    // Liberar memória
    liberaMemoria(raizBinaria);
    liberaMemoria(raizAVL);

    return 0;
}
