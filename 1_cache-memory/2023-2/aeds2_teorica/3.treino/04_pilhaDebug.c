#include <stdio.h>

#define MAX_ALTURA 3 // Tamanho máximo da pilha

// Definindo uma estrutura para representar a pilha
typedef struct {
    int altura;
    int topo;
    int livros[MAX_ALTURA]; // Vetor de livros
} Pilha; // Apelido da struct

void inicializaPilha(Pilha *pilha, int altura) {
    pilha->altura = altura; // Faz a estrutura receber a altura
    pilha->topo = -1; // Indica pilha vazia
}

int insere(Pilha *pilha, int add) { // Passa a estrutura "pilha" com o livro a ser empilhado
    if (pilha->topo == pilha->altura - 1) { // Verifica se a pilha está cheia
        printf("A pilha está cheia. Não foi possível empilhar mais um livro.\n");
        return -1;
    } else { // Caso não esteja cheia...
        pilha->topo++; // Faz o topo subir um degrau
        pilha->livros[pilha->topo] = add; // Empilha um livro no topo
        printf("Livro %d inserido na pilha.\n", add);
        return pilha->topo;
    }
}

int main() {
    Pilha pilha;
    
    printf("\nDefina a altura máxima da pilha: ");
    scanf("%d", &pilha.altura);

    inicializaPilha(&pilha, pilha.altura);

    int numLivros;
    printf("Quantos livros deseja inserir na pilha? ");
    scanf("%d", &numLivros);

    for (int i = 0; i < numLivros; i++) {
        int addLivro;
        printf("Digite o valor do livro %d: ", i + 1);
        scanf("%d", &addLivro);

        int posicao = insere(&pilha, addLivro);

        if (posicao != -1) {
            printf("Livro inserido na posição %d da pilha.\n", posicao);
        }
    }

    return 0;
}
