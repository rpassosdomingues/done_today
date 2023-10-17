#ifndef TREE_H
#define TREE_H

// Structure for a binary tree node
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int item);
Node* insertNode(Node* node, int value);
void printInOrder(Node* root);
Node* seed(int n);
Node* trim(int arr[], int start, int end);
Node* balanceTree(Node* root, int n);

#endif
