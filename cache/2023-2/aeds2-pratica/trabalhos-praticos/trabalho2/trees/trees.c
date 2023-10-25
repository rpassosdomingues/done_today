#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trees.h"

tree *createSubTree(int data) {
    tree *newNode = malloc(sizeof(tree));
    if (newNode == NULL) {
        printf("\nMemory Allocation Error!");
    } else {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

tree *insertBinaryTree(tree *root, int data) {
    if (root == NULL) {
        return createSubTree(data);
    }
    if (data < root->data) {
        root->left = insertBinaryTree(root->left, data);
    } else if (data > root->data) {
        root->right = insertBinaryTree(root->right, data);
    }
    return root;
}

tree *insertAVLTree(tree* root, int data) {
    if (root == NULL) {
        tree* newNode = malloc(sizeof(tree));
        if (newNode == NULL) {
            printf("\nMemory Allocation Error");
            exit(1);
        }
        newNode->data = data;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (data < root->data) {
        root->left = insertAVLTree(root->left, data);
    } else if (data > root->data) {
        root->right = insertAVLTree(root->right, data);
    }

    return balanceNode(root);
}

tree *removeBinaryTree(tree *root, int data) {
    if (root == NULL) {
        return root;
    }

    // Recursively search for the node to remove
    if (data < root->data) {
        root->left = removeBinaryTree(root->left, data);
    } else if (data > root->data) {
        root->right = removeBinaryTree(root->right, data);
    } else {
        // Node with the key to be deleted found

        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            tree *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            tree *temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children, get the inorder successor
        tree *temp = minValueNode(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = removeBinaryTree(root->right, temp->data);
    }
    return root;
}

tree *removeAVLTree(tree *root, int data) {
    tree *oldNode = search(root, data);

    if (oldNode == NULL) {
        printf("\nSub-Tree not found");
        return root;
    }

    tree *father = searchFather(root, oldNode, NULL);

    if (oldNode->left == NULL && oldNode->right == NULL) {
        // Case 1: No childs
        if (father == NULL) {
            // Remove root
            free(root);
            return NULL;
        } else if (father->left == oldNode) {
                free(father->left);
                father->left = NULL;
            } else {
                free(father->right);
                father->right = NULL;
            }
    } else if (oldNode->left == NULL || oldNode->right == NULL) {
        // Case 2: One child
        tree *child = (oldNode->left != NULL) ? oldNode->left : oldNode->right;
        if (father == NULL) {
            free(root);
            return child;
        } else if (father->left == oldNode) {
                free(father->left);
                father->left = child;
            } else {
                free(father->right);
                father->right = child;
            }
        } else {
            // Case 3: Two childs.
            tree *successor = oldNode->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }

            int tmp = successor->data;
            root = removeAVLTree(root, tmp);
            oldNode->data = tmp;
        }

    return root;
}

tree *search(tree *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

tree *searchFather(tree *root, tree *node, tree *parent) {
    if (root == NULL || node == NULL) {
        return NULL;  // Node not found or tree is empty
    }

    if (root->left == node || root->right == node) {
        return root;  // Found the parent of the given node
    }

    if (node->data < root->data) {
        return searchFather(root->left, node, root);
    } else {
        return searchFather(root->right, node, root);
    }
}

int height(tree *node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

void updateHeight(tree* node) {
    if (node == NULL) {
        return;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

tree *minValueNode(tree *node) {
    tree *current = node;

    // Find the leftmost leaf node
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

tree* rotateRight(tree *node) {
    tree* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

tree* rotateLeft(tree* node) {
    tree* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

int balanceFactor(tree *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

tree *balanceNode(tree* node) {
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

    return node;
}

void printInOrder(tree *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}

void freeTree(tree *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

double binaryTree(tree *root, int instance) {
    double time = 0;
    clock_t begin = clock();

    root = insertBinaryTree(root, instance);
    
    clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    return (1000 * time);
}

double avlTree(tree *root, int instance) {
    double time = 0;
    clock_t begin = clock();

    root = insertAVLTree(root, instance);

    clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    return (1000 * time);
}


int main(int argc, char* argv[]) {

    int instance = -1;
    instance = atoi(argv[1]);
    if (instance < 1 || instance > 3) {
        printf("Enter a ./tree x\n\twhere x is number between 1 and 3 of instances.\n");
        exit(0);
    }
    
    tree *root = NULL;

    double time_binaryTree = binaryTree(root, instance);
    double time_avlTree = avlTree(root, instance);
    
    printf("%f\n%f\n", time_binaryTree, time_avlTree);

    return (1);
}
