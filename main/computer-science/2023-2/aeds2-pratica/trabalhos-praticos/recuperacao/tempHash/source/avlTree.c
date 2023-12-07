/**
 * =========================================================================
 * Utility functions to collision handling using AVL Tree
 * =========================================================================
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "header.h"

#include "../data/instanceReader.c"

#define MAX_PLAYERS 1149

// Function to create an AVL tree from an array of players
AVLTree* createAVLTree(Player player[]) {
    AVLTree* root = NULL;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        root = insertAVLTree(root, player[i]);
        root = balanceNode(root);  // Ensure balancing after each insertion
    }

    return root;
}

// Utility function to create an AVL node
AVLTree* createAVLNode(Player player) {
    AVLTree* newNode = (AVLTree*)malloc(sizeof(AVLTree));
    if (newNode == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    newNode->player = player;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

// Function to search for a player in AVL Tree
AVLTree* searchAVLTree(AVLTree* node, Player player) {
    // Check for NULL node
    if (node == NULL) {
        printf("Error: AVL Tree is NULL.\n");
        return NULL;
    }

    while (node != NULL) {
        int comparisonResult = strcmp(player.name, node->player.name);

        if (comparisonResult < 0) {
            node = node->left;
        } else if (comparisonResult > 0) {
            node = node->right;
        } else {
            // Player found in AVL Tree
            return node;
        }
    }

    // Player not found in AVL Tree
    printf("Player '%s' not found in AVL Tree.\n", player.name);
    return NULL;
}

// Function to find the parent node of a given node in the Tree
AVLTree* searchFather(AVLTree* root, AVLTree* node, AVLTree* parent) {
    if (root == NULL || node == NULL) {
        return NULL;  // Node not found or Tree is empty
    }

    AVLTree* foundNode = searchAVLTree(root, node->player);

    if (foundNode != NULL) {
        // Node found, check if it is the child of the provided parent
        if (parent == NULL || (root->left == foundNode || root->right == foundNode)) {
            return root;  // Found the parent of the given node
        }
    }

    // Search recursively
    AVLTree* nextRoot = (strcmp(node->player.name, root->player.name) < 0) ? root->left : root->right;
    return searchFather(nextRoot, node, root);
}

// Function to insert a node into an AVL Tree
AVLTree* insertAVLTree(AVLTree* root, Player player) {
    if (root == NULL) {
        // Create a new AVL node for the current player
        return createAVLNode(player);
    }

    int comparisonResult = strcmp(player.name, root->player.name);

    if (comparisonResult < 0) {
        root->left = insertAVLTree(root->left, player);
    } else if (comparisonResult > 0) {
        root->right = insertAVLTree(root->right, player);
    }

    return balanceNode(root);
}

// Function to remove a node from an AVL Tree
AVLTree* removeAVLTree(AVLTree* root, Player player) {
    AVLTree *oldNode = searchAVLTree(root, player);

    if (oldNode == NULL) {
        //printf("\nSub-Tree not found");
        return root;
    }

    AVLTree* father = searchFather(root, oldNode, NULL);

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
        AVLTree *child = (oldNode->left != NULL) ? oldNode->left : oldNode->right;
        if (father == NULL) {
            //free(root);
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
        AVLTree *successor = minValueNode(oldNode->right);
        oldNode->player = successor->player;
        oldNode->right = removeMinValueNode(oldNode->right);
    }

    return balanceNode(father);
}

AVLTree* removeMinValueNode(AVLTree* root) {
    if (root == NULL || root->left == NULL) {
        return root->right;
    }

    root->left = removeMinValueNode(root->left);
    return balanceNode(root);
}

// Function to find the node with the minimum value in a Tree
AVLTree* minValueNode(AVLTree* node) {
    AVLTree *current = node;

    // Find the leftmost leaf node
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Function to perform a right rotation on a node in an AVL Tree
AVLTree* rotateRight(AVLTree* node) {
    AVLTree* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to perform a left rotation on a node in an AVL Tree
AVLTree* rotateLeft(AVLTree* node) {
    AVLTree* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to balance an AVL Tree node
AVLTree* balanceNode(AVLTree* node) {
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

// Function to get the height of a node (used in AVL Trees)
int height(AVLTree* node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// Function to calculate the balance factor of a node (used in AVL Trees)
int balanceFactor(AVLTree* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Function to update the height of a node
void updateHeight(AVLTree* node) {
    if (node == NULL) {
        return;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to free the memory allocated for an AVL Tree
void freeAVLTree(AVLTree* root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}