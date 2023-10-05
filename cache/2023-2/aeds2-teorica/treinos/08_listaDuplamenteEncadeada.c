#include <stdio.h>
#include <stdlib.h>

// Define uma struct para um nó na lista encadeada
typedef struct no {
    int chave;
    int valor;
    struct no *anterior;
    struct no *proximo;
} No;

// Função para criar um novo nó e retornar um ponteiro para ele
No* cria() {
    No* novoNo = malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n...Algo deu errado...\n");
    } else {
        printf("\nSucesso!\n");
        novoNo->proximo = NULL;
    }
    return novoNo;
}

// Função para liberar a memória alocada dinamicamente
void destroi(No* lista) {
    while (lista != NULL) {
        No* temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

// Função para inserir um novo nó na lista
void poe(No **lista, int inserido) {
    No* novoNo = cria();
    if (novoNo != NULL) {
        novoNo->valor = inserido;
        novoNo->proximo = *lista;
        *lista = novoNo;
    }
}

// Função para remover um nó na lista
void tira(No** lista) {
    if (*lista != NULL) {
        No* temp = *lista;
        *lista = (*lista)->proximo;
        free(temp);
    }
}

// Função para buscar por um valor na lista
No* busca(No* lista, int buscado) {
    No* posicao = lista;
    while (posicao != NULL) {
        if (posicao->valor == buscado) {
            return posicao;
        }
        posicao = posicao->proximo;
    }
    return NULL;
}

// Função para imprimir os valores armazenados nos nós da lista em ordem de inserção
void imprime(No* lista) {
    printf("\n");
    while (lista != NULL) {
        printf("%d ", lista->valor);
        lista = lista->proximo;
    }
    printf("\n");
}

// Função para imprimir o menu
void menu() {
    printf("\n===========================");
    printf("\n\t Menu");
    printf("\n---------------------------");
    printf("\n0. Sair");
    printf("\n1. Inserir");
    printf("\n2. Remover");
    printf("\n3. Buscar");
    printf("\n4. Imprimir");
    printf("\n===========================");
    printf("\nO que quer fazer? ");
}

int main() {
    No* lista = NULL;
    int opcao, valor, procurado, posicao;
    No* valorProcurado;

    while (1) {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                // Libera memória alocada dinamicamente
                destroi(lista);
                return 0;
            case 1:
                printf("\n\tDigite um valor a ser inserido: ");
                scanf(" %d", &valor);
                poe(&lista, valor);
                break;
            case 2:
                tira(&lista);
                break;
            case 3:
                printf("\n\tDigite um valor a ser procurado: ");
                scanf("%d", &procurado);
                valorProcurado = busca(lista, procurado);
                if (valorProcurado == NULL) {
                    printf("\nO valor nao foi encontrado.\n");
                } else {
                    printf("\nO valor foi encontrado na posicao %d da lista.\n", posicao);
                }
                break;
            case 4:
                imprime(lista);
                break;
            default:
                printf("\nEntrada invalida!");
        }
    }

    return 0;
}
