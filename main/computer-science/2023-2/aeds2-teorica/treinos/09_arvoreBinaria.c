/**
 * Árvore Binária de Busca
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct _no {
    struct _no *esquerda;
    //int chave;
    int valor;
    struct _no *direita;
} no;

no *busca (no *raiz, int procurado) {
    if ( (raiz == NULL) || (raiz->valor == procurado) ) {
        return raiz;
    } if ( (raiz->valor) > procurado) {
        return busca(raiz->esquerda, procurado);
    } else {
        return busca(raiz->direita, procurado);
    }
}

no *planta(no *raiz, int semente) {
    // Crie um novo nó
    no *folhaNova = malloc(sizeof(no));

    folhaNova->esquerda = NULL;
    folhaNova->valor = semente;
    folhaNova->direita = NULL;

    // Verifique se a raiz é nula
    if (raiz == NULL) {
        return folhaNova;
    }

    // Insira o novo nó na posição apropriada na árvore
    if (semente < raiz->valor) {
        raiz->esquerda = planta(raiz->esquerda, semente);
    } else {
        raiz->direita = planta(raiz->direita, semente);
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

int main () {
    no *raiz = NULL;
    int opcao;
    //int valor;

    do {
        menu();
        printf("O que quer fazer? ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                // Some com a árvore
                desmatamento(raiz);
                return 0;
            case 1:
                // planta um valor
                // Ordem de inserção sugerida: 8 3 1 6 4 7 10 14 13
                //printf("\tQual valor que inserir? ");
                //scanf(" %d", &valor);
                raiz = planta(raiz, 8);
                raiz = planta(raiz, 3);
                raiz = planta(raiz, 1);
                raiz = planta(raiz, 6);
                raiz = planta(raiz, 4);
                raiz = planta(raiz, 7);
                raiz = planta(raiz, 10);
                raiz = planta(raiz, 14);
                raiz = planta(raiz, 13);
                printf("\nElementos inseridos com sucesso!\n");
                break;
            case 2:
                // Remove um valor
                //printf("\tQual valor quer remover? ");
                //scanf(" %d", &valor);
                //raiz = poda(raiz, valor);
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
