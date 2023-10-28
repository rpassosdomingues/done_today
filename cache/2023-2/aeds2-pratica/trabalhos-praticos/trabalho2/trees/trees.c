/***
 * Authors:
 * 
 * Pedro Mendes
 * Rafael Domingues
 * Rikson Pablo Rocha
 ***
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trees.h"

// Function to create a new tree node with the given data
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

// Function to insert a node into a binary search tree
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

// Function to insert a node into an AVL tree
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

// Function to remove a node from a binary search tree
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

// Function to remove a node from an AVL tree
tree *removeAVLTree(tree *root, int data) {
    tree *oldNode = search(root, data);

    if (oldNode == NULL) {
        //printf("\nSub-Tree not found");
        return root;
    }

    tree *father = searchFather(root, oldNode, NULL);

    if (oldNode->left == NULL && oldNode->right == NULL) {
        // Case 1: No children
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
        // Case 3: Two children.
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

// Function to search for a node with a specific data value
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

// Function to find the parent node of a given node in the tree
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

// Function to get the height of a node (used in AVL trees)
int height(tree *node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// Function to update the height of a node
void updateHeight(tree* node) {
    if (node == NULL) {
        return;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to find the node with the minimum value in a tree
tree *minValueNode(tree *node) {
    tree *current = node;

    // Find the leftmost leaf node
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Function to perform a right rotation on a node in an AVL tree
tree* rotateRight(tree *node) {
    tree* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to perform a left rotation on a node in an AVL tree
tree* rotateLeft(tree* node) {
    tree* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to calculate the balance factor of a node (used in AVL trees)
int balanceFactor(tree *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Function to balance an AVL tree node
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

// Function to perform an in-order traversal of the tree and print the values (used to inputs tests)
void printInOrder(tree *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}

// Function to free the memory used by the tree
void freeTree(tree *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Function to benchmark operations on a binary tree
double binaryTree(tree *root, int instance) {
    double time = 0;
    clock_t begin = clock();

    // Insert data from 0 to 10,000 into the insertion functions
    for (int row = 0; row <= 10000; row++) {
        root = insertBinaryTree(root, row);
    }
    // Remove data from 10000 to 20000 from the removal functions
    for (int row = 10001; row <= 20000; row++) {
        root = removeBinaryTree(root, row);
    }
    
    clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    return (1000 * time); // Convert to milliseconds
}

// Function to benchmark operations on an AVL tree
double avlTree(tree *root, int instance) {
    double time = 0;
    clock_t begin = clock();

    // Insert data from 0 to 10,000 into the insertion functions
    for (int row = 0; row <= 10000; row++) {
        root = insertAVLTree(root, row);
    }
    // Remove data from 10001 to 20000 from the removal functions
    for (int row = 10001; row <= 20000; row++) {
        root = removeAVLTree(root, row);
    }

    clock_t end = clock();
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    return (1000 * time); // Convert to milliseconds
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [instance]\n", argv[0]);
        printf("Please provide an instance (1, 2, or 3) as a command-line argument.\n");
        return 1;
    }

    // Instance Reader
    int instance = atoi(argv[1]);
    if (instance < 1 || instance > 3) {
        printf("Invalid instance. Please provide 1, 2, or 3.\n");
        return 1;
    }

    // Initialize tree roots pointers with NULL
    tree *binaryTreeRoot = NULL;
    tree *avlTreeRoot = NULL;

    // Call the function of the benckmarks operations on an trees
    double time_binaryTree = binaryTree(binaryTreeRoot, instance);
    double time_avlTree = avlTree(avlTreeRoot, instance);

    // Show results of the benckmarks operations on an trees
    printf("\nTime taken for Binary Tree: %f ms\n", time_binaryTree);
    printf("Time taken for AVL Tree: %f ms\n\n", time_avlTree);

    // Free the memory used by the trees
    freeTree(binaryTreeRoot);
    freeTree(avlTreeRoot);

    return 0;
}
