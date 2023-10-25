#ifndef _H_TREES
#define _H_TREES

typedef struct tree_ {
    int data;
    int height;
    struct tree_ *left;
    struct tree_ *right;
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