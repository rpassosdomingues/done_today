#ifndef _H_TREES
#define _H_TREES

// Structure to represent a node in the tree
typedef struct tree_ {
    int data;          // Data value stored in the node
    int height;        // Height of the node (for AVL trees)
    struct tree_ *left;  // Pointer to the left child
    struct tree_ *right; // Pointer to the right child
} tree;

tree *createSubTree(int data);

tree *insertBinaryTree(tree *root, int data);
tree *insertAVLTree(tree* root, int data);

tree *removeBinaryTree(tree *root, int data);
tree *removeAVLTree(tree *root, int data);

tree *search(tree *root, int data);
tree *searchFather(tree *root, tree *node, tree *parent);
int height(tree *node);
void updateHeight(tree* node);
tree *minValueNode(tree *node);

tree* rotateRight(tree *node);
tree* rotateLeft(tree *node);

int balanceFactor(tree *node);
tree *balanceNode(tree* node);

void printInOrder(tree *root);

void freeTree(tree *root);

double binaryTree(tree *root, int instance);
double avlTree(tree *root, int instance);

#endif // _H_TREES