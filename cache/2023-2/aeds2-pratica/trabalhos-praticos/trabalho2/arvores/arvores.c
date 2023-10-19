#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"

// Estrutura de um nó da árvore AVL
struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
};

// Função para criar um novo nó da árvore binária de busca
struct TreeNode* createTreeNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        perror("Falha na alocação de memória.");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor em uma árvore binária de busca
struct TreeNode* insertTreeNode(struct TreeNode* root, int value) {
    if (root == NULL) {
        return createTreeNode(value);
    }
    if (value < root->data) {
        root->left = insertTreeNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertTreeNode(root->right, value);
    }
    return root;
}

// Função para criar uma árvore binária de busca
struct TreeNode* createBinaryTree(int instancia_num) {
    struct TreeNode* root = NULL;
    srand((unsigned)time(NULL)); // Inicializa a semente do gerador de números aleatórios
    for (int i = 0; i < instancia_num; i++) {
        int value = rand() % 100; // Gera números aleatórios de 0 a 99
        root = insertTreeNode(root, value);
    }
    return root;
}

// Função para percorrer a árvore binária de busca em ordem
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        // Fazer algo com o valor do nó, por exemplo, imprimir
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Função para liberar a memória de uma árvore binária de busca
void freeBinaryTree(struct TreeNode* root) {
    if (root != NULL) {
        freeBinaryTree(root->left);
        freeBinaryTree(root->right);
        free(root);
    }
}

// Função para calcular a altura de um nó da árvore AVL
int height(struct AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Função para calcular o fator de balanceamento de um nó da árvore AVL
int balanceFactor(struct AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Função para atualizar a altura de um nó da árvore AVL
void updateHeight(struct AVLNode* node) {
    if (node == NULL) {
        return;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Função para realizar uma rotação simples à direita em um nó da árvore AVL
struct AVLNode* rotateRight(struct AVLNode* node) {
    struct AVLNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Função para realizar uma rotação simples à esquerda em um nó da árvore AVL
struct AVLNode* rotateLeft(struct AVLNode* node) {
    struct AVLNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Função para balancear um nó da árvore AVL
struct AVLNode* balanceNode(struct AVLNode* node) {
    updateHeight(node);
    int factor = balanceFactor(node);

    if (factor > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (factor < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node; // Nó já está balanceado
}

// Função para inserir um valor em uma árvore AVL
struct AVLNode* insertAVLNode(struct AVLNode* root, int value) {
    if (root == NULL) {
        struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
        if (newNode == NULL) {
            perror("Falha na alocação de memória.");
            exit(1);
        }
        newNode->data = value;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (value < root->data) {
        root->left = insertAVLNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertAVLNode(root->right, value);
    }

    return balanceNode(root);
}

// Função para criar uma árvore AVL
struct AVLNode* createAVLTree(int instancia_num) {
    struct AVLNode* root = NULL;
    srand((unsigned)time(NULL)); // Inicializa a semente do gerador de números aleatórios
    for (int i = 0; i < instancia_num; i++) {
        int value = rand() % 100; // Gera números aleatórios de 0 a 99
        root = insertAVLNode(root, value);
    }
    return root;
}

// Função para percorrer a árvore AVL em ordem
void inorderAVLTraversal(struct AVLNode* root) {
    if (root != NULL) {
        inorderAVLTraversal(root->left);
        // Fazer algo com o valor do nó, por exemplo, imprimir
        printf("%d ", root->data);
        inorderAVLTraversal(root->right);
    }
}

// Função para liberar a memória de uma árvore AVL
void freeAVLTree(struct AVLNode* root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

double arvore_binaria(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    // Criar uma árvore binária de busca com os valores gerados aleatoriamente
    struct TreeNode* root = createBinaryTree(instancia_num);

    clock_t end = clock();
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;

    // Fazer algo com a árvore, por exemplo, percorrer em ordem
    // inorderTraversal(root);

    // Liberar a memória alocada para a árvore binária de busca
    freeBinaryTree(root);

    return tempo;
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    // Criar uma árvore AVL com os valores gerados aleatoriamente
    struct AVLNode* root = createAVLTree(instancia_num);

    clock_t end = clock();
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;

    // Fazer algo com a árvore AVL, se necessário.
    // Por exemplo, percorrer em ordem
    // inorderAVLTraversal(root);

    // Liberar a memória alocada para a árvore AVL
    freeAVLTree(root);

    return tempo;
}

int main() {
    // Abre o arquivo para a árvore binária desbalanceada
    FILE* arquivo_desbalanceada = fopen("arvore_desbalanceada.txt", "w");
    if (arquivo_desbalanceada == NULL) {
        perror("Erro ao abrir o arquivo para a árvore desbalanceada");
        exit(1);
    }

    // Abre o arquivo para a árvore AVL balanceada
    FILE* arquivo_balanceada = fopen("arvore_balanceada.txt", "w");
    if (arquivo_balanceada == NULL) {
        perror("Erro ao abrir o arquivo para a árvore balanceada");
        exit(1);
    }

    // Realiza as medições para diferentes tamanhos de instância (de 0 a 1000 de um em um)
    for (int instancia_num = 0; instancia_num <= 1000; instancia_num++) {
        double tempo_n_balanceada = arvore_binaria(instancia_num);
        double tempo_balanceada = arvore_balanceada(instancia_num);

        // Escreve os tempos de execução no arquivo da árvore binária desbalanceada
        fprintf(arquivo_desbalanceada, "%d %f\n", instancia_num, tempo_n_balanceada);

        // Escreve os tempos de execução no arquivo da árvore AVL balanceada
        fprintf(arquivo_balanceada, "%d %f\n", instancia_num, tempo_balanceada);
    }

    // Fecha os arquivos
    fclose(arquivo_desbalanceada);
    fclose(arquivo_balanceada);

    return 0;
}