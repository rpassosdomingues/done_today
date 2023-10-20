/**
 * Árvore Binária de Busca
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct _no {
    struct _no *esquerda;
    int chave;
    int valor;
    struct _no *direita;
} no;

no *busca (no *raiz, int k) {
    if ( (raiz == NULL) || (raiz->valor == k) ) {
        return raiz;
    } if ( (raiz->valor) > k) {
        return busca(raiz->esquerda, k);
    } else {
        return busca(raiz->direita, k);
    }
}

no *insere (no *raiz, no *novoNo) {
    if (raiz == NULL) {
        return novoNo;
    } if ( (raiz->valor) > (novoNo->valor) ) {
        raiz->esquerda = insere(raiz->esquerda, novoNo);
    } else {
        raiz->direita = insere(raiz->direita, novoNo);
    }
    return raiz;
}

no *poda (no *raiz, int galhoSeco) {
    // verifica se o nó existe
    no *n = busca(raiz, galhoSeco);
    if (n) {
        // descobre quem é o nó pai
        no *pai = buscaPai(raiz, n);
        // caso tenha nó pai
        if (pai) {
            // O nó a ser removido é filho à direita
            if ( (pai->direita) == n ) {
                pai->direita = podaRaiz(n);
              // O nó a ser removido é filho à esquerda
            } else {
                pai->esquerda = podaRaiz(n);
            }
          // Não possui pai, logo é o próprio nó raiz
        } else {
            raiz = podaRaiz(n);
        }
    }
    return raiz;
}

void imprimeEmOrdem(no *raiz) {
    if (raiz != NULL) {
        imprimeEmOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimeEmOrdem(raiz->direita);
    }
}

void imprimePreOrdem(no *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        imprimePreOrdem(raiz->esquerda);
        imprimePreOrdem(raiz->direita);
    }
}

void imprimePosOrdem(no *raiz) {
    if (raiz != NULL) {
        imprimePosOrdem(raiz->esquerda);
        imprimePosOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

void desmatamento(no *raiz) {
    if (raiz != NULL) {
        desmatamento(raiz->esquerda);
        desmatamento(raiz->direita);
        free(raiz);
    }
}

void menu () {
    printf("================================\n");
    printf("Menu:\n");
    printf("--------------------------------\n");
    printf("0 - Sair\n");
    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Imprimir Em Ordem\n");
    printf("4 - Imprimir Pre Ordem\n");
    printf("5 - Imprimir Pos Ordem\n");
    printf("================================\n");
}

void main () {
    no *raiz = NULL;
    int opcao, valor;

    do {
        menu();
        printf("O que vai fazer? ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                // Some com a árvore
                desmatamento(raiz);
                break;
            case 1:
                // Insere um valor
                // Ordem de inserção sugerida: 8 3 1 6 4 7 10 14 13
                printf("\tQual valor que inserir? ");
                scanf(" %d", &valor);
                raiz = insere(raiz, valor);
                break;
            case 2:
                // Remove um valor
                printf("\tQual valor quer remover? ");
                scanf(" %d", &valor);
                raiz = poda(raiz, valor);
                break;
            case 3:
                // Imprimir em Ordem
                printf("\nEm Ordem: ");
                imprimeEmOrdem(raiz);
                printf("\n");
                break;
            case 4:
                // Imprimir Pre Ordem
                printf("\nPre Ordem: ");
                imprimePreOrdem(raiz);
                printf("\n");
                break;
            case 5:
                // Imprimir Pos Ordem
                printf("\nPos Ordem: ");
                imprimePosOrdem(raiz);
                printf("\n");
                break;
            default:
                printf("Opcao Invalida.\n");
        }
    } while (opcao != 0);
}
