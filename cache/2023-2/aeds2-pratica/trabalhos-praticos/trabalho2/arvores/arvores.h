// arvores.h

#ifndef ARVORES_H
#define ARVORES_H

struct AVLNode;

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createBinaryTree(int instancia_num);
struct AVLNode* createAVLTree(int instancia_num);

void freeBinaryTree(struct TreeNode* root);
void freeAVLTree(struct AVLNode* root);

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif
