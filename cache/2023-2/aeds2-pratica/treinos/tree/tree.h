#ifndef _H_ARVORE
#define _H_ARVORE

// Define a structure for a tree node
typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} Node;

Node* newNode(int item);
Node* insertNode(Node* node, int value);
Node* findMin(Node* node);
Node* removeNode(Node* root, int value);
void printInOrder(Node* root);
void printPreOrder(Node* root);
void printPosOrder(Node* root);
void displayMenu();
void deallocateTree(Node* root);

#endif // _H_ARVORE