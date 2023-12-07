/***
 * Author: Rafael Passos Domingues
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * Estrutura para nós sub-arvores.
*/
typedef struct arvore {
    struct arvore *esquerda;
    int conteudo;
    struct arvore *direita;
} arvore;

/**
 * Função para inserir sub-árvores.
*/
arvore *planta(arvore *raiz, int semente) {
    if (raiz == NULL) {
        arvore *folhaNova = malloc(sizeof(arvore));
        folhaNova->esquerda = NULL;
        folhaNova->conteudo = semente;
        folhaNova->direita = NULL;
        return folhaNova;
    }

    if (semente < raiz->conteudo) {
        raiz->esquerda = planta(raiz->esquerda, semente);
    } else {
        raiz->direita = planta(raiz->direita, semente);
    }
    return raiz;
}

/**
 * Função para encontrar um determinado valor em alguma sub-árvore.
*/
arvore *busca(arvore *raiz, int procurado) {
    if ((raiz == NULL) || (raiz->conteudo == procurado)) {
        return raiz;
    }
    if ((raiz->conteudo) > procurado) {
        return busca(raiz->esquerda, procurado);
    } else {
        return busca(raiz->direita, procurado);
    }
}

/**
 * Função para encontrar o pai de uma sub-árvore a ser removida.
*/
arvore *buscaPai(arvore *raiz, arvore *galho, arvore *pai) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz == galho) {
        return pai;
    }

    if (galho->conteudo < raiz->conteudo) {
        return buscaPai(raiz->esquerda, galho, raiz);
    } else {
        return buscaPai(raiz->direita, galho, raiz);
    }
}

/**
 * Função para remover uma sub-árvore em 3 diferentes cenários.
*/
arvore *poda(arvore *raiz, int valor) {
    arvore *galho = busca(raiz, valor);

    if (galho == NULL) {
        printf("Elemento não encontrado na árvore.\n");
        return raiz;
    }

    arvore *pai = buscaPai(raiz, galho, NULL);

    if (galho->esquerda == NULL && galho->direita == NULL) {
        // Caso 1: O nó é uma folha (não tem filhos).
        if (pai == NULL) {
            free(raiz);
            return NULL; // Raiz é removida
        } else {
            if (pai->esquerda == galho) {
                free(pai->esquerda);
                pai->esquerda = NULL;
            } else {
                free(pai->direita);
                pai->direita = NULL;
            }
        }
    } else if (galho->esquerda == NULL || galho->direita == NULL) {
        // Caso 2: O nó tem um filho.
        arvore *filho = (galho->esquerda != NULL) ? galho->esquerda : galho->direita;
        if (pai == NULL) {
            free(raiz);
            return filho; // Raiz é removida
        } else {
            if (pai->esquerda == galho) {
                free(pai->esquerda);
                pai->esquerda = filho;
            } else {
                free(pai->direita);
                pai->direita = filho;
            }
        }
    } else {
        // Caso 3: O nó tem dois filhos.
        // Encontra o nó sucessor (o menor nó na subárvore direita) e substitui pelo nó a ser removido.
        arvore *sucessor = galho->direita;
        while (sucessor->esquerda != NULL) {
            sucessor = sucessor->esquerda;
        }

        int temp = sucessor->conteudo;
        raiz = poda(raiz, temp); // Remove o nó sucessor
        galho->conteudo = temp; // Substitui o valor do nó pelo valor do sucessor
    }

    return raiz;
}

void imprimeEmOrdem(arvore *raiz) {
    if (raiz != NULL) {
        imprimeEmOrdem(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimeEmOrdem(raiz->direita);
    }
}

void imprimePreOrdem(arvore *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->conteudo);
        imprimePreOrdem(raiz->esquerda);
        imprimePreOrdem(raiz->direita);
    }
}

void imprimePosOrdem(arvore *raiz) {
    if (raiz != NULL) {
        imprimePosOrdem(raiz->esquerda);
        imprimePosOrdem(raiz->direita);
        printf("%d ", raiz->conteudo);
    }
}

/**
 * Função para liberar a memória alocada dinamicamente para a árvore.
*/
void desmatamento(arvore *raiz) {
    if (raiz == NULL) {
        return;
    }
    desmatamento(raiz->esquerda);
    desmatamento(raiz->direita);
    free(raiz);
}

void menu() {
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

int main() {
    arvore *raiz = NULL;
    int opcao;
    int valor;

    do {
        menu();
        printf("O que deseja fazer? ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                // Liberar a árvore
                desmatamento(raiz);
                raiz = NULL;
                printf("Arvore desmatada.\n");
                return 0;
            case 1:
                // Planta um valor na árvore
                printf("\tQual valor quer inserir? ");
                scanf(" %d", &valor);
                raiz = planta(raiz, valor);
                printf("\nElemento inserido com sucesso!\n");
                break;
            case 2:
                // Remove um valor
                printf("\tQual valor quer remover? ");
                scanf(" %d", &valor);
                raiz = poda(raiz, valor);
                printf("\nElemento removido com sucesso!\n");
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
