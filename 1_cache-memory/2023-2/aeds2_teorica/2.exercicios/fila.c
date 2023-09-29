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
    No *no = malloc(sizeof(No)); // aloca memória para o nó
    if (no != NULL) { // se a alocação foi bem sucedida
        no->chave = chave; // atribui a chave ao campo chave do nó
        no->valor = valor; // atribui o valor ao campo valor do nó
        no->proximo = NULL; // atribui NULL ao campo proximo do nó
    }
    return no; // retorna o ponteiro para o nó
}

// Função que insere um novo nó no final da fila
void insere(No **fila, int chave, int valor) {
    No *novo = criarNo(chave, valor); // cria um novo nó com a chave e o valor
    if (novo != NULL && *fila == NULL) { // se a criação foi bem sucedida e se a fila estiver vazia
        *fila = novo; // o novo nó se torna o primeiro elemento da fila
    } else { // senão
        No *aux = *fila; // cria um ponteiro auxiliar para percorrer a fila
        while (aux->proximo != NULL) { // enquanto não chegar no último nó da fila
            aux = aux->proximo; // avança para o próximo nó
        }
        aux->proximo = novo; // insere o novo nó após o último nó da fila
    }
    //printf("Erro na alocação de memória!\n"); // imprime uma mensagem de erro
}

// Função que imprime as chaves e os valores dos nós da fila
void imprime (No *fila) {
    No *aux = fila; // cria um ponteiro auxiliar para percorrer a fila
    while (aux != NULL) { // enquanto não chegar no final da fila
        printf("Valor: %d, Chave: %d\n", aux->chave, aux->valor); // imprime a chave e o valor do nó atual
        aux = aux->proximo; // avança para o próximo nó
    }
}

// Função que libera a memória alocada para os nós da fila
void liberar (No *fila) {
    No *aux = fila; // cria um ponteiro auxiliar para percorrer a fila
    while (aux != NULL) { // enquanto não chegar no final da fila
        No *temp = aux; // guarda o ponteiro para o nó atual em uma variável temporária
        aux = aux->proximo; // avança para o próximo nó
        free(temp); // libera a memória do nó atual
    }
}

int main() {
    No *fila = NULL; // cria uma variável do tipo No e inicializa com NULL

    insere(&fila, 1, 10); // insere um novo nó com valor 1 e chave 10 na fila
    insere(&fila, 2, 20); // insere um novo nó com valor 2 e chave 20 na fila
    insere(&fila, 3, 30); // insere um novo nó com valor 3 e chave 30 na fila
    insere(&fila, 4, 40); // insere um novo nó com valor 4 e chave 40 na fila
    insere(&fila, 5, 50); // insere um novo nó com valor 5 e chave 50 na fila

    imprime(fila); // imprime os valores e as chaves dos nós da fila

    liberar(fila); // libera a memória alocada para os nós da fila

    return 0;
}
