#include <stdio.h>
#include <stdlib.h>

// Estrutura que representa um nó da fila
typedef struct No {
    int chave; // chave do nó
    int valor; // valor do nó
    struct No *proximo; // ponteiro para o próximo nó
} No;

// Função que cria um novo nó com uma chave e um valor
No *criarNo(int chave, int valor) {
    No *no = (No*)malloc(sizeof(No)); // aloca memória para o nó
    if (no != NULL) { // se a alocação foi bem sucedida
        no->chave = chave; // atribui a chave ao campo chave do nó
        no->valor = valor; // atribui o valor ao campo valor do nó
        no->proximo = NULL; // atribui NULL ao campo proximo do nó
    }
    return no; // retorna o ponteiro para o nó
}

// Função que insere um novo nó no fundo da fila
void insere(No **fila, int chave, int valor) {
    No *novo = criarNo(chave, valor); // cria um novo nó com a chave e o valor
    if (*fila == NULL) { // se a fila estiver vazia
        *fila = novo; // o novo nó se torna o primeiro elemento da fila
    } else { // senão
        No *aux = *fila; // cria um ponteiro auxiliar para percorrer a fila
        while (aux->proximo != NULL) { // enquanto não chegar no último nó da fila
            aux = aux->proximo; // avança para o próximo nó
        }
        aux->proximo = novo; // insere o novo nó após o último nó da fila
    }
}

// Função que remove um nó da frente da fila
void remover(No **fila) {
    if (*fila != NULL) {
        No *temp = *fila;
        *fila = (*fila)->proximo;
        free(temp);
    }
}

// Função que imprime as chaves e os valores dos nós da fila
void imprime(No *fila) {
    No *aux = fila; // cria um ponteiro auxiliar para percorrer a fila
    while (aux != NULL) { // enquanto não chegar no final da fila
        printf("Chave: %d, Valor: %d\n", aux->chave, aux->valor); // imprime a chave e o valor do nó atual
        aux = aux->proximo; // avança para o próximo nó
    }
}

// Função que libera a memória alocada para os nós da fila
void liberar(No *fila) {
    No *aux = fila; // cria um ponteiro auxiliar para percorrer a fila
    while (aux != NULL) { // enquanto não chegar no final da fila
        No *temp = aux; // guarda o ponteiro para o nó atual em uma variável temporária
        aux = aux->proximo; // avança para o próximo nó
        free(temp); // libera a memória do nó atual
    }
}

int main() {
    No *fila = NULL; // cria uma variável do tipo No e inicializa com NULL

    insere(&fila, 1, 10); // insere um novo nó com chave 1 e valor 10 na fila
    insere(&fila, 2, 20); // insere um novo nó com chave 2 e valor 20 na fila
    insere(&fila, 3, 30); // insere um novo nó com chave 3 e valor 30 na fila

    imprime(fila); // imprime as chaves e os valores dos nós da fila

    remover(&fila); // remove o primeiro elemento da fila

    imprime(fila); // imprime as chaves e os valores dos nós da fila

    liberar(fila); // libera a memória alocada para os nós da fila

    return 0;
}
