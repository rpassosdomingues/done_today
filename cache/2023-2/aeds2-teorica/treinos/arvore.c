#include<stdio.h>
#include<stdlib.h>

typedef struct arvore_{
    struct arvore_ *esquerda;
    int conteudo;
    struct arvore_ *direita;
} arvore;

arvore *planta (arvore *raiz, int semente) {
    if (raiz == NULL) {
        return semente;
    }

    arvore *folhaNova = malloc(sizeof(folhaNova));

    folhaNova->esquerda = NULL;
    folhaNova->conteudo = semente;
    folhaNova->direita = NULL;

    if ((raiz->conteudo) > semente) {
        raiz->esquerda = planta(raiz->esquerda, semente);
    } else {
        raiz->direita = planta(raiz->direita, semente);
    }
    return raiz;
}

arvore *busca (arvore *raiz, int procurado) {
    if ( (raiz == NULL) || (raiz->conteudo == procurado) ) {
        return raiz;
    }
    if ((raiz->conteudo) > procurado) {
        return busca(raiz->esquerda, procurado);
    } else {
        return busca(raiz->direita, procurado);
    }
}

/*
void buscaPai (arvore *raiz, int procurado) {
    //to-do
}

void podaRaiz (folhaSeca) {
    //to-do
}

arvore *poda (arvore *raiz, arvore galho) {
    arvore *folhaSeca = busca(raiz, galho);
    if (folhaSeca) {
        arvore *pai = buscaPai(raiz, folhaSeca);
        if (pai) {
            if ((pai->direita) == folhaSeca) {
                pai->direita = podaRaiz(folhaSeca);
            } else {
                pai->esquerda = podaRaiz(folhaSeca);
            }
        } else {
            raiz = podaRaiz(folhaSeca);
        }
    }
    return raiz;
}
*/

void imprimeEmOrdem (arvore *raiz) {
    if (raiz != NULL) {
        imprimeEmOrdem(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimeEmOrdem(raiz->direita);
    }
}

int main () {
    arvore *raiz = NULL;

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

    // Imprimir em Ordem
    printf("\nEm Ordem: ");
    imprimeEmOrdem(raiz);
    printf("\n");

    return 0;
}